#
# Copyright 2015 riteme
#

class A(object):
    def __init__(self):
        self._num = 0

    @property
    def number(self):
        return self._num

    @number.setter
    def number(self, value):
        if not isinstance(value, int):
            raise ValueError('Value must be int.')
        else:
            self._num = value

a = A()
print a.number
a.number = 1
print a.number
a.number = 's'
