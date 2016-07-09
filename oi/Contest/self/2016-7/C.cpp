#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

int mod = 2333, day;

//=============================================================Matrix=============================================================
struct matrix {
    int a, b, c, d;
    friend matrix operator*(matrix p, matrix q) {
        matrix m;
        m.a = (p.a * q.a + p.b * q.c) % mod;
        m.b = (p.a * q.b + p.b * q.d) % mod;
        m.c = (p.c * q.a + p.d * q.c) % mod;
        m.d = (p.c * q.b + p.d * q.d) % mod;
        return m;
    }
};

matrix basic, ok;

matrix quick_pow(int p) {
    if (p == 1)
        return basic;
    if (p == 0) {
        matrix tmp;
        tmp.a = 1, tmp.b = 0, tmp.c = 0, tmp.d = 1;
        return tmp;
    }

    matrix tmp = quick_pow(p / 2);
    if (p % 2 == 0)
        tmp = tmp * tmp;
    else
        tmp = tmp * tmp * basic;

    return tmp;
}

void init() {
    basic.a = 0, basic.b = 2, basic.c = 1, basic.d = 3;
    ok = quick_pow(day - 1);
}

int ask(int f1, int f2) {
    return (f1 * ok.a + f2 * ok.c) % mod;
}

void dp(int f1, int f2) {
    int i, f[1005] = { 0 };
    f[1] = f1, f[2] = f2;
    for (i = 3; i <= day; i++)
        f[i] = (2 * f[i - 2] + 3 * f[i - 1]) % mod;
    printf("Boom:F[%d]=%d\n", day, f[day]);
}
//=============================================================Matrix=============================================================

int n;
vector<int> son[500005];
int w[500005] = { 0 };
bool reach[500005] = { 0 };

void inp() {
    int i, ta, tb;
    scanf("%d%d", &n, &day);
    init();

    for (i = 1; i <= n; i++)
        scanf("%d%d", &ta, &tb), w[i] = ask(ta, tb);
    for (i = 1; i < n; i++)
        scanf("%d%d", &ta, &tb), son[ta].push_back(tb), son[tb].push_back(ta);
}

int o[500005] = { 0 };

int dfs(int x) {
    // printf("dfs %d\n",x);
    reach[x] = 1;

    int i, max = 0, tmp, sec = 0;
    vector<int> v;
    if (son[x].size() == 1 && reach[son[x][0]])  // leaf
    {
        o[x] = w[x];
        return w[x];
    }

    for (i = 0; i < son[x].size(); i++)
        if (!reach[son[x][i]])
            v.push_back(dfs(son[x][i]));

    for (i = 0; i < v.size(); i++)
        if (v[i] > v[max])
            max = i;
    tmp = v[max], v[max] = 0, max = tmp;

    for (i = 0; i < v.size(); i++)
        if (v[i] > v[sec])
            sec = i;
    sec = v[sec];

    // printf("dfs[%d]:max=%d sec=%d o[]=%d\n",x,max,sec,max+sec+w[x]);
    o[x] = max + sec + w[x];

    // if(son[x].size()==2)        //Single son
    //    return max;

    return max + w[x];
}

void out() {
    int i, max = 0;
    for (i = 1; i <= n; i++)
        if (o[i] > max)
            max = o[i];

    printf("%d\n", max);
}

int main(void) {
    inp();
    dfs(1);
    out();
    for (int i = 1; i <= n; i++) {
        printf("w[%d] = %d\n", i, w[i]);
    }  // for
}
