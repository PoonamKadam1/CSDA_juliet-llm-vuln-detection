# Code : evaluation
# compares each model's answers (results/*.jsonl) with the answer key (labels.csv)
# and saves the result tables in evaluation/ (summary, per_cwe, details)
# run: python evaluate.py

import argparse
import csv
import glob
import json
import os
import re


sample = "/Volumes/Seagate/juliet_data/llm_sample"

# CWEs counted as "related" to each target CWE (same weakness family)
buffer_cwes = {"119", "120", "121", "122", "124", "125", "126",
               "127", "131", "170", "193", "787", "788", "805", "806"}
related = {
    "78": {"78", "77", "88"},                     # command / argument injection
    "121": buffer_cwes,                           # stack overflow -> buffer errors
    "122": buffer_cwes,                           # heap overflow -> buffer errors
    "190": {"190", "191", "128", "680", "682"},   # integer overflow / wraparound
    "416": {"416", "825", "672"},                 # use after free
    "476": {"476", "690", "824"},                 # NULL pointer dereference
}
near = 2  # a predicted line at most 2 lines away from the flaw line counts as "near"


# ---------- small helpers ----------
# to get only the number of CWE
def cwe_number(text):
    if not text:
        text = ""
    m = re.search(r"(\d+)", str(text))
    if m:
        return m.group(1)
    return ""

 # turn the model's line numbers into whole numbers, skip anything that is not a number
def to_int_list(values):
    out = []
    if not isinstance(values, list):
        return out
    for v in values:
        try:
            out.append(int(v))
        except (TypeError, ValueError):
            pass
    return out

# a out of b as a percentage with 1 decimal (empty if b is 0)
def percent(a, b):
    if not b:
        return ""
    return round(100 * a / b, 1)

