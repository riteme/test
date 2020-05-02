#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define SIZE 1000003
#define SMAX 4000000

struct Data {
    int key, t0, t1;
};

int cnt;
Data mem[SMAX];
vector<int> buc[SIZE];

bool is_new;
int get(int key) {
    int pos = key % SIZE;
    is_new = false;
    for (int i : buc[pos])
        if (mem[i].key == key)
            return i;

    is_new = true;
    cnt++;
    mem[cnt].key = key;
    buc[pos].push_back(cnt);
    return cnt;
}

#define NMAX 100
#define MOD 998244353
#define INC 0x1041041  // 0b000001...

int n, m, L, P;
int to[SMAX][2];
char s[NMAX + 10];

#define inc(p) (INC >> (6 * (5 - (p))));
#define take(x, i) (((x) >> (6 * ((i) - 1))) & 0x3f)
#define reset(x, i) ((x) & ~(0x3fu << (6 * ((i) - 1))))

void fuck(int x, int p) {
    int i = get(x);
    if (!is_new)
        return;

    int x0 = x + inc(p);
    if (p && take(x0, p) >= L) {
        x0 = reset(x0, p);
        fuck(x0, p - 1);
    } else
        fuck(x0, p);

    int x1 = x + inc(p);
    if (p && take(x1, p) > L) {
        x1 = reset(x1, p);
        p--;
    }
    if (p < P) {
        if (p && take(x1, p) >= L) {
            x1 = reset(x1, p);
            p--;
        }
        x1 = (x1 << 6) + 1;
        fuck(x1, p + 1);
    } else {
        x1 = -1;
    }

    mem[i].t0 = x0;
    mem[i].t1 = x1;
}

int f[SMAX], g[SMAX];

void add(int &a, int b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}

int main() {
    scanf("%d%d%d%s", &n, &L, &P, s + 1);
    fuck(0, 0);
    for (int i = 1; i <= cnt; i++) {
        to[i][0] = mem[i].t0 >= 0 ? get(mem[i].t0) : 0;
        to[i][1] = mem[i].t1 >= 0 ? get(mem[i].t1) : 0;
    }
    m = cnt;

    g[get(0)] = 1;
    for (int i = 1; i <= n; i++) {
        memset(f + 1, 0, sizeof(int) * m);
        if (s[i] == '0') {
            for (int j = 1; j <= m; j++)
                add(f[to[j][0]], g[j]);
        } else {
            for (int j = 1; j <= m; j++) {
                add(f[to[j][0]], g[j]);
                add(f[to[j][1]], g[j]);
            }
        }

        memcpy(g + 1, f + 1, sizeof(int) * m);
        g[0] = 0;
    }

    int ans = 0;
    for (int i = 1; i <= m; i++)
        add(ans, g[i]);
    printf("%d\n", ans);

    // fprintf(stderr, "m = %d\n", m);
    return 0;
}