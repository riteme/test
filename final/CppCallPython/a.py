#
# Copyright 2015 riteme
#

import ctypes

share = ctypes.CDLL("libshare.so")

def hello_world():
    print 'Hello, world!'

def ask(question):
    answer = raw_input(question + ' ')
    return answer

def set_a(num):
    share.set(num)
