#!/usr/bin/env pypy

import path

P = []

P += path.generate_horizontal((0, 0), (10**8, 0), 2, 0)
P += path.generate_horizontal((10**8, 5 * 10**7), (0, 5 * 10**7), 10**6 - 10, 4 * 10**7)

print("\n".join(
    ["%s %s" % p for p in P]
))
