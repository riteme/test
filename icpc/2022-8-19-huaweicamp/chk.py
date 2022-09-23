import os
import random

def sh(x):
    print(f'# {x}')
    assert not os.system(x)

sh('g++ D.cpp -g -fsanitize=undefined -Wall -Wextra -o a.out')
sh('g++ D2.cpp  -g -fsanitize=undefined -Wall -Wextra -o b.out')

cnt = 0
while True:
    cnt += 1
    print(cnt)
    n = 6
    m = 10
    with open('D0.in', 'w') as f:
        f.write(f'{n}\n')
        f.write(' '.join(str(random.randint(1, m)) for i in range(n)))
        f.write('\n')
    sh('./a.out < D0.in > D0.out')
    sh('./b.out < D0.in > D0.ans')
    sh('diff D0.out D0.ans')