# save a list of rows (dictionaries) as a CSV file
def write_csv(path, rows):
    with open(path, "w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=list(rows[0].keys()))
        writer.writeheader()
        writer.writerows(rows)

# for CWE Number
def cwe_sort_number(cwe):
    return int(cwe_number(cwe))


def compute_metrics(rows):
    tp = 0   # bad file, model said vulnerable    (correct)
    fn = 0   # bad file, model said safe          (missed)
    fp = 0   # good file, model said vulnerable  (false alarm)
    tn = 0   # good file, model said safe       (correct)
    for r in rows:
        if r["label"] == "bad" and r["said_vuln"]:
            tp = tp + 1
        elif r["label"] == "bad":
            fn = fn + 1
        elif r["said_vuln"]:
            fp = fp + 1
        else:
            tn = tn + 1

    #   Accuracy    = (tp + tn) / (tp + fn + fp + tn)
    #   Precision   = tp / (tp + fp)
    #   Recall      = tp / (tp + fn)
    #   Specificity = tn / (fp + tn)      -> false alarm rate = fp / (fp + tn) = 1 - specificity
    #   F1 (Fscore, beta = 1) = 2 * Precision * Recall / (Precision + Recall)
    precision = 0
    if tp + fp > 0:
        precision = tp / (tp + fp)
    recall = 0
    if tp + fn > 0:
        recall = tp / (tp + fn)
    f1 = 0
    if precision + recall > 0:
        f1 = 2 * precision * recall / (precision + recall)

    # the vulnerable files the model found (only these are checked for CWE and line)
    found = []
    for r in rows:
        if r["label"] == "bad" and r["said_vuln"]:
            found.append(r)
    cwe_exact = 0
    cwe_related = 0
    line_exact = 0
    line_near = 0
    for r in found:
        cwe_exact += r["cwe_exact"]
        cwe_related += r["cwe_related"]
        line_exact += r["line_exact"]
        line_near += r["line_near"]

    no_answer = 0
    total_seconds = 0
    for r in rows:
        no_answer += r["unparsed"]
        total_seconds += r["seconds"]
    avg_seconds = ""
    if rows:
        avg_seconds = round(total_seconds / len(rows), 1)

    return {
        "files": len(rows),
        "TP": tp, "FN": fn, "FP": fp, "TN": tn,
        "accuracy_%": percent(tp + tn, len(rows)),
        "recall_%": percent(tp, tp + fn),
        "precision_%": percent(tp, tp + fp),
        "F1_%": round(100 * f1, 1),
        "false_alarm_rate_%": percent(fp, fp + tn),
        "cwe_exact_%": percent(cwe_exact, len(found)),
        "cwe_related_%": percent(cwe_related, len(found)),
        "line_exact_%": percent(line_exact, len(found)),
        "line_near_%": percent(line_near, len(found)),
        "no_answer": no_answer,
        "avg_seconds": avg_seconds,
    }


# ---------- main ----------

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--sample", default=sample)
    args = ap.parse_args()

    #to load the answer key
    labels_path = os.path.join(args.sample, "labels.csv")
    if not os.path.exists(labels_path):
        print("error: cannot find", labels_path)
        raise SystemExit(1)
    labels = {}
    with open(labels_path, newline="") as f:
        for row in csv.DictReader(f):
            labels[row["file"]] = row

    # to  find all model result files (one per model)
    pattern = os.path.join(args.sample, "results", "*.jsonl")
    result_files = sorted(glob.glob(pattern))
    if not result_files:
        print("error: no model answers found in results/")
        raise SystemExit(1)

    # to check every answer against the answer key
    details = []
    for path in result_files:
        answers = []
        with open(path) as f:
            for line in f:
                if line.strip():
                    answers.append(json.loads(line))

        if answers:
            model = answers[0]["model"]
        else:
            model = os.path.basename(path)

        answered = set()
        for a in answers:
            answered.add(a["file"])
        missing = len(labels) - len(answered)
        if missing:
            print("Note: " + model + " has no answer yet for " + str(missing)
                  + " of " + str(len(labels)) + " files (run not finished?)")

        for a in answers:
            lab = labels[a["file"]]            # the correct answer for this file
            ans = a.get("answer")              # the model's answer
            if not ans:
                ans = {}

            target = cwe_number(lab["cwe"])            # correct CWE?
            said_vuln = ans.get("vulnerable") is True  # did the model say "vulnerable"?
            got_cwe = cwe_number(ans.get("cwe"))       # CWE the model named

            flaws = []                                 # correct flaw line?
            for x in lab["flaw_lines"].split(";"):
                if x:
                    flaws.append(int(x))
            lines = to_int_list(ans.get("lines"))      #  model named?

            if target in related:
                allowed = related[target]
            else:
                allowed = {target}

            # did the model name a flaw line exactly, or within 2 lines?
            exact_hit = False
            near_hit = False
            for l in lines:
                for t in flaws:
                    if l == t:
                        exact_hit = True
                    if abs(l - t) <= near:
                        near_hit = True

            line_texts = []
            for x in lines:
                line_texts.append(str(x))

            if got_cwe:
                model_cwe = "CWE-" + got_cwe
            else:
                model_cwe = ""

            seconds = a.get("seconds")
            if not seconds:
                seconds = 0

            details.append({
                "model": model,
                "file": a["file"],
                "cwe": lab["cwe"],
                "label": lab["label"],
                "variant": lab["variant"],
                "said_vuln": said_vuln,
                "correct": said_vuln == (lab["label"] == "bad"),
                "true_lines": lab["flaw_lines"],
                "model_lines": ";".join(line_texts),
                "model_cwe": model_cwe,
                "cwe_exact": said_vuln and got_cwe == target,
                "cwe_related": said_vuln and got_cwe in allowed,
                "line_exact": said_vuln and exact_hit,
                "line_near": said_vuln and near_hit,
                "unparsed": bool(ans.get("_unparsed")),
                "seconds": seconds,
                "why": ans.get("why", ""),
                "fix": ans.get("fix", ""),
            })

    # to group the answers by model, then make the summary and per-CWE table. 
    by_model = {}
    for d in details:
        if d["model"] not in by_model:
            by_model[d["model"]] = []
        by_model[d["model"]].append(d)

    summary = []
    per_cwe = []
    for model in by_model:
        rows = by_model[model]

        row = {"model": model}
        metrics = compute_metrics(rows)
        for key in metrics:
            row[key] = metrics[key]
        summary.append(row)

        by_cwe = {}
        for r in rows:
            if r["cwe"] not in by_cwe:
                by_cwe[r["cwe"]] = []
            by_cwe[r["cwe"]].append(r)
        for cwe in sorted(by_cwe, key=cwe_sort_number):
            row = {"model": model, "cwe": cwe}
            metrics = compute_metrics(by_cwe[cwe])
            for key in metrics:
                row[key] = metrics[key]
            per_cwe.append(row)

    # to  save the CSV files
    out = os.path.join(args.sample, "evaluation")
    os.makedirs(out, exist_ok=True)
    write_csv(os.path.join(out, "summary.csv"), summary)
    write_csv(os.path.join(out, "per_cwe.csv"), per_cwe)
    write_csv(os.path.join(out, "details.csv"), details)

    # to  print the tables on screen
    overall_rows = []
    for s in summary:
        overall_rows.append([s["model"], str(s["files"]), fmt(s["accuracy_%"]), fmt(s["recall_%"]),
                             fmt(s["false_alarm_rate_%"]), fmt(s["F1_%"]), fmt(s["cwe_exact_%"]),
                             fmt(s["cwe_related_%"]), fmt(s["line_exact_%"]), fmt(s["line_near_%"]),
                             fmt(s["avg_seconds"], False)])
    print_table("OVERALL",
                ["Model", "Files", "Accuracy", "Recall", "False alarms", "F1",
                 "CWE exact", "CWE related", "Line exact", "Line +-2", "Sec/file"],
                overall_rows)

    cwe_rows = []
    for p in per_cwe:
        cwe_rows.append([p["model"], p["cwe"], fmt(p["recall_%"]), fmt(p["false_alarm_rate_%"]),
                         fmt(p["F1_%"]), fmt(p["cwe_related_%"]), fmt(p["line_near_%"])])
    print_table("PER CWE (recall = vulnerable files found, false alarms = safe files flagged)",
                ["Model", "CWE", "Recall", "False alarms", "F1", "CWE related", "Line +-2"],
                cwe_rows, left=2)

    print("\nSaved tables to " + out + "/")


# ---------- display helpers and percentage conversion ----------

def fmt(value, add_percent=True):
    if value == "" or value is None:
        return "-"
    if add_percent and isinstance(value, float):
        return str(round(value, 1)) + "%"
    return str(value)

 # print a neat table
def print_table(title, header, rows, left=1):
    widths = []
    for i in range(len(header)):
        w = len(header[i])
        for r in rows:
            if len(r[i]) > w:
                w = len(r[i])
        widths.append(w)

    print("\n" + title)
    print(make_line(header, widths, left))
    dashes = []
    for w in widths:
        dashes.append("-" * w)
    print("  ".join(dashes))
    for r in rows:
        print(make_line(r, widths, left))

#formatting 
def make_line(cells, widths, left):
    parts = []
    for i in range(len(cells)):
        if i < left:
            parts.append(cells[i].ljust(widths[i]))
        else:
            parts.append(cells[i].rjust(widths[i]))
    return "  ".join(parts)


if __name__ == "__main__":
    main()