#include <stdio.h>
#include <algorithm>
#include <math.h>

#define ll long long
#define vi vector <int>
#define vc vector <complex>
#define pb push_back
#define mod 1000000007

using namespace std;

struct complex {
    double x , y;
    complex ():x(0),y(0){}
    complex (const double &_x,const double &_y):x(_x),y(_y){}
};
inline complex operator + (const complex &a ,const complex &b) {return complex(a.x+b.x,a.y+b.y);}
inline complex operator - (const complex &a ,const complex &b) {return complex(a.x-b.x,a.y-b.y);}
inline complex operator * (const complex &a ,const complex &b) {return complex(a.x*b.x-a.y*b.y,a.y*b.x+a.x*b.y);}
inline complex conj ( const complex &a ) {return complex (a.x,-a.y);}

const double pi = acos ( -1 );

inline int add(int a, int b) {
    a += b;
    return (a < mod) ? a : (a - mod);
}
inline int sub(int a, int b) {
    a -= b;
    return (a < 0) ? a + mod : a;
}
inline int mul(int a, int b) {
    return (ll)a * b % mod;
}
int power(int a, int b) {
    if (!b) return 1;
    int u = power(a, b >> 1);
    u = mul(u, u);
    if (b & 1) u = mul(u, a);
    return u;
}
vi rev;
vc w;
int mx = -1;
void init( int m ) {
    mx = m;
    int N = (1<<m);
    w.resize ( N );
    for ( int i = 0 ; i < N ; i++ ) w[i] = complex (cos(2*pi*i/N),sin(2*pi*i/N));
}
void calr(int m) {
    rev.resize(1 << m);
    if (mx < m) init(m);
    rev[0] = 0;
    for (int j = 0; j < m; j++)
        for (int k = 0; k < (1 << j); k++)
            rev[k | (1 << j)] = rev[k] + (1 << (m - j - 1));
}
void dft(vc& a) {
    int n = a.size(), r = 0; // 保证 a 是 2 幂
    while ((1 << r) < n) r++;
    calr(r);
    for (int i = 0; i < n; i++)
        if (rev[i] > i)
            swap(a[rev[i]], a[i]);
    for (int i = 1,lyc=(1<<(mx-1)); i < n; i <<= 1,lyc>>=1) {
        for (int j = 0; j < n; j += (i << 1)) {
            for (int k = 0,now=0; k < i; k++) {
                complex mr = a[i + j + k]*w[now];
                a[i + j + k] = a[j + k]-mr;
                a[j + k] = a[j + k]+mr;
                now += lyc;
            }
        }
    }
}
vi operator * (vi a, vi b) {
    int l = a.size() + b.size() - 1 , N;
    if ((ll)a.size() * b.size() < 100) {
        vi fn(a.size() + b.size() - 1);
        for (int i = 0; i < a.size(); i++)
            for (int j = 0; j < b.size(); j++)
                fn[i + j] = add(fn[i + j], mul(a[i], b[j]));
        return fn;
    }
    int i , r = 0;
    while ((1 << r) < l) r++;
    N = 1<<r;
    a.resize(N), b.resize(N);

    for ( i = 0 ; i < N ; i++ ) (a[i] += mod) %= mod, (b[i] += mod) %= mod;
    static vc x , y;
    static vc dfta , dftb , dftc , dftd;
    x.resize(N);y.resize(N);
    dfta.resize(N);dftb.resize(N);dftc.resize(N);dftd.resize(N);
    complex zeros = complex();
    for (int i = 0;i < N;i++) {
        x[i]=zeros;
        y[i] = zeros;
        dfta[i] = zeros;
        dftb[i] = zeros;
        dftc[i] = zeros;
        dftd[i] = zeros;
    }

    for(i=0;i<N;i++) x[i] = complex(a[i] & 32767, a[i] >> 15);
    for(i=0;i<N;i++) y[i] = complex(b[i] & 32767, b[i] >> 15);
    dft(x); dft(y);
    for(i=0;i<N;i++) {
        int j = (N - i) & (N - 1);
        static complex da, db, dc, dd;
        da = (x[i] + conj(x[j])) * complex(0.5, 0);
        db = (x[i] - conj(x[j])) * complex(0, -0.5);
        dc = (y[i] + conj(y[j])) * complex(0.5, 0);
        dd = (y[i] - conj(y[j])) * complex(0, -0.5);
        dfta[j] = da * dc;
        dftb[j] = da * dd;
        dftc[j] = db * dc;
        dftd[j] = db * dd;
    }
    for(i=0;i<N;i++) x[i] = dfta[i] + dftb[i] * complex(0, 1);
    for(i=0;i<N;i++) y[i] = dftc[i] + dftd[i] * complex(0, 1);
    dft(x); dft(y);
    for(i=0;i<N;i++)
    {
        int da = (ll)(x[i].x / N + 0.5) % mod;
        int db = (ll)(x[i].y / N + 0.5) % mod;
        int dc = (ll)(y[i].x / N + 0.5) % mod;
        int dd = (ll)(y[i].y / N + 0.5) % mod;
        a[i] = (da + ((ll)(db + dc) << 15) + ((ll)dd << 30)) % mod;
    }

    x.clear();
    x.shrink_to_fit();
    y.clear();
    y.shrink_to_fit();
    dfta.clear();
    dfta.shrink_to_fit();
    dftb.clear();
    dftb.shrink_to_fit();
    dftc.clear();
    dftc.shrink_to_fit();
    dftd.clear();
    dftd.shrink_to_fit();

    a.resize(l);
    for ( i = 0 ; i < l ; i++ )
        if ( a[i] < 0 ) a[i] += mod;
    return a;
}
vi inv(vi a) {
    int n = a.size() , r=0;
    vi g(1) , h;
    while ((1 << r) < n) r++;
    a.resize ( 1<<r );
    g[0] = power ( a[0] , mod - 2 );
    for ( int i = 2 ; i <= (1<<r) ; i = i * 2 ) {
        h.resize ( i );
        for ( int j = 0 ; j < i ; j++ ) h[j] = a[j];
        h = g * (g*h); g.resize ( i );
        for ( int j = 0 ; j < i ; j++ )
            g[j] = sub ( mul (g[j],2),h[j]);
    }
    g.resize (n);
    for ( int i = 0 ; i < n ; i++ )
        if ( g[i] < 0 ) g[i] += mod;
    return g;
}

