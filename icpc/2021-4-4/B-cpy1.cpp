#include <cstdio>
#include <cassert>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

constexpr int DMAX = 10;
constexpr int SMAX = 1 << DMAX;
constexpr int INF = 0x3f3f3f3f;

int f[SMAX][SMAX];
struct {
    int s, t;
} g[SMAX][SMAX];

int n, K, A;
char s[100];

int main() {
    scanf("%d%d", &K, &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        for (int j = 0; j < K; j++) {
            if (s[j] == '1')
                A |= 1 << j;
        }
    }

    memset(f, 0x3f, sizeof(f));
    f[0][0] = 0;
    for (int S = 0; S < (1 << K); S++)
    for (int T = 0; T < (1 << K); T++) {
        if (f[S | T][0] > f[S][T] + 1) {
            f[S | T][0] = f[S][T] + 1;
            g[S | T][0] = {S, T};
        }

        for (int i = 0; i < K; i++) {
            int nT = T | (1 << i);
            if (f[S][nT] > f[S][T] + 1) {
                f[S][nT] = f[S][T] + 1;
                g[S][nT] = {S, T};
            }
        }
    };

    int ans = INF, s, t;
    for (int S = 0; S < (1 << K); S++)
    for (int T = 0; T < (1 << K); T++) {
        if ((A & (S | T)) == A && ans > f[S][T]) {
            ans = f[S][T];
            s = S;
            t = T;
        }
    };

    vector<char> stk;
    while (s != 0 || t != 0) {
        int ns, nt;
        ns = g[s][t].s;
        nt = g[s][t].t;

        if (t == 0)
            stk.push_back('R');
        else {
            int a = t ^ nt;

            bool found = false;
            for (int i = 0; i < K; i++) {
                if (a == (1 << i)) {
                    stk.push_back('0' + i);
                    found = true;
                    break;
                }
            }

            assert(found);
        }

        s = ns;
        t = nt;
    }

    printf("%d\n", ans);
    for (int i = stk.size() - 1; i >= 0; i--) {
        printf("%c ", stk[i]);
    }
    puts("");

    return 0;
}