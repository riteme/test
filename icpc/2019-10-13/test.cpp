#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100

typedef long long i64;

int n, K;
i64 r0[NMAX], r1[NMAX];

i64 pw(i64 i, i64 k) {
    return (1 << k) + i - 1;
}

void print() {
    printf("[K = %d]\n", K);
    for (int i = 1; i <= n; i++)
        printf("%3d ", i);
    puts(" i");
    for (int i = 1; i <= n; i++)
        printf("%3lld ", r0[i] % 1000);
    puts(" r(i)");
    for (int i = 1; i <= n; i++)
        printf("%3lld ", r1[i] % 1000);
    puts(" r'(i)");
    i64 lp = 0;
    for (int i = 1; i <= n; i++) {
        printf(r1[i] != lp ? "  * " : "    ");
        lp = r1[i];
    }
    puts("");
}

void update() {
    i64 mi = 1 << K;
    for (int i = n; i; i--) {
        r1[i] = mi;
        mi = min(mi, r0[i] - i + 1);
    }
}

int main(int argc, char *argv[]) {
    n = atoi(argv[1]);
    for (int i = 0; i < NMAX; i++)
        r0[i] = pw(i, 0);
    update();
    print();
    char buf[64];
    while (scanf("%64s", buf) != EOF) {
        if (buf[0] == 'r') {  // reset
            int i;
            scanf("%d", &i);
            for (int j = i; j && r0[j] > i; j--)
                r0[j] = i;
        } else {  // next
            for (int i = 1; i < NMAX; i++) {
                int j = r0[i] + 1;
                if (j < NMAX) r0[i] = r0[j];
                else r0[i] = pw(j, K);
            }
            K++;
        }
        update();
        print();
    }
    return 0;
}
