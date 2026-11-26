# Code: dataset prep and sanitization
# juliet testcases we selected -> 145 good + 145 bad = 290 clean files + labels.csv

import os
import re
import csv
import glob
import random
import shutil

NIST_PATH = "/Volumes/Seagate/juliet_data/nist/C/testcases"
OUT_DIR = "/Volumes/Seagate/juliet_data/llm_sample"
CWES = ["78", "121", "122", "190", "416", "476"]
VARIANTS = ["01", "09"]
PAIRS_PER_CWE = 25
SEED = 42
MARKER = "JULIET_FLAW_MARKER_X"


def get_version(code, keep_type):
    """Keep only the bad (OMITBAD) or good (OMITGOOD) code and drop main()."""
    lines = code.splitlines()
    result = []
    # Each item in stack is [is_target_macro, should_keep_lines]
    block_stack = []

    for line in lines:
        s = line.strip()

        if s.startswith("#ifndef OMITBAD"):
            block_stack.append([True, keep_type == "bad"])
            continue
        elif s.startswith("#ifndef OMITGOOD"):
            block_stack.append([True, keep_type == "good"])
            continue
        elif s.startswith("#ifdef INCLUDEMAIN"):
            block_stack.append([True, False])
            continue
        elif s.startswith("#if ") or s.startswith("#ifdef ") or s.startswith("#ifndef "):
            block_stack.append([False, True])
            if all_blocks_active(block_stack):
                result.append(line)
            continue

        if s.startswith("#else") and len(block_stack) > 0:
            last_block = block_stack[-1]
            if last_block[0] == True:
                last_block[1] = not last_block[1]
            elif all_blocks_active(block_stack):
                result.append(line)
            continue

        if s.startswith("#endif") and len(block_stack) > 0:
            last_block = block_stack.pop()
            if last_block[0] == False and all_blocks_active(block_stack):
                result.append(line)
            continue

        if all_blocks_active(block_stack):
            result.append(line)

    return "\n".join(result) + "\n"


def all_blocks_active(block_stack):
    """Check if all outer #if blocks are currently active."""
    for block in block_stack:
        if block[1] == False:
            return False
    return True

  """Put MARKER right before the vulnerable code line."""
def put_flaw_marker(code):
    lines = code.splitlines()
    result = []
    waiting_for_code = False

    for line in lines:
        s = line.strip()

        if ("/* FLAW" in s or "/* POTENTIAL FLAW" in s):
            waiting_for_code = True
            result.append(line)
            continue

        is_comment = s.startswith("/*") or s.startswith("//") or s == "*" or s.startswith("* ") or s.startswith("*/")
        if waiting_for_code and s != "" and not is_comment:
            result.append(MARKER)
            waiting_for_code = False

        result.append(line)

    return "\n".join(result) + "\n"

"""for comment removal, Remove /* ... */ and // comments while keeping string literals safe."""
def strip_comments(code):
    result = []
    i = 0
    length = len(code)

    while i < length:
        ch = code[i]

        # for Skip over string or character literals so we don't break "//" inside quotes
        if ch == '"' or ch == "'":
            j = i + 1
            while j < length and code[j] != ch:
                if code[j] == "\\":
                    j = j + 1
                j = j + 1
            result.append(code[i:j + 1])
            i = j + 1

        # for Handle /* ... */ and // comments
        elif code[i:i + 2] == "/*" or code[i:i + 2] == "//":
            if code[i:i + 2] == "/*":
                end_pos = code.find("*/", i + 2)
                end = length if end_pos == -1 else end_pos + 2
            else:
                end_pos = code.find("\n", i)
                end = length if end_pos == -1 else end_pos

            # to Check if the comment was alone on its own line
            current_text = "".join(result)
            line_start = current_text.rfind("\n") + 1
            next_newline = code.find("\n", end)
            rest_of_line = code[end:length if next_newline == -1 else next_newline]

            if current_text[line_start:].strip() == "" and rest_of_line.strip() == "":
                result = [current_text[:line_start]]
                i = length if next_newline == -1 else next_newline + 1
            else:
                result.append(" ")
                i = end
        else:
            result.append(ch)
            i = i + 1

    return "".join(result)

 """Remove comments, hide bad/good/CWE names, and clean extra blank lines."""
