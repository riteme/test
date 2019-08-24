#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

#define NMAX 200000
#define FORBID (n + 1)

typedef long long i64;

struct Edge {
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

    int u, v, w;

    int either(int x) {
        return u == x ? v : u;
    }
};  // struct Edge

static int n;
static vector<Edge *> G[NMAX + 10];
static unordered_map<i64, int> data;

void initialize() {
    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);

        Edge *e = new Edge(u, v, c);
        G[u].push_back(e);
        G[v].push_back(e);
    }  // for
}

inline i64 id(int x, int nxt) {
    return (static_cast<i64>(x) << 32) + nxt;
}

int dp(int x, int nxt, int father) {
    i64 pos = id(x, nxt);
    if (data.count(pos))
        return data[pos];

    int &answer = data[pos];
    int d1 = INT_MIN, d2 = INT_MIN;
    int p1 = 0, p2 = 0;
    int fd1 = INT_MIN, fd2 = INT_MIN;
    int fp1 = 0, fp2 = 0;
    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (v == father)
            continue;
        if (v == nxt) {
            answer += dp(v, FORBID, x) + e->w;
            continue;
        }

        int maxp = 0;
        for (size_t j = 0; j < G[v].size(); j++) {
            Edge *e2 = G[v][j];
            int p = e2->either(v);

            if (p == x)
                continue;
            if (maxp == 0 || dp(v, p, x) > dp(v, maxp, x))
                maxp = p;
        }  // for

        int ret = max(dp(v, 0, x), maxp ? dp(v, maxp, x) + e->w : 0);

        if (!nxt) {
            int d = dp(v, 0, x) + e->w - ret;
            int fd = dp(v, FORBID, x) + e->w - ret;

            if (d > d1) {
                d2 = d1, p2 = p1;
                d1 = d, p1 = v;
            } else if (d > d2)
                d2 = d, p2 = v;

            if (fd > fd1) {
                fd2 = fd1, fp2 = fp1;
                fd1 = fd, fp1 = v;
            } else if (fd > fd2)
                fd2 = fd, fp2 = v;
        }

        answer += ret;
    }  // for

    if (p1 && fp1) {
        if (p1 != fp1 && d1 + fd1 > 0)
            answer += d1 + fd1;
        else {
            int a = max(fp2 ? d1 + fd2 : -1, p2 ? d2 + fd1 : -1);

            if (a > 0)
                answer += a;
        }
    }

    return answer;
}

int main() {
    initialize();

    printf("%d\n", dp(1, 0, 0));

    return 0;
}  // function main
