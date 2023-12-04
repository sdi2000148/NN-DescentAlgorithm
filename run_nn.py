import subprocess
import os

results_dir = 'NNResults/'
dataset_dir = 'Datasets/'
solution_dir = 'Solutions/'

if not os.path.exists(dataset_dir):
    print(f"Directory '{dataset_dir}' does not exist!")
    exit(0)

if not os.path.exists(solution_dir):
    print(f"Directory '{solution_dir}' does not exist!")
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
    if os.path.exists(output_path):
        print(f"The file '{output_path}' already exists.")
        continue
    outputs.append(output_path)
    for k in [100]:
        solution_path = solution_dir + part1 + '-' + str(k) + '.txt'
        for p in [0.2, 0.4, 1]:
            for d in [0.001]:
                for metric in ['l2']:
                    args += [[output_path, type, dataset_dir+file, solution_path, k, p, d, metric]]

if args == []:
    print('All experiments already conducted. Exiting.')
    exit(0)

if not os.path.exists(results_dir):
    os.makedirs(results_dir)
    print(f"Directory '{results_dir}' created successfully.")
else:
    print(f"Directory '{results_dir}' already exists.")

for output in outputs:
    with open(output, 'w') as file:
        file.write('Type,Dataset,N,k,Recall,Metric,p,d,Time\n')

# run multiple experiments
subprocess.run(['make', 'nn'])

for output, type, dataset, solution, k, p, d, metric in args:
    print('./nn', str(type), dataset, metric, str(k), str(p), str(d), solution, output)
    subprocess.run(['./nn', str(type), dataset, metric, str(k), str(p), str(d), solution, output])

subprocess.run(['make', 'clean-nn'])

