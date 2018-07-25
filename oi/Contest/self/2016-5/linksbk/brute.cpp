#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define COLORMAX 200000
#define COLORINDEXMAX 1000000

static int color[NMAX + 10];
static int _cnt;
static int _hash[COLORINDEXMAX + 10];

inline int colorhash(int x) {
    if (_hash[x] == 0)
        _hash[x] = ++_cnt;

    return _hash[x];
}

typedef bitset<COLORMAX + 10> ColorMap;

static int n, m;
static vector<int> G[NMAX + 10];
static int in[NMAX + 10];
static int out[NMAX + 10];
static int colordata[NMAX + 10];
static int timestamp;

static void dfs(int x) {
    in[x] = ++timestamp;

    for (unsigned i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (in[v] == 0) {
            dfs(v);
        }
    }  // for

    out[x] = timestamp;
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        int c;
        scanf("%d", &c);

        colordata[i] = colorhash(c);
    }  // for

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }  // for

    scanf("%d", &m);

    dfs(1);
    for (int i = 1; i <= n; i++) {
        color[in[i]] = colordata[i];
    }  // for
}

struct Data {
    int colors[COLORMAX + 10];
    int answer = 0;
};  // struct Data

static void brute(Data &data, int s, int t) {
    memset(data.colors, 0, sizeof(data.colors));
    data.answer = 0;

    for (int j = s; j <= t; j++) {
        int c = color[j];

        if (data.colors[c] == 0) {
            data.answer++;
        }
        data.colors[c]++;
    }  // for
}

static void move(Data &data, int fx, int fy, int tx, int ty) {
    if (fx < tx) {
        for (; fx < tx; fx++) {
            data.colors[color[fx]]--;

            if (data.colors[color[fx]] == 0) {
                data.answer--;
            }
        }  // for
    } else if (fx > tx) {
        for (fx--; fx >= tx; fx--) {
            if (data.colors[color[fx]] == 0) {
                data.answer++;
            }

            data.colors[color[fx]]++;
        }  // for
    }

    if (fy < ty) {
        for (fy++; fy <= ty; fy++) {
            if (data.colors[color[fy]] == 0) {
                data.answer++;
            }

            data.colors[color[fy]]++;
        }  // for
    } else if (fy > ty) {
        for (; fy > ty; fy--) {
            data.colors[color[fy]]--;

            if (data.colors[color[fy]] == 0) {
                data.answer--;
            }
        }  // for
    }
}

inline int cost(int fx, int fy, int tx, int ty) {
    return abs(fx - tx) + abs(fy - ty);
}

int main() {
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    initialize();

    Data last;
    int lx = 0, ly = 0;
    for (int i = 0; i < m; i++) {
        int command;
        scanf("%d", &command);

        if (command == 0) {
            int u, c;
            scanf("%d%d", &u, &c);

            u = in[u];
            c = colorhash(c);

            if (lx <= u && u <= ly) {
                if (last.colors[c] == 0) {
                    last.answer++;
                }

                last.colors[color[u]]--;
                last.colors[c]++;

                if (last.colors[color[u]] == 0) {
                    last.answer--;
                }
            }

            color[u] = c;
        } else {  // 1
            int u;
            scanf("%d", &u);

            int s = in[u], t = out[u];
            if (cost(lx, ly, s, t) > t - s + 1) {
                brute(last, s, t);
            } else {
                move(last, lx, ly, s, t);
            }

            lx = s;
            ly = t;

            printf("%d\n", last.answer);
        }
    }  // for

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
