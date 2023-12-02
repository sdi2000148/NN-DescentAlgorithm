import subprocess
import os

# create csv file
filename = 'results.csv'

if os.path.exists(filename):
    print(f"File '{filename}' already exists")
    exit(0)

with open(filename, 'w') as file:
    file.write('Type,Dataset,N,k,Recall,Metric,p,d,Time\n')

# run multiple experiments
subprocess.run(['make'])

args = [[1, 'Datasets/00000020.bin', 'l2', 10, 0.1, 0.001, 'Solutions/20-k10.txt']]
times = 1

for type, dataset, metric, k, p, d, solution in args:
    subprocess.run(['./main', str(type), dataset, metric, str(k), str(p), str(d), solution, filename])

subprocess.run(['make', 'clean'])

