# Code: dataset prep and sanitization
# juliet testcases we selected -> 145 good + 145 bad = 290 clean files + labels.csv
import argparse
import csv
import glob
import os
import random
import re
import shutil
from collections import defaultdict

nist = "/Volumes/Seagate/juliet_data/nist/C/testcases"
outdir = "/Volumes/Seagate/juliet_data/llm_sample"
cwes = ["78", "121", "122", "190", "416", "476"] # CWEs use for project
#-------------------------------------
# Serch pattern so we can sanitize
#-------------------------------------
re_file = re.compile(r"^CWE(\d+)_.*_(\d{2})\.(c|cpp)$")
re_if = re.compile(r"^\s*#\s*(if|ifdef|ifndef)\b\s*(\w*)") # read file and find word and ifndef in group 1  keyword (if|ifdef|ifndef) and group 2 Omitbad
re_else = re.compile(r"^\s*#\s*else\b") # Read else decision and flip stack
re_endif = re.compile(r"^\s*#\s*endif\b") # Read endif and pop stack
re_flaw = re.compile(r"/\*\s*(POTENTIAL\s+)?FLAW")  # to find flaw comment in code
re_comment = re.compile(r"^(/\*|//|\*(\s|/|$))") # to find comment lines in code
re_func = re.compile(r"\)\s*\{")    # to find function definitions in code
re_hint = re.compile(r"\b\w*(?:bad|good|cwe\d+)\w*\b", re.I)    # to find bad/good/cwe words in code
MARK = "JULIET_FLAW_MARKER_X"
#-------------------------------------
# Spliting juliet file into good and bad versions, keeping only the requested one
#-------------------------------------
def split_version(code, keep):
    out = []
    stack = []
    for line in code.splitlines():
        m = re_if.match(line)
        if m:
            kind, name = m.group(1), m.group(2)
            if kind == "ifndef" and name == "OMITBAD":
                stack.append((True, keep == "bad"))
            elif kind == "ifndef" and name == "OMITGOOD":
                stack.append((True, keep == "good"))
            elif kind == "ifdef" and name == "INCLUDEMAIN":
                stack.append((True, False))
            else:
                stack.append((False, True))
                if all(a for _, a in stack):
                    out.append(line)
            continue
        if re_else.match(line) and stack:
            tracked, was = stack[-1]
            if tracked:
                stack[-1] = (True, not was)
            elif all(a for _, a in stack):
                out.append(line)
            continue
        if re_endif.match(line) and stack:
            tracked, _ = stack.pop()
            if not tracked and all(a for _, a in stack):
                out.append(line)
            continue
        if all(a for _, a in stack):
            out.append(line)
    return "\n".join(out) + "\n"

## put MARK after the FLAW comment
def mark_flaws(code):
    out = []
    pending = False
    for line in code.splitlines():
        s = line.strip()
        if re_flaw.search(line):
            pending = True
            out.append(line)
            continue
        if pending and s and not re_comment.match(s):
            out.append(MARK)
            pending = False
        out.append(line)
    return "\n".join(out) + "\n"

## Strip comments and remove bad/good/CWE words from the code, so the model cannot  by looking at them miss understood and incorrect ans. 
def strip_comments(code):
    out = []
    i = 0
    n = len(code)
    while i < n:
        c = code[i]
        if c in "\"'":
            j = i + 1
            while j < n and code[j] != c:
                if code[j] == "\\":
                    j += 1
                j += 1
            out.append(code[i:j + 1])
            i = j + 1
        elif code.startswith("/*", i) or code.startswith("//", i):
            if code.startswith("/*", i):
                j = code.find("*/", i + 2)
                end = n if j == -1 else j + 2
            else:
                j = code.find("\n", i)
                end = n if j == -1 else j
            cur = "".join(out)
            line_start = cur.rfind("\n") + 1
            k = code.find("\n", end)
            rest = code[end:n if k == -1 else k]
            if cur[line_start:].strip() == "" and rest.strip() == "":
                out = [cur[:line_start]]
                i = n if k == -1 else k + 1
            else:
                out.append(" ")
                i = end
        else:
            out.append(c)
            i += 1
    return "".join(out)

