#!/usr/bin/env python3

import os
import sys

if len(sys.argv) < 2:
    print("Usage: %s [N]" % sys.argv[0])
    exit(-1)

n = int(sys.argv[1])
os.system("./datagen.py %s > landlords.in" % n)
os.system("cat landlords.in")
os.system("./a.out < landlords.in")
