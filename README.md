# C/C++ Vulnerability detection using Local AI Models

**Course:** T-742-CSDA- Computer security defence against dark art.

**Student Name:** Poonam Vikram Kadam

## Versions v2
- CSDA_juliet-llm-vuln-detection_v2.zip: cleaner version with some corrections in the notebook. Results are same.

  
This project tests how well 3 local language models (LLMs) can find security vulneraboility in C/C++ code. For each file model verifies :
- The file is vulnerable?
- Which type of vulnerability it is? (CWE)
- On which line vulnerability is?
- suggested Fix for vulnerability?

## Inventory
 This all LLM models runs on laptop with Ollama, So code runs in secure and isolated environment (your own laptop). 
 - Python 3.13.3 version 
 - Complelet run perform on : MacBook Pro M3, 16 GB & Ollama

## LLM models we used are:
1. codellama:7b 
2. deepseek-coder:6.7b
3. qwen2.5-coder:7b 

## Dataset
The test files come from the official NIST Juliet C/C++ 1.3 test suite.
We selected total 290 files for our pipeline validatation. Out of 290 we selected 145 good files and 145 bad files. 
For dataset cover we targated total 6 vulnerabilities. The vulnerabilities are Test files are came from the official NIST Juliet C/C++ 1.3 test suit : We selected total 290 files out of which 145 good and 145 vulnerable files. We are covering total 6 CWEs (CWE-78, 121, 122, 190, 416, 476).
url: https://samate.nist.gov/SARD/test-suites/112

## Install Package

python3 -m venv venv
source venv/bin/activate
pip install pandas matplotlib notebook

Test files are came from the official NIST Juliet C/C++ 1.3 test suit : We selected total 290 files out of which 145 good and 145 vulnerable files. We are covering total 6 CWEs (CWE-78, 121, 122, 190, 416, 476).
## Project and files structure 
```
├── README.md               # provides the instructions for how to execute project 
├── dataset_sampling.py  # step 1: use to build total 290 (145 good+ 145 bad) test files, clean and the answer from the NIST Juliet and generates the "labels.csv" 
├── prompt_builder.py              # step 2: add numbers to the code lines , build prompt and sends each file to a model in Ollama and saves the answers
├── evaluate.py             # step 3: compares the "labels.csv"  and ".jsonl file. Count TP, FP, FN and TN to verify accuracy, recall, precision, false alarm & specificity.  
├── analysis.ipynb          # step 4: Single jupyter notebook file to just open and check complete form of report. 
└── data/llm_sample/
    ├── files/              # the 290 test files given to the models (sample_0001.c ...)
    ├── labels.csv          # answer key: vulnerable or safe, CWE, flaw line(s) for each file
    ├── results/            # the logs: every model answer, one JSON line per file
    │   ├── deepseek-coder_6.7b.jsonl
    │   ├── codellama_7b.jsonl
    │   └── qwen2.5-coder_7b.jsonl
    └── evaluation/         # output of evaluate.py and analysis.ipynb (CSV tables formats and PNG figures)
```

## To reproduce the result:

1. Download ZIP file and unzip it. 

2. Open Terminal in that folder:
```bash
cd ~/Downloads/CSDA_juliet-llm-vuln-detection-main
```
(If you use the v2 zip, the folder is called `juliet-llm-vuln-detection` instead.)
3. Install the packages:
```bash
python3 -m venv venv
source venv/bin/activate
pip install pandas matplotlib notebook
```

4. Run the evaluation:
```bash
python evaluate.py --sample data/llm_sample
```

5. Open the notebook, then click **Run → Run All Cells**:
```bash
JULIET_SAMPLE=data/llm_sample jupyter notebook analysis.ipynb
```
