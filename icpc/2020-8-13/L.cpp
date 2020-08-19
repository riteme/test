#include <cstdio>
#include <cstring>
#include <climits>

#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 2000
#define INF 1000000010

struct inc {
    inc() : x(0), v(0) {}
    inc(int _x, int _v) : x(_x), v(_v) {}

    int x, v;

    bool operator<(const inc &z) const {
        return x < z.x || (x == z.x && v > z.v);
    }
};

typedef deque<inc> fn;

int n;
int L[NMAX + 10], R[NMAX + 10];
vector<int> G[NMAX + 10];

int get_max(const fn &z) {
    int s = 0, mx = 0;
    for (int i = 0; i < z.size(); i++) {
        s += z[i].v;

        if (i + 1 == z.size() || z[i].x < z[i + 1].x)
            mx = max(mx, s);
    }
    return mx;
}

void print(int x, const fn &z) {
    printf("[%d] ", x);
    int s = 0;
    for (int i = 0; i < z.size(); i++) {
        s += z[i].v;
        printf("%d:%+d ", z[i].x, z[i].v);
        if (i + 1 == z.size() || z[i + 1].x > z[i].x)
            printf("(%d) ", s);
    }
    puts("");
}

fn dp(int x, int pa) {
    fn rax;
    for (int i = 0; i < G[x].size(); i++) {
        int v = G[x][i];
        if (v == pa)
            continue;

        fn ret = dp(v, x);

        int mx = get_max(ret);

        ret.push_front(inc(ret[0].x, +1));
        ret.push_back(inc(ret[ret.size() - 1].x, -1));

        int sum = 0, ls, rs;
        int lp = -1, rp = -1;
        if (!ret.empty()) {
            if (ret[0].x > L[x]) {
                lp = 0;
                ls = 0;
            }
            if (ret[0].x > R[x]) {
                rp = 0;
                rs = 0;
            }
        }
        for (int i = 0; i < ret.size(); i++) {
            sum += ret[i].v;

            if (lp < 0 && (i + 1 == ret.size() || ret[i + 1].x > L[x])) {
                lp = i + 1;
                ls = sum;
            }
            if (rp < 0 && (i + 1 == ret.size() || ret[i + 1].x > R[x])) {
                rp = i + 1;
                rs = sum;
            }
        }

        rax.push_back(inc(L[x], +max(ls, mx)));
        sum = ls;
        for (int i = lp; i < rp; i++) {
            inc z = ret[i];
            int pre = sum;
            sum += z.v;
            if (pre < mx && sum < mx)
                continue;

            z.v = max(sum, mx) - max(pre, mx);
            rax.push_back(z);
        }
        rax.push_back(inc(R[x] + 1, -max(rs, mx)));
    }

    rax.push_front(inc(L[x], 0));
    rax.push_back(inc(R[x] + 1, 0));
    sort(rax.begin(), rax.end());

    //print(x, rax);
    return rax;
}

void _main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        G[i].clear();
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d%d", L + i, R + i);
    }

    fn ret = dp(0, 0);
    int ans = n - get_max(ret);
    printf("%d\n", ans);
}

int main() {
    G[0].push_back(1);
    L[0] = R[0] = 0;

    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}
