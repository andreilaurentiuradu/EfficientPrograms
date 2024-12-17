import os
import json
import sys

imp_name = sys.argv[1]
req_m = None
if len(sys.argv) > 2:
    req_m = sys.argv[2] 


dirnames = []
for filename in os.listdir("benchmarks/"):
    if imp_name in filename:
        dirnames += [filename]
metrics = {}
dirnames.sort()
most_recent = dirnames[-1]

#parsing all the values
for filename in os.listdir(f"benchmarks/{most_recent}"):
    with open(f'benchmarks/{most_recent}/{filename}') as f:
        metrics[filename] = {}
        for i in f.readlines():
            try:
                d = json.loads(i)
                metrics[filename][d['event']] = d
            except Exception as e:
                pass

print(f"{'Test Name':<40} {'Metric':<15} {'Value':>15}")
print("=" * 80)
if req_m == None:
    for key in metrics.keys():
        print(f"{key:<40} {'cpu-cycles':<15} {metrics[key]['cpu-cycles']['counter-value']:>15}")
else:
    for m_name in req_m.split(','):
        for key in metrics.keys():
            print(f"{key:<40} {m_name:<15} {metrics[key][m_name]['counter-value']:>15}")        