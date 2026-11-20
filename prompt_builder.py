# Code : ask the LLMs? 
# sends each clean test file to a local model in Ollama and saves its answers in results/<model>.jsonl

import argparse
import csv
import json
import os
import time
import urllib.error
import urllib.request

sample = "/Volumes/Seagate/juliet_data/llm_sample"      # folder with files/ and labels.csv
ollama_url = "http://localhost:11434/api/generate"      # Ollama runs on this laptop

# the answer must follow this JSON structure (only types, no example values that could bias the model)
schema = {
    "type": "object",
    "properties": {
        "vulnerable": {"type": "boolean"},
        "lines": {"type": "array", "items": {"type": "integer"}},
        "cwe": {"type": "string"},
        "why": {"type": "string"},
        "fix": {"type": "string"},
    },
    "required": ["vulnerable", "lines", "cwe", "why", "fix"],
}

# the question sent to the model (do not change: all results were made with this exact prompt)
PROMPT = """You are a security code reviewer. Analyse the C/C++ code below for security vulnerabilities.
The code may or may not contain a vulnerability.

Notes about the code:
- Lines are numbered as "N | code". Use these numbers when you refer to lines.
- Helper functions such as printLine, printIntLine, printWLine and printHexCharLine only print values to the screen.
- Function names like func1, func2 have no meaning.

Answer these questions:
1. Is there a security vulnerability in this code? (true or false)
2. WHERE: which line number(s) contain the vulnerability?
3. WHAT: which CWE best describes it (for example "CWE-787")?
4. WHY: briefly explain why it is a vulnerability.
5. FIX: show how to fix it (the corrected line or lines).

If there is no vulnerability, set "vulnerable" to false, "lines" to [] and the other fields to "".

Reply ONLY with JSON in this format:
{{"vulnerable": <true or false>, "lines": [<line numbers>], "cwe": "<CWE ID>", "why": "<short explanation>", "fix": "<corrected code>"}}

"""
 # add line numbers so the model can name  line" 
def number_lines(code):
    lines = code.splitlines()
    numbered = []
    for i in range(len(lines)):
        numbered.append(str(i + 1) + " | " + lines[i])
    return "\n".join(numbered)

# to send one prompt to Ollama and return its reply
def ask(model, prompt, timeout):
    settings = {"temperature": 0, "seed": 42, "num_ctx": 4096, "num_predict": 600}  # temperature 0 + seed = same answer every time
    request_data = {
        "model": model,
        "prompt": prompt,
        "format": schema,      # force the JSON structure above
        "stream": False,       # wait for the full answer
        "options": settings,
    }
    body = json.dumps(request_data).encode()
    req = urllib.request.Request(ollama_url, data=body, headers={"Content-Type": "application/json"})
    with urllib.request.urlopen(req, timeout=timeout) as r:
        return json.loads(r.read())

# to take the JSON part of the reply; if it is broken, mark the answer as unparsed
def parse(text):
    try:
        start = text.index("{")
        end = text.rindex("}") + 1
        data = json.loads(text[start:end])
    except ValueError:
        return {"_unparsed": True}
    if isinstance(data, dict):
        return data
    return {"_unparsed": True}

#------------Main-----------------
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("model")                              
    ap.add_argument("--limit", type=int, default=None)    
    ap.add_argument("--sample", default=sample)
    ap.add_argument("--timeout", type=int, default=600)  
    args = ap.parse_args()

    # to get the list of files from labels.csv (only the file names are used not labels)
    labels_path = os.path.join(args.sample, "labels.csv")
    if not os.path.exists(labels_path):
        print("error: cannot find", labels_path)
        raise SystemExit(1)
    with open(labels_path, newline="") as f:
        rows = list(csv.DictReader(f))
    if args.limit:
        rows = rows[:args.limit]

    # results file for this model
    out_dir = os.path.join(args.sample, "results")
    os.makedirs(out_dir, exist_ok=True)
    file_name = args.model.replace(":", "_").replace("/", "_") + ".jsonl"
    out_path = os.path.join(out_dir, file_name)

    #  skip files that already have an answer, so a stopped run can just be started again
    done = set()
    if os.path.exists(out_path):
        with open(out_path) as f:
            for line in f:
                if line.strip():
                    done.add(json.loads(line)["file"])
    todo = []
    for r in rows:
        if r["file"] not in done:
            todo.append(r)

    print(f"Model: {args.model}")
    print(f"{len(rows)} files selected, {len(rows) - len(todo)} already done, {len(todo)} to run")
    print(f"Answers go to {out_path}\n")

    # to ask the model about each file
    times = []
    unparsed = 0
    with open(out_path, "a") as out:
        for n, row in enumerate(todo, start=1):
            with open(os.path.join(args.sample, "files", row["file"]), encoding="utf-8") as f:
                code = f.read()
            if row["file"].endswith(".cpp"):
                lang = "cpp"
            else:
                lang = "c"
            prompt = PROMPT.format(lang=lang, code=number_lines(code))

            start = time.time()
            try:
                resp = ask(args.model, prompt, args.timeout)
                raw = resp.get("response", "")
                error = None
            except urllib.error.URLError as e:     # if Ollama is not running: stop
                print("\nerror: cannot reach Ollama (" + str(e) + "). Is the Ollama app running?")
                raise SystemExit(1)
            except Exception as e:                 
                resp = {}
                raw = ""
                error = str(e)
            seconds = round(time.time() - start, 1)
            times.append(seconds)

            if error:
                answer = {"_unparsed": True}
            else:
                answer = parse(raw)
            if answer.get("_unparsed"):
                unparsed += 1

            # to save one line per file (raw = the model's exact reply and  keep it  as a log)
            result = {
                "file": row["file"],
                "model": args.model,
                "seconds": seconds,
                "answer": answer,
                "raw": raw,
                "error": error,
                "eval_tokens": resp.get("eval_count"),
            }
            out.write(json.dumps(result) + "\n")
            out.flush()   

            if answer.get("vulnerable") is True:
                said = "vulnerable"
            elif answer.get("vulnerable") is False:
                said = "not vulnerable"
            else:
                said = "no clear answer"
            print(f"[{n}/{len(todo)}] {row['file']}: {said} ({seconds}s)")

    if times:
        avg = sum(times) / len(times)
        print(f"\nAverage {avg:.1f} s per file; {unparsed} answer(s) were not valid JSON")
        print(f"Estimated time for all 290 files: about {avg * 290 / 60:.0f} minutes")

if __name__ == "__main__":
    main()