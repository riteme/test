import os
from random import randint

def sh(x):
    assert not os.system(x)

cnt = 0
while True:
    cnt += 1
    print(cnt)

    n = 10
    R = randint(1, n - 1)
    with open('data.in', 'w') as f:
        f.write(f'{n} {R}\n')
        f.write(' '.join(str(randint(1, 100)) for i in range(n - 1)))
    sh('./a.out < data.in > data.out')
    sh('python3 std.py < data.in > data.ans')
    sh('diff -Bb data.out data.ans')
