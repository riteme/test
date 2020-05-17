import re
import numpy as np

# A = 10007
# B = 18980504
# MOD = 998244353

# with open('small.cpp', 'r') as fp:
    # graph_line = fp.readlines()[7:3006]
with open('large.cpp', 'r') as fp:
    graph_line = fp.readlines()[12:3011]

reg = r'void f([0-9]{1,4})\(\)\{f([0-9]{1,4})\(\);f([0-9]{1,4})\(\);\}'
m = re.compile(reg)

def take(M, k):
    return np.diag(np.diag(M, k), k)

O = np.ones((64, 64), dtype=np.int64)
I = np.identity(64, dtype=np.int64)
L13 = take(O, -13)
R7 = take(O, 7)
L17 = take(O, -17)
T = (I + L13)
T = (I + R7) @ T
T = (I + L17) @ T

T0 = np.zeros((128, 128), dtype=np.int64)
T1 = np.zeros((128, 128), dtype=np.int64)
T0[0:64, 0:64] = I
T0[0:64, 64:128] = T
T0[64:128, 64:128] = T
T1[0:64, 0:64] = I
T1[64:128, 64:128] = T

# dp = [
#     np.array([
#         [A, 0],
#         [0, 1]
#     ]),
#     np.array([
#         [1, B],
#         [0, 1]
#     ])
# ]

dp = [T0, T1]
for line in graph_line:
    ret = m.match(line)
    assert ret is not None
    x, u, v = map(int, ret.groups())
    assert x == len(dp)
    dp.append((dp[v] @ dp[u]) & 1)

R = dp[-1]

def bits(x):
    v = list(map(int, reversed(bin(x)[2:])))
    return v + [0] * (64 - len(v))

v = np.hstack((np.zeros((64), dtype=np.int64), np.array(bits(233), dtype=np.int64))).reshape(-1, 1)
# print(v)

u = ((R @ v) & 1).flatten()
print(list(u))