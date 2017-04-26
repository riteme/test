// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define BASE 2333
#define MOD 1000000009
#define NMAX 30

typedef long long i64;
typedef unsigned long long u64;

class HashTable {
 public:
    typedef pair<u64, int> Data;

    static const int size = 2399993;

    vector<Data> bucket[size];

    void insert(u64 key) {
        int pos = key % size;

        for (size_t i = 0; i < bucket[pos].size(); i++) {
            if (bucket[pos][i].first == key) {
                bucket[pos][i].second++;

                if (bucket[pos][i].second == MOD)
                    bucket[pos][i].second = 0;

                return;
            }
        }

        bucket[pos].push_back(make_pair(key, 1));
    }
};

static int n, m;
static u64 tpow[NMAX * 2 + 10];
static char mat[NMAX + 10][NMAX + 10];
static HashTable tb;

void dfs(int sx, int sy, int tx, int ty, int len, u64 code) {
    code += mat[sx][sy] * tpow[len];

    if (sx == tx && sy == ty) {
        tb.insert(code);
        return;
    }

    const int dx[] = {-1,  1,  0,  0,  1,  1, -1, -1};
    const int dy[] = { 0,  0, -1,  1,  1, -1,  1, -1};
    for (size_t p = 0; p < 8; p++) {
        int nx = sx + dx[p];
        int ny = sy + dy[p];

        if (nx < 1 || nx > n || ny < 1 || ny > m ||
            abs(nx - tx) > abs(sx - tx) ||
            abs(ny - ty) > abs(sy - ty))
            continue;

        dfs(nx, ny, tx, ty, len + 1, code);
    }
}

void initialize() {
    tpow[0] = 1;
    for (int i = 1; i <= NMAX * 2; i++) {
        tpow[i] = tpow[i - 1] * BASE;
    }

    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%s", &mat[i][1]);
    }
}

int main() {
#ifdef NDEBUG
    freopen("makina.in", "r", stdin);
    freopen("makina.out", "w", stdout);
#endif
    initialize();

    for (int sx = 1; sx <= n; sx++) {
        for (int sy = 1; sy <= m; sy++) {
            for (int tx = 1; tx <= n; tx++) {
                for (int ty = 1; ty <= m; ty++) {
                    if (sx != tx || sy != ty)
                        dfs(sx, sy, tx, ty, 0, 0);
                }
            }
        }
    }

    i64 answer = 0;
    for (size_t i = 0; i < tb.size; i++) {
        for (size_t j = 0; j < tb.bucket[i].size(); j++) {
            HashTable::Data &d = tb.bucket[i][j];
            answer = (answer + d.second * d.second) % MOD;
        }
    }

    printf("%lld\n", answer);

    return 0;
}
