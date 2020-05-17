from random import *

S = 'abcdef'
print(''.join(choice(S) for i in range(1000000)))