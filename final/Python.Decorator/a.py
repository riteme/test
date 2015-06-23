#
# Copyright 2015 riteme
#

import functools

def log(info):
    def decorator(func):
        @functools.wraps(func)
        def wapper(*args, **kw):
            print '{0} {1}()'.format(info, func.__name__)
            return func(*args, **kw)
        return wapper
    return decorator

@log('call')
def add(a, b):
    return a + b

print add(1, 2)
