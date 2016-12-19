import os
import sys

filename = sys.argv[1]
from_id = int(sys.argv[2])
to_id = int(sys.argv[2])

for i in range(from_id, to_id + 1):
    sys.system("mv {0}.in{1} {0}{1}.in".format(filename, i))
    sys.system("mv {0}.out{1} {0}{1}.out".format(filename, i))
