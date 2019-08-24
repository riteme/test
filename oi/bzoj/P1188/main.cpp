/**
 * 分为两个游戏，组合起来即可~~~
 */

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 21
#define SMAX (1 << NMAX)

static int n;
static int P[NMAX + 10];
static int sg[NMAX + 10];
static bool mex[SMAX + 10];
static int current;

static void evaluate_sg() {
    sg[n - 1] = 0;
    
    for (int i = n - 2; i >= 0; i--) {
        memset(mex, 0, sizeof(mex));

        for (int j = i + 1; j < n; j++) {
            for (int k = j; k < n; k++) {
                int v = sg[j] ^ sg[k];
                mex[v] = true;
            }
        }

        sg[i] = 0;

        while (mex[sg[i]]) {
            sg[i]++;
        }
    }
}

inline int move(int i, int j, int k) {
    return current ^ sg[i] ^ sg[j] ^ sg[k];
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", P + i);
    }
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();
        evaluate_sg();

        current = 0;
        for (int i = 0; i < n; i++) {
            if (P[i] & 1)
                current ^= sg[i];
        }


        int ai = -1, aj = -1, ak = -1;
        int cnt = 0;
        if (current) {
            for (int i = 0; i < n - 1; i++) {
                for (int j = i + 1; j < n; j++) {
                    for (int k = j; k < n; k++) {
                        int v = move(i, j, k);

                        if (!v) {
                            cnt++;

                            if (ai < 0) {
                                ai = i;
                                aj = j;
                                ak = k;
                            }
                        }
                    }
                }
            }
        }

        printf("%d %d %d\n", ai, aj, ak);
        printf("%d\n", cnt);
    }

    return 0;
}
