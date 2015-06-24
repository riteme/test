#
# Copyright 2015 riteme
#

from multiprocessing import *
import os

def proc(name):
    print 'Running child process \"' + name +'\", pid:', os.getpid()

if __name__ == "__main__":
    print 'Parent process is', os.getpid()
    new_proc = Process(target = proc, args = ('A',))
    print 'Process will start'
    new_proc.start()
    new_proc.join()
    print 'Process end'
