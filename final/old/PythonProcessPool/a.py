#
# Copyright 2015 riteme
#

from multiprocessing import *
import os, time, random

def proc(proc_id, sleep_time):
    print 'Process %s (%s) is running...' % (proc_id, os.getpid())
    start = time.time()
    time.sleep(sleep_time)
    end = time.time()
    print 'Process %s (%s) ended in %s.' % (proc_id, os.getpid(), (end - start))

if __name__ == '__main__':
    print 'Parent process pid: %s' % os.getpid()
    proc_pool = Pool()
    for i in range(1, 11):
        proc_pool.apply_async(proc, args=(i, random.randrange(500, 5001) / 1000.0))
    print 'Parent process is waiting.'
    proc_pool.close()
    proc_pool.join()
    print 'All subprocess finished.'
