from os import *

def sh(x):
    assert not system(x)

sh("g++ F.cpp -O3")

cnt = 0
while True:
    cnt += 1
    print(cnt)
    sh("python3 F-gen.py > F.in")
    sh("./a.out < F.in > F.out")
