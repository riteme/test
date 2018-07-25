#!/usr/bin/env python3

import os
import sys

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: {} [DOT FILE]".format(sys.argv[0]))
        exit(1)

    status = os.system("dot -Tsvg {} -o /tmp/showdot.tmp.svg".format(sys.argv[1]))

    if not os.path.exists("/tmp/showdot.tmp.svg"):
        print("Can't process dot script.")
        exit(-1)

    os.system("eog /tmp/showdot.tmp.svg")
    
    try:
        os.remove("/tmp/showdot.tmp.svg")
    except:
        pass
