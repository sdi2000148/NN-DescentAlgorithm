import subprocess
import os

# create csv file
results_dir = 'NNResults/'
dataset_dir = 'Datasets/'
solution_dir = 'Solutions/'

# preparing arguments list
args = []
outputs = []
files_list = os.listdir(dataset_dir)
for file in files_list:
    part1, separator, part2 = file.rpartition('.')
    if part2 == 'bin':
        type = 1
    elif part2 == 'ascii':
        continue
    for k in [100]:
        for p in [0.2, 0.4, 1]:
            for d in [0.001]:
                for metric in ['l2']:
                    temp = solution_dir + part1 + '-' + str(k) + '.txt'
                    output = part1 + '.csv'
                    if output not in outputs:
                        outputs.append(output)
                    args += [[output, type, dataset_dir+file, temp, k, p, d, metric]]


if not os.path.exists(results_dir):
    os.makedirs(results_dir)
    print(f"Directory '{results_dir}' created successfully.")
else:
    print(f"Directory '{results_dir}' already exists.")

for output in outputs:
    filename = results_dir + output
    with open(filename, 'w') as file:
        file.write('Type,Dataset,N,k,Recall,Metric,p,d,Time\n')

# run multiple experiments
subprocess.run(['make', 'nn'])

for filename, type, dataset, solution, k, p, d, metric in args:
    print('./nn', str(type), dataset, metric, str(k), str(p), str(d), solution, results_dir+filename)
    subprocess.run(['./nn', str(type), dataset, metric, str(k), str(p), str(d), solution, results_dir+filename])

subprocess.run(['make', 'clean-nn'])

