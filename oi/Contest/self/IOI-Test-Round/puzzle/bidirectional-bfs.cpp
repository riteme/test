// #define NDEBUG

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

#define NMAX 10
#define ONE ((map_t)1)

typedef __uint128_t map_t;

namespace std {

template <>
struct hash<map_t> {
    size_t operator()(const map_t &a) const {
        return a;
    }
};  // struct hash<map_t>

}  // namespace std

enum BlockType {
    UNKNOWN = 0,
    RIGHT,
    DOWN,
};  // enum BlockType

static int n, m;
static int S[NMAX][NMAX], T[NMAX][NMAX];

inline map_t encode(int a[NMAX][NMAX]) {
    map_t ret = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == DOWN)
                ret |= ONE << (i * m + j);
        }  // for
    }      // for

    return ret;
}

inline void decode(map_t s, int a[NMAX][NMAX]) {
    memset(a, 0, sizeof(int) * NMAX * NMAX);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++, s >>= 1) {
            if (s & 1)
                a[i][j] = DOWN;
            else if ((i == 0 || a[i - 1][j] != DOWN) &&
                     (j == 0 || a[i][j - 1] != RIGHT))
                a[i][j] = RIGHT;
        }  // for
    }      // for
}

void read_data(int a[NMAX][NMAX]) {
    static char buf[NMAX];

    memset(a, 0, sizeof(int) * NMAX * NMAX);
    for (int i = 0; i < n; i++) {
        scanf("%s", buf);

        for (int j = 0; j < m; j++) {
            if (buf[j] == '$' && (i == 0 || a[i - 1][j] != DOWN))
                a[i][j] = DOWN;
            if (buf[j] == '#' && (j == 0 || a[i][j - 1] != RIGHT))
                a[i][j] = RIGHT;
        }  // for
    }      // for
}

struct Info {
    Info() {}
    Info(map_t _father, int _x, int _y) : father(_father), x(_x), y(_y) {}

    map_t father;
    int x, y;
};  // struct Info

static map_t s, t;
static queue<map_t> q[2];
static unordered_map<map_t, Info> r[2];
static int mat[NMAX][NMAX];
static vector<Info> op;

void finish(map_t u) {
    auto pos = op.size();

    for (map_t x = u; x != s; x = r[0][x].father) {
        op.push_back(r[0][x]);
    }  // for

    reverse(op.begin() + pos, op.end());

    for (map_t x = u; x != t; x = r[1][x].father) {
        op.push_back(r[1][x]);
    }  // for

    printf("%zu\n", op.size());
    for (auto &e : op) {
        printf("%d %d\n", e.x + 1, e.y + 1);
    }  // foreach in op
}

inline bool rotatable(int x, int y, int a[NMAX][NMAX]) {
    return !(a[x][y] == UNKNOWN ||
             (a[x][y] == RIGHT && a[x][y] != a[x + 1][y]) ||
             (a[x][y] == DOWN && a[x][y] != a[x][y + 1]));
}

bool expand(int i) {
    map_t u = q[i].front();
    q[i].pop();
    decode(u, mat);

    for (int x = 0; x < n - 1; x++) {
        for (int y = 0; y < m - 1; y++) {
            if (!rotatable(x, y, mat))
                continue;

            map_t v = u;
            if (mat[x][y] == RIGHT) {
                v |= ONE << (x * m + y);
                v |= ONE << (x * m + y + 1);
            } else {
                v ^= ONE << (x * m + y);
                v ^= ONE << (x * m + y + 1);
            }

            if (r[i].count(v))
                continue;

            r[i][v] = Info(u, x, y);

            if (r[i ^ 1].count(v)) {
                finish(v);
                return true;
            } else
                q[i].push(v);
        }  // for
    }      // for

    return false;
}

void greedy() {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            if (rotatable(x, y, S) && rotatable(x, y, T) &&
                S[x][y] != T[x][y]) {
                op.push_back(Info(0, x, y));

                if (S[x][y] == RIGHT) {
                    S[x][y] = S[x][y + 1] = DOWN;
                    S[x + 1][y] = UNKNOWN;
                } else {
                    S[x][y] = S[x + 1][y] = RIGHT;
                    S[x][y + 1] = UNKNOWN;
                }
            }
        }  // for
    }      // for
}

void bfs() {
    s = encode(S), t = encode(T);
    q[0] = queue<map_t>(), q[1] = queue<map_t>();
    r[0].clear(), r[1].clear();
    q[0].push(s);
    q[1].push(t);
    r[0][s] = r[1][t] = Info();

    while (!expand(r[0].size() < r[1].size() ? 0 : 1))
        ;
}

void solve() {
    op.clear();
    greedy();
    bfs();
}

int main() {
    // freopen("data.in", "r", stdin);

    int t, _;
    scanf("%d%d%d%d", &t, &n, &m, &_);
    read_data(S);

    for (int i = 1; i <= t; i++) {
        fprintf(stderr, "(info) Processing testcase #%d...\n", i);
        read_data(T);
        solve();
        memcpy(S, T, sizeof(S));
        fprintf(stderr, "(info) Finished testcase #%d!\n", i);
    }  // for

    return 0;
}