def clean_code(code):
    code = strip_comments(code)

    # to Replace bad/good/CWE identifiers in order of appearance with func1, func2...
    word_map = {}
    matches = list(re.finditer(r"\b\w*(?:bad|good|cwe\d+)\w*\b", code, flags=re.IGNORECASE))
    pieces = []
    last_idx = 0

    for m in matches:
        word = m.group(0)
        if word not in word_map:
            word_map[word] = "func" + str(len(word_map) + 1)
        pieces.append(code[last_idx:m.start()])
        pieces.append(word_map[word])
        last_idx = m.end()

    pieces.append(code[last_idx:])
    code = "".join(pieces)

    # to Strip trailing spaces and keep max 1 blank line between blocks (same as original)
    trimmed_lines = []
    for line in code.splitlines():
        trimmed_lines.append(line.rstrip())
    code = "\n".join(trimmed_lines)
    code = re.sub(r"\n\s*\n+", "\n\n", code).strip() + "\n"
    return code


def extract_line_numbers(code):
    """Remove MARKER lines and save exact flaw line numbers."""
    final_lines = []
    flaw_lines = []

    for line in code.split("\n"):
        if line.strip() == MARKER:
            flaw_lines.append(len(final_lines) + 1)
        else:
            final_lines.append(line)

    return "\n".join(final_lines), flaw_lines


# ---------------- main ----------------
if not os.path.isdir(NIST_PATH):
    print("error: cannot find", NIST_PATH)
    raise SystemExit(1)

all_pairs = {}

for cwe in CWES:
    cwe_name = "CWE" + cwe
    all_pairs[cwe_name] = []
    search_pattern = os.path.join(NIST_PATH, cwe_name + "_*", "**", "*.c*")
    paths = sorted(glob.glob(search_pattern, recursive=True))

    found = 0
    skipped = 0

    for path in paths:
        filename = os.path.basename(path)
        m = re.match(r"^CWE(\d+)_.*_(\d{2})\.(c|cpp)$", filename)
        if not m or m.group(1) != cwe or m.group(2) not in VARIANTS:
            continue

        found = found + 1
        with open(path, encoding="utf-8", errors="replace") as f:
            original = f.read()

        # to Process bad and good versions
        bad_code = get_version(original, "bad")
        bad_code = put_flaw_marker(bad_code)
        bad_code = clean_code(bad_code)
        bad_code, flaws = extract_line_numbers(bad_code)

        good_code = get_version(original, "good")
        good_code = clean_code(good_code)
        good_code, _ = extract_line_numbers(good_code)

        # to Make sure both versions still contain functions and at least one flaw line
        has_bad_func = re.search(r"\)\s*\{", bad_code) is not None
        has_good_func = re.search(r"\)\s*\{", good_code) is not None
        if not (has_bad_func and has_good_func and len(flaws) > 0):
            skipped = skipped + 1
            continue

        all_pairs[cwe_name].append({
            "path": os.path.relpath(path, os.path.dirname(NIST_PATH)),
            "variant": m.group(2),
            "ext": "." + m.group(3),
            "bad": bad_code,
            "good": good_code,
            "flaws": flaws,
        })

    print(f"{cwe_name}: {found} files found, {len(all_pairs[cwe_name])} usable pairs, {skipped} skipped")

# to Sample 25 pairs per CWE (or all 20 for CWE476)
rng = random.Random(SEED)
chosen = []
print()

for cwe in CWES:
    cwe_name = "CWE" + cwe
    k = min(PAIRS_PER_CWE, len(all_pairs[cwe_name]))
    sampled = rng.sample(all_pairs[cwe_name], k)
    for p in sampled:
        chosen.append((cwe_name, "bad", p))
        chosen.append((cwe_name, "good", p))
    print(f"{cwe_name}: sampled {k} pairs")

rng.shuffle(chosen)

# to  Write cleaned files and labels.csv
files_dir = os.path.join(OUT_DIR, "files")
if os.path.isdir(files_dir):
    shutil.rmtree(files_dir)
os.makedirs(files_dir)

leaks = 0
labels_path = os.path.join(OUT_DIR, "labels.csv")

with open(labels_path, "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["id", "file", "cwe", "label", "variant", "flaw_lines", "original_path"])

    idx = 1
    for cwe_name, label, p in chosen:
        name = f"sample_{idx:04d}{p['ext']}"
        code = p[label]

        if re.search(r"bad|good|cwe\d", code, re.I):
            leaks = leaks + 1

        with open(os.path.join(files_dir, name), "w", encoding="utf-8") as dst:
            dst.write(code)

        flaw_lines = ""
        if label == "bad":
            flaw_lines = ";".join([str(x) for x in p["flaws"]])

        writer.writerow([idx, name, cwe_name, label, p["variant"], flaw_lines, p["path"]])
        idx = idx + 1

print()
print("Wrote", len(chosen), "cleaned files to", files_dir + "/")
print("Answers saved in", labels_path)
print("Files still containing bad/good/CWE words:", leaks)