#include <cstdio>
#include <cstring>

#include <stack>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

typedef long long i64;
#define NMAX 400000
#define MOD 1000000007
const i64 INV2 = ((MOD + 1) / 2);

i64 minv(i64 x) {
    return x == 1 ? 1 : MOD - MOD / x * minv(MOD % x) % MOD;
}

struct edge {
    int v, nxt;
};

int n, m, cnt;
vector<int> G[NMAX + 1], T[NMAX + 1];

struct Pair {
    Pair() : u(0), v(0) {}
    Pair(int _u, int _v) : u(_u), v(_v) {}

    int u, v;
};

vector<Pair> stk;
//bool marked[NMAX + 1];
bitset<NMAX+1> marked;
int in[NMAX + 1], low[NMAX + 1], cur;

void reset() {
    stk.clear();
    stk.shrink_to_fit();
    //memset(marked + 1, 0, (n + cnt));
    marked.reset();
    memset(in + 1, 0, sizeof(int) * (n + cnt));
    memset(low + 1, 0, sizeof(int) * (n + cnt));
    cur = 0;
    for (int i = 1; i <= n + cnt; i++) {
        G[i].clear();
        T[i].clear();
        G[i].shrink_to_fit();
        T[i].shrink_to_fit();
    }
}

void add(int p, int x, int &linked) {
    if (!marked[x]) {
        marked[x] = true;
        T[p].push_back(x);
        T[x].push_back(p);
        linked++;
    }
}

void bcc(int u, int f = 0) {
    in[u] = low[u] = ++cur;
    for (int _ = 0; _ < G[u].size(); _++) {
        int v = G[u][_];
        if (v == f) f = 0;
        else if (in[v]) low[u] = min(low[u], in[v]);
        else {
            stk.push_back(Pair(u, v));
            bcc(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > in[u]) {  // cut edge u-v
                T[u].push_back(v);
                T[v].push_back(u);
                stk.pop_back();
            } else if (low[v] >= in[u]) {
                cnt++;
                int linked = 0, p = n + cnt;
                while (!stk.empty()) {
                    Pair x = stk[stk.size() - 1];
                    stk.pop_back();
                    add(p, x.v, linked);
                    add(p, x.u, linked);
                    if (x.u == u && x.v == v)
                        break;
                }
                for (int _ = 0; _ < T[p].size(); _++) {
                    int px = T[p][_];
                    marked[px] = false;
                }
                if (linked == 0)
                    cnt--;
            }
        }
    }
}

i64 ans = 0;
int sum[NMAX + 10];

void dfs(int x, int pa) {
    sum[x] = x > n ? 0 : 1;
    for (int _ = 0; _ < T[x].size(); _++) {
        int v = T[x][_];
        if (v == pa)
            continue;
        dfs(v, x);
        sum[x] += sum[v];
    }

    if (x > n) {
        vi f, g;

        int l = T[x].size();
        //f.reserve(l);
        //g.reserve(l + l / 2);
        for (int i = 0; i < T[x].size(); i++) {
            int v = T[x][i];
            int sz = v == pa ? n - sum[x] : sum[v];
            f.push_back(sz);
        }
        for (int i = 0; i < l; i++) {
            g.push_back(f[l - i - 1]);
        }
        for (int i = 0; i < l / 2; i++) {
            g.push_back(f[l - i - 1]);
        }

        f = f * g;

        i64 invl = minv(l);
        for (int i = l; i < l + l / 2; i++) {
            i64 a = i - l + 1;
            if (l == 2 * a)
                f[i] = i64(f[i]) * INV2 % MOD;
            //printf("a = %lld, f[i] = %d\n", a, f[i]);
            ans = (ans + invl * f[i] % MOD * a % MOD * (l - a)) % MOD;
        }
    } else {
        for (int _ = 0; _ < T[x].size(); _++) {
            int v = T[x][_];
            if (v > n || v == pa)
                continue;
            i64 sz = sum[v];
            ans = (ans + sz * (n - sz)) % MOD;
        }
    }
}

void _main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        G[i].shrink_to_fit();
    }

    bcc(1);
    stk.clear();
    stk.shrink_to_fit();

    for (int i = 1; i <= n + cnt; i++) {
        G[i].clear();
        G[i].shrink_to_fit();
        T[i].shrink_to_fit();
    }

    ans = 0;
    dfs(1, 0);

    ans %= MOD;
    if (ans < 0)
        ans += MOD;
    printf("%lld\n", ans);
    reset();
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}
