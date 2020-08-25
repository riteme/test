#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <cassert>

#include <vector>
#include <algorithm>
#include <tr1/unordered_map>
//#include <map>

using namespace std;

#define NMAX 5000
#define KMAX 40
#define TMAX 50000
#define LMAX 2000000
#define EPS 1e-8

typedef long long i64;
typedef vector<int> vi;
typedef tr1::unordered_map<i64, int> mp_t;
//typedef map<i64, int> mp_t;
typedef pair<int, int> pi;

bool mark[LMAX + 10];
int pcnt;
i64 pr[LMAX + 10];
mp_t idx;
i64 op[TMAX + 10];
vector<pi> D[NMAX + 10];

bool cmp(int a, int b) {
    return a > b;
}

i64 encode(vi &v) {
    i64 rax = 1;
    sort(v.begin(), v.end(), cmp);
    for (int i = 0; i < v.size(); i++)
    for (int j = 0; j < v[i]; j++) {
        rax *= pr[i];
    }
    return rax;
}

void inc(const vi &u, vi &v) {
    v[0]++;
    for (int i = 0; i < u.size(); i++) {
        if (v[i] > u[i]) {
            v[i + 1]++;
            v[i] = 0;
        }
    }
}

vi sub(vi u, const vi &v) {
    for (int i = 0; i < u.size(); i++) {
        u[i] -= v[i];
    }
    return u;
}

i64 get(vi v) {
    i64 key = encode(v);

    if (idx.count(key))
        return idx[key];

    int u = idx.size() + 1;
    idx[key] = u;
    assert(u <= NMAX);

    int cnt = 1;
    for (int i = 0; i < v.size(); i++) {
        cnt *= v[i] + 1;
    }

    vi z;
    z.resize(v.size());
    for (int i = 1; i < cnt - 1; i++) {
        inc(v, z);
        int a = get(z);
        int b = get(sub(v, z));
        D[u].push_back(pi(a, b));
    }

    return u;
}

double f[KMAX + 10][NMAX + 10];
bool ok[KMAX + 10][NMAX + 10];

double dp(int k, int x) {
    if (k <= 1)
        return 1;
    if (ok[k][x])
        return f[k][x];

    double &rax = f[k][x];
    rax = 0;
    for (int i = 0; i < D[x].size(); i++) {
        int a = D[x][i].first, b = D[x][i].second;
        double ap = dp(k - 1, a);
        double bp = dp(k - 1, b);
        rax += 1 - (1 - ap) * (1 - bp);
    }

    if (D[x].size())
        rax /= D[x].size();

    ok[k][x] = true;
    return rax;
}

vi factor(i64 n) {
    vi v;
    for (int i = 0; pr[i] * pr[i] <= n; i++) {
        int c = 0;
        while (n % pr[i] == 0) {
            n /= pr[i];
            c++;
        }

        if (c)
            v.push_back(c);
    }

    if (n > 1)
        v.push_back(1);

    return v;
}

void _main() {
    i64 n;
    scanf("%lld", &n);
    vi v = factor(n);
    int x = get(v);

    double ans = 0;
    for (int k = 1; k < KMAX; k++) {
        double ret = dp(k, x);
        ans += ret;
        //if (ret < EPS)
        //    break;
    }

    printf("%.6lf\n", ans);
}

int main() {
    for (i64 i = 2; i <= LMAX; i++) {
        if (!mark[i])
            pr[pcnt++] = i;
        for (int j = 0; i * pr[j] <= LMAX; j++) {
            mark[i * pr[j]] = true;
            if (i % pr[j] == 0)
                break;
        }
    }

    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        printf("Case #%d: ", i);
        _main();
    }

    return 0;
}
