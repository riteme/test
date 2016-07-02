#!/usr/bin/env pypy

import sys

from random import *

N = 100000
no_not = False
no_brackets = False
only_or = False

if "--no-not" in sys.argv:
    no_not = True
if "--no-brackets" in sys.argv:
    no_brackets = True
if "--only-or" in sys.argv:
    only_or = True
if "-n100" in sys.argv:
    N = 100

def random_name():
    rlen = randint(1, 4)
    return "".join([chr(randint(ord("a"), ord("z"))) for i in range(0, rlen)])

def random_not():
    return "!" * randint(0, 2)

def random_op():
    global only_or

    if only_or:
        return "|"
    OP = ["&", "|", "^"]
    return choice(OP)

def generate():
    global N
    global only_or
    global no_not
    global no_brackets

    if only_or:
        N = randint(10000, 100000)

    cnt = N
    names = set()
    while len(names) < N * 3:
        names.add(random_name())
    names = list(names)
    L = names[:N - 1]

    brackets_number = randint(1, int(N / 2))

    if not no_brackets:
        for cnt in range(0, brackets_number):
            x = randrange(0, len(L) - 5)
            y = randrange(x + 2, len(L))
            L.insert(x, "(")
            L.insert(y, ")")

    S = []
    i = 0
    while i < len(L):
        if L[i] == "(" and L[i + 1] == ")":
            S.append("(")
            S.append(names[cnt])
            S.append(")")
            cnt += 1
            i += 2
        else:
            S.append(L[i])
            i += 1

    for i in range(0, len(S)):
        if not no_not:
            if i > 0 and S[i] != ")":
                S[i] = random_not() + S[i]

        if i < len(S) - 1 and not S[i].endswith("(") and not S[i + 1].endswith(")"):
            S[i] = S[i] + random_op()

    print("".join(S))

generate()
generate()
generate()
