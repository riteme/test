#!/usr/bin/python3

import os, sys, subprocess

C_FLAGS = '-O2 -w'
CXX_FLAGS = '-O2 -std=c++11 -w'

def C_CXX_Compile(string):
  compile = ''
  exec = [string]
  if '.cpp' == string[-4:]:
    compile = 'g++ ' + CXX_FLAGS + ' ' + string + ' -o ' + string[:-4]
    exec = ['./' + string[:-4]]
  elif '.c' == string[-2:]:
    compile = 'gcc ' + C_FLAGS + ' ' + string + ' -o ' + string[:-2]
    exec = ['./' + string[:-2]]
  #print(compile, exec)
  if compile != '':
    print('compiling', string, '...')
    proc = subprocess.Popen(compile, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, bufsize=-1)
    _, err = proc.communicate()
  else:
    err = b''
  return exec, str(err, encoding='utf8')

argv = sys.argv
if len(argv) != 4:
    print(
'''Error: arguments number error, need 3 arguments.
Run as: python3 test_all.py [DATA_FOLDER] [JUDGER_CODE/JUDGER_BIN] [SOLVER_CODE/SOLVER_BIN]
Example: python3 test_all.py data judger.cpp solver.exe'''
    )
    exit()

judger, judger_err = C_CXX_Compile(argv[2])
solver, solver_err = C_CXX_Compile(argv[3])

if judger_err != '' or solver_err != '':
    print('Compile Error:')
    if judger_err != '':
        print(judger_err)
    if solver_err != '':
        print(solver_err)
    exit()

datafolder = argv[1]
inputs = os.listdir(datafolder)
inputs.sort(key = lambda x:int(x[:-3]))

results = []

for input in inputs:
    input_full = os.path.join(datafolder, input)
    print('start testing', input_full)
    command = ['python3', 'interactive_runner.py'] + judger + [input_full, '--'] + solver
    command = ' '.join(command)
    #print(command)
    res = os.popen(command).read()
    jcode = -1
    scode = -1
    jres = ''
    score = -1
    for line in res.split('\n'):
        if line == 'Time Limit Excedeed':
            jres = 'Time Limit Excedeed'
        elif line[:25] == 'Judge return code:       ':
            jcode = int(line[25:])
        elif line[:25] == 'Judge standard error:    ':
            jres = line[25:]
            if jcode == 0 and line[25:39] == 'Passed! Asks: ':
                score = int(line[39:])
        elif line[:25] == 'Solution return code:    ':
            scode = int(line[25:])
            break
    results.append([jcode, jres, scode, score, input[:-3]])

print('Results:')
print('\n'.join(['|'.join(x) for x in [[str(z) for z in y] for y in results]]))