# replace bad/good/CWE words with func1, func2, like that so the model cannot miss understood and incorrect ans. 
def remove_leaks(code):  
    mapping = {}

    def repl(m): # replace matched words with function names 
        w = m.group(0)
        if w not in mapping:
            mapping[w] = "func" + str(len(mapping) + 1)
        return mapping[w]

    return re_hint.sub(repl, code)

## remove comments, bad/good/CWE words, trailing whitespace, and extra blank lines
def clean(code): 
    code = strip_comments(code)
    code = remove_leaks(code)
    code = "\n".join(line.rstrip() for line in code.splitlines())
    code = re.sub(r"\n\s*\n+", "\n\n", code).strip() + "\n"
    return code

# to pull out MARK lines, return code + line numbers
def take_markers(code): 
    
    out = []
    flaws = []
    for line in code.split("\n"):
        if line.strip() == MARK:
            flaws.append(len(out) + 1)
            continue
        out.append(line)
    return "\n".join(out), flaws


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--cwes", nargs="+", default=cwes)
    ap.add_argument("--pairs", type=int, default=25)
    ap.add_argument("--seed", type=int, default=42)
    ap.add_argument("--variants", nargs="+", default=["01", "09"])
    ap.add_argument("--nist", default=nist)
    ap.add_argument("--out", default=outdir)
    args = ap.parse_args()
    variants = set()
    for v in args.variants:
        variants.add(f"{int(v):02d}")

    if not os.path.isdir(args.nist):
        print("error: cannot find", args.nist)
        raise SystemExit(1)

    pairs = defaultdict(list)
    for cwe in args.cwes:
        cwe = str(int(cwe))
        paths = glob.glob(os.path.join(args.nist, f"CWE{cwe}_*", "**", "*.c*"), recursive=True)
        found = 0
        skipped = 0
        for path in sorted(paths):
            m = re_file.match(os.path.basename(path))
            if not m or m.group(1) != cwe or m.group(2) not in variants:
                continue
            found += 1
            with open(path, encoding="utf-8", errors="replace") as f:
                original = f.read()
            # print(path)  # debug
            bad_code, flaws = take_markers(clean(mark_flaws(split_version(original, "bad"))))
            good_code, _ = take_markers(clean(split_version(original, "good")))
            if not (re_func.search(bad_code) and re_func.search(good_code) and flaws):
                skipped += 1
                continue
            pairs[f"CWE{cwe}"].append({
                "path": os.path.relpath(path, os.path.dirname(args.nist)),
                "variant": m.group(2),
                "ext": "." + m.group(3),
                "bad": bad_code,
                "good": good_code,
                "flaws": flaws,
            })
        print(f"CWE{cwe}: {found} files found, {len(pairs['CWE' + cwe])} usable pairs, {skipped} skipped")

    rng = random.Random(args.seed)
    chosen = []
    print()
    for cwe in sorted(pairs, key=lambda c: int(c[3:])):
        k = min(args.pairs, len(pairs[cwe]))
        for p in rng.sample(pairs[cwe], k):
            chosen.append((cwe, "bad", p))
            chosen.append((cwe, "good", p))
        print(f"{cwe}: sampled {k} pairs")

    rng.shuffle(chosen)

    files_dir = os.path.join(args.out, "files")
    if os.path.isdir(files_dir):
        shutil.rmtree(files_dir)
    os.makedirs(files_dir)

    leaks = 0
    f = open(os.path.join(args.out, "labels.csv"), "w", newline="")
    w = csv.writer(f)
    w.writerow(["id", "file", "cwe", "label", "variant", "flaw_lines", "original_path"])
    for i, (cwe, label, p) in enumerate(chosen, start=1):
        name = f"sample_{i:04d}{p['ext']}"
        code = p[label]
        if re.search(r"bad|good|cwe\d", code, re.I):
            leaks += 1
        dst = open(os.path.join(files_dir, name), "w", encoding="utf-8")
        dst.write(code)
        dst.close()
        flaw_lines = ""
        if label == "bad":
            flaw_lines = ";".join(map(str, p["flaws"]))
        w.writerow([i, name, cwe, label, p["variant"], flaw_lines, p["path"]])
    f.close()

    print()
    print("Wrote", len(chosen), "cleaned files to", files_dir + "/")
    print("Answers saved in", os.path.join(args.out, "labels.csv"))
    print("Files still containing bad/good/CWE words:", leaks)


if __name__ == "__main__":
    main()
    
