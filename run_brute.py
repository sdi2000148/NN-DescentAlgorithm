import subprocess
import os

results_dir = 'BruteResults/'
dataset_dir = 'Datasets/'
solution_dir = 'Solutions/'

if not os.path.exists(dataset_dir):
    print(f"Directory '{dataset_dir}' does not exist!")
    exit(0)

args = []
outputs = []
files_list = os.listdir(dataset_dir)
for file in files_list:
    part1, separator, part2 = file.rpartition('.')
    if part2 == 'bin':
        type = 1
    elif part2 == 'ascii':
        continue
    output_path = results_dir + part1 + '.csv'
    for k in [100]:
        solution_path = solution_dir + part1 + '-' + str(k) + '.txt'
        if os.path.exists(solution_path):
            print(f"The file '{solution_path}' already exists.")
            continue
        if output_path not in outputs:
            outputs.append(output_path)
        for metric in ['l2']:
            args += [[output_path, type, dataset_dir+file, solution_path, k, metric]]

if args == []:
    print('Nothing to run. Exiting.')
    exit(0)

if not os.path.exists(results_dir):
    os.makedirs(results_dir)
    print(f"Directory '{results_dir}' created successfully.")
else:
    print(f"Directory '{results_dir}' already exists.")

if not os.path.exists(solution_dir):
    os.makedirs(solution_dir)
    print(f"Directory '{solution_dir}' created successfully.")
else:
    print(f"Directory '{solution_dir}' already exists.")

for output in outputs:
    with open(output, 'w') as file:
        file.write('Type,Dataset,N,k,Metric,Time\n')

# run multiple experiments
subprocess.run(['make', 'brute'])

for output, type, dataset, solution, k, metric in args:
    print('./brute', str(type), dataset, metric, str(k), solution, output)
    subprocess.run(['./brute', str(type), dataset, metric, str(k), solution, output])

subprocess.run(['make', 'clean-brute'])





