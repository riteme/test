#!/usr/bin/python3

# Based on code written by Google Code Jam
#
# This is a small program that runs two processes, connecting the
# stdin of each one to the stdout of the other.
# It doesn't perform a lot of checking, so many errors may
# be caught internally by Python (e.g., if your command line has incorrect
# syntax) or not caught at all (e.g., if the judge or solution hangs).
#
# Run this as:
# python interactive_runner.py <cmd_line_judge> -- <cmd_line_solution>
#
# For example:
# python interactive_runner.py python testing_tool.py 0 -- ./my_binaRy
#
# this will run the first test set of a python judge called "testing_tool.py"
# that receives the test set number (starting from 0) via command line parameter
# with a solution compiled into a binary called "my_binary".
#
# This is only intended as a convenient tool to help contestants test solutions
# locally. In particular, it is not identical to the implementation on our
# server, which is more complex.

from __future__ import print_function
import sys, subprocess, threading, time, os, signal

class SubprocessThread(threading.Thread):
  def __init__(self,
               args,
               stdin_pipe=subprocess.PIPE,
               stdout_pipe=subprocess.PIPE,
               stderr_pipe=subprocess.PIPE):
    threading.Thread.__init__(self, daemon=True)
    self.p = subprocess.Popen(
        args,
        stdin=stdin_pipe,
        stdout=stdout_pipe,
        stderr=stderr_pipe)

  def run(self):
    try:
      self.return_code = self.p.wait()
      self.stdout = "" if self.p.stdout is None else self.p.stdout.read()
      self.stderr = "" if self.p.stderr is None else self.p.stderr.read()
    except (SystemError, OSError):
      self.return_code = -1
      self.stdout = ""
      self.stderr = "The process crashed or produced too much output."

assert sys.argv.count("--") == 1, (
    "There should be exactly one instance of '--' in the command line.")
sep_index = sys.argv.index("--")
judge_args = sys.argv[1:sep_index]
sol_args = sys.argv[sep_index + 1:]

C_FLAGS = '-O2 -w'
CXX_FLAGS = '-O2 -std=c++11 -w'

def C_CXX_Compile(strs):
  compile = ''
  exec = strs
  if '.cpp' == strs[0][-4:]:
    compile = 'g++ ' + CXX_FLAGS + ' ' + strs[0] + ' -o ' + strs[0][:-4]
    exec = ['./' + strs[0][:-4]] + strs[1:]
  elif '.c' == strs[0][-2:]:
    compile = 'gcc ' + C_FLAGS + ' ' + strs[0] + ' -o ' + strs[0][:-2]
    exec = ['./' + strs[0][:-2]] + strs[1:]
  #print(compile, exec)
  if compile != '':
    print('compiling', strs[0], '...')
    proc = subprocess.Popen(compile, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, bufsize=-1)
    _, err = proc.communicate()
  else:
    err = b''
  return exec, str(err, encoding='utf8')

judge_args, judge_err = C_CXX_Compile(judge_args)
sol_args, sol_err = C_CXX_Compile(sol_args)

if judge_err != '' or sol_err != '':
  print('Compile Error:')
  if judge_err != '':
    print(judge_err)
  if sol_err != '':
    print(sol_err)
  exit()

t_sol = SubprocessThread(sol_args)
t_judge = SubprocessThread(judge_args, stdin_pipe=t_sol.p.stdout,
                           stdout_pipe=t_sol.p.stdin)
t_sol.start()
t_judge.start()
#t_sol.join()
#t_judge.join()
starttime = time.time()
while True:
  if not t_judge.isAlive():
    usetime = time.time() - starttime
    time.sleep(0.5)
    judge_code = '-'
    judge_text = '-'
    sol_code = '-'
    sol_text = '-'
    try:
      judge_code = t_judge.return_code
      if 'stderr' in dir(t_judge): judge_text = t_judge.stderr.decode()
      else: judge_text = '+'
      if judge_text == '': judge_text = '-'
      if 'return_code' in dir(t_sol):
        sol_code = t_sol.return_code
        if 'stderr' in dir(t_sol): sol_text = t_sol.stderr.decode()
        else: sol_text = '+'
      else:
        sol_code = -1
        sol_text = 'Still running'
      if sol_text == '': sol_text = '-'
    except Exception as e:
      print("Error occured when getting results.", e)
    print("Judge return code:      ", judge_code)
    print("Judge standard error:   ", judge_text)
    print("Solution return code:   ", sol_code)
    print("Solution standard error:", sol_text)
    print("Use time: %.2f" % usetime)
    break
  if time.time() - starttime > 10:
    print("Time Limit Excedeed")
    t_judge.p.kill()
    t_sol.p.kill()
    #os.killpg(t_judge.p.pid, signal.SIGUSR1)
    #os.killpg(t_sol.p.pid, signal.SIGUSR1)
    exit()
  time.sleep(0.01)
