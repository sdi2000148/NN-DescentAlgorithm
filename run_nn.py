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
    output_path = results_dir + part1 + '.csv'
    if os.path.exists(output_path):
        print(f"The file '{output_path}' already exists.")
        continue
    outputs.append(output_path)
    for k in [100]:
        solution_path = solution_dir + part1 + '-' + str(k) + '.txt'
        for p in [0.1]:
            for d in [0.001]:
                for metric in ['l2']:
                    args += [[output_path, dataset_dir+file, solution_path, k, p, d, metric]]

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
        file.write('Dataset,N,k,Recall,Metric,p,d,Thread_count,Time\n')

times = 1

# run multiple experiments
subprocess.run(['make', 'nn'])

for output, dataset, solution, k, p, d, metric in args:
    for thread_count in range(0,3):
        for i in range(0, times):
            print('./nn', dataset, metric, str(k), str(p), str(d), str(pow(2, thread_count)), solution, output)
            subprocess.run(['./nn', dataset, metric, str(k), str(p), str(d), str(pow(2, thread_count)), solution, output])

subprocess.run(['make', 'clean-nn'])

