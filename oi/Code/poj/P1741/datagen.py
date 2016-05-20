from random import choice, randint

N = 10000
K = 233333333
CMAX = 1000

L = []
T = [1]
# for i in range(1, N):
#     v = i + 1
#     f = choice(T)
#     L.append("{} {} {}".format(f, v, randint(1, CMAX)))
#     T.append(v)
for i in range(1, N):
    L.append("{} {} 100".format(i, i + 1))

with open("data.in", "w") as file:
    file.write("{} {}\n".format(N, K))
    file.write("\n".join(L))
    file.write("\n0 0\n")
