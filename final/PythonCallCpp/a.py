#
# Copyright 2015 riteme
#

import ctypes

so = ctypes.CDLL('./liba.so')
so.say_hello('riteme')
print so.add(1, 2)

so.add_to_i(3)
print so.get_i()
