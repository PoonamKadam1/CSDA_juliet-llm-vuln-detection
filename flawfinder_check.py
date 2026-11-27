# flawfinder_check.py 
# This script checks Flawfinder's results against our labels.csv file. 
#  rule for check: If Flawfinder finds any warning, we say the file is vulnerable.

import csv
import math

folder = "/Volumes/Seagate/juliet_data/llm_sample"

# ---  Read Flawfinder results ---
# We  want to know which files Flawfinder found  issue.
flawfinder_hits = []

file_path = folder + "/evaluation/flawfinder_clean.csv"
with open(file_path, "r") as f:
    reader = csv.reader(f)
    header = next(reader)
    file_index = header.index("File")
    
    for row in reader:
        # Get just the file name (e.g. sample_0002.c)
        name = row[file_index].split("/")[-1]
        
        # If we haven't seen this file yet, add it to our list.
        if name not in flawfinder_hits:
            flawfinder_hits.append(name)

# --- Compare with the correct answers initialzation to 0 ---
tp = 0
fp = 0
fn = 0
tn = 0

labels_path = folder + "/labels.csv"
with open(labels_path, "r") as f:
    reader = csv.reader(f)
    header = next(reader)
    file_index = header.index("file")
    label_index = header.index("label")
    
    for row in reader:
        name = row[file_index]
        label = row[label_index]
        
        # is Flawfinder find something in this file?
        if name in flawfinder_hits:
            if label == "bad":
                tp = tp + 1  # True +ve
            else:
                fp = fp + 1  # False alarm
        else:
            if label == "bad":
                fn = fn + 1  # False -ve (Missed)
            else:
                tn = tn + 1  # True -ve

# ---  Print the results and metrics ---
print("Flawfinder Results:")
print("  TP =", tp, " FP =", fp, " FN =", fn, " TN =", tn)

# Calculate basic metrics
accuracy = (tp + tn) / 290 * 100
recall = tp / (tp + fn) * 100
false_alarm = fp / (fp + tn) * 100

# To Calculate MCC 
denominator = math.sqrt((tp + fp) * (tp + fn) * (tn + fp) * (tn + fn))

if denominator == 0:
    mcc = 0
else:
    mcc = (tp * tn - fp * fn) / denominator

print("  Accuracy    =", round(accuracy, 1), "%")
print("  Recall      =", round(recall, 1), "%")
print("  False alarm =", round(false_alarm, 1), "%")
print("  MCC         =", round(mcc, 3))
