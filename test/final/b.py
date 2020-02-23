#!/usr/bin/env python3

import re
import os
import os.path
import time
import random

HISTORY = '.bash_history'

W = []
user_home=os.path.expanduser('~')
history = open(os.path.join(user_home, '.bash_history'), 'r')

for line in history:
    W.append(line[0 : len(line) - 2])

history.close()

while True:
    print(W[random.randrange(0, len(W))])
    time.sleep(0.05)

print('Aborted.')
