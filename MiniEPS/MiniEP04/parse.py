import re
import numpy as np

Executions = []
Execution = {'sched': None, 'n_th': None, 'n_ac': None, 'sync': None, 'bakery': None, 'gate': None}

File = open("test.txt")
for line in File:
    sched = re.findall(r'SCHEDULER: (.+)', line)
    n_th = re.findall(r'THREADS: (.+)', line)
    n_ac = re.findall(r'ACCESS: (.+)', line)
    sync = re.findall(r'SYNC: (.+)', line)

    if sched != []:
        Execution.update({'sched': sched[0]})

    if n_th != []:
        Execution.update({'n_th': n_th[0]})

    if n_ac != []:
        Execution.update({'n_ac': n_ac[0]})

    if sync != []:
        Execution.update({'sync': sync[0]})

    if (Execution['sched'] != None and Execution['n_th'] != None and
            Execution['n_ac'] != None and Execution['sync'] != None):

        for i in range (0, 2):

            elp_times = np.array([])
            avg_times = np.array([])
            std_times = np.array([])

            for j in range(0, 240):
                line_j = File.readline();
                aux = re.findall(r'.+: (.+), .+: (\d+)', line_j)
                if aux != []:
                    algorithm = aux[0][0]

                elapsed_time = re.findall(r'\): (\d+)', line_j)
                average_time = re.findall(r'Average of accesses: (.+)', line_j)
                std_time = re.findall(r'Standard Deviation of accesses: (.+)', line_j)

                if (elapsed_time != []):
                    elapsed_time = float(elapsed_time[0])
                    elp_times = np.append(elp_times, elapsed_time)

                if (average_time != []):
                    average_time = float(average_time[0])
                    avg_times = np.append(avg_times, average_time)

                if (std_time != []):
                    std_time = float(std_time[0])
                    std_times = np.append(std_times, std_time)

            times = {'elapsed_time': {'avg': np.mean(elp_times), 'std': np.std(std_times)},
                     'average_time': {'avg': np.mean(avg_times), 'std': np.std(std_times)},
                     'standard_deviation': {'avg': np.mean(std_times), 'std': np.std(std_times)}}

            Execution.update({algorithm: times})


        Executions.append(Execution)
        Execution = {'sched': None, 'n_th': None, 'n_ac': None, 'sync': None, 'bakery': None, 'gate': None}

for test in Executions:
    print(test)
