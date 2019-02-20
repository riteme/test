#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll maxn = 100010,inf = 1e9,mod = 1e9 + 7;
ll T,n,head[maxn],to[maxn * 2],nextt[maxn * 2],tot = 1;
ll a[maxn],son[maxn * 3],dfs_clock,L[maxn],R[maxn],f[maxn];
ll pre[maxn],last[maxn],d[maxn],sizee[maxn],root,now,top;
ll lc[maxn * 40],rc[maxn * 40],sum[maxn * 40],tag[maxn * 40];
pair<ll,ll> S[maxn];

void init()
{
    for (ll i = 1; i <= n; i++)
        head[i] = 0,f[i] = 0;
    tot = 1;
    dfs_clock = 0;

}

bool cmp(ll x,ll y)
{
    return sizee[x] > sizee[y];
}

void add(ll x,ll y)
{
    to[tot] = y;
    nextt[tot] = head[x];
    head[x] = tot++;
}

ll newnode()
{
    ++now;
    tag[now] = 1;
    lc[now] = rc[now] = sum[now] = 0;
    return now;
}

void dfs(ll u,ll faa)
{
    d[u] = d[faa] + a[u];
    sizee[u] = 1;
    for (ll i = head[u];i;i = nextt[i])
    {
        ll v = to[i];
        if (v == faa)
            continue;
        dfs(v,u);
        sizee[u] += sizee[v];
    }
    L[u] = R[u] = dfs_clock + 1;
    for (ll i = head[u];i;i = nextt[i])
    {
        ll v = to[i];
        if (v == faa)
            continue;
        son[++R[u]] = v;
    }
    R[u]++;
    dfs_clock = R[u];
    sort(son + L[u] + 1,son + R[u],cmp);
}

void addtag(ll o,ll v)
{
    if (!o)
        return;
    tag[o] = 1LL * tag[o] * v % mod;
    sum[o] = 1LL * sum[o] * v % mod;
}

void pushdown(ll o)
{
    if (tag[o] != 1)
    {
        addtag(lc[o],tag[o]);
        addtag(rc[o],tag[o]);
        tag[o] = 1;
    }
}

ll query(ll o,ll l,ll r,ll x,ll y)
{
    if (!o)
        return 0;
    if (x <= l && r <= y)
        return sum[o];
    pushdown(o);
    ll mid = (l + r) >> 1;
    if (y <= mid)
        return query(lc[o],l,mid,x,y);
    else if (x > mid)
        return query(rc[o],mid + 1,r,x,y);
    else
        return (query(lc[o],l,mid,x,mid) + query(rc[o],mid + 1,r,mid + 1,y)) % mod;
}

void pushup(ll o)
{
    sum[o] = (sum[lc[o]] + sum[rc[o]]) % mod;
}

void insert(ll &o,ll l,ll r,ll pos,ll v)
{
    if (!o)
        o = newnode();
    if (l == r)
    {
        sum[o] += v;
        sum[o] %= mod;
        return;
    }
    pushdown(o);
    ll mid = (l + r) >> 1;
    if (pos <= mid)
        insert(lc[o],l,mid,pos,v);
    else
        insert(rc[o],mid + 1,r,pos,v);
    pushup(o);
}

void get(ll u,ll faa,ll s)
{
    S[++top] = make_pair(d[u],1LL * s * pre[R[u] - 1] % mod);
    for (ll i = L[u] + 1; i < R[u]; i++)
    {
        ll v = son[i];
        get(v,u,1LL * s * pre[i - 1] % mod * last[i + 1] % mod);
    }
}

void dp(ll u,ll faa)
{
    for (ll i = L[u] + 2; i < R[u]; i++)
    {
        dp(son[i],u);
        now = 0;
        root = newnode();
    }
    if (L[u] + 1 < R[u])
        dp(son[L[u] + 1],u);
    pre[L[u]] = 1;
    for (ll i = L[u] + 1; i < R[u]; i++)
        pre[i] = 1LL * pre[i - 1] * f[son[i]] % mod;
    last[R[u]] = 1;
    for (ll i = R[u] - 1; i > L[u]; i--)
        last[i] = 1LL * last[i + 1] * f[son[i]] % mod;
    if (d[u] >= d[faa])
        f[u] = (f[u] + pre[R[u] - 1]) % mod;
    f[u] = (f[u] + 1LL * last[L[u] + 2] * query(root,0,inf + inf,d[faa] + inf,inf + inf) % mod) % mod;
    for (ll i = L[u] + 2; i < R[u]; i++)
    {
        top = 0;
        get(son[i],u,1);
        for (ll j = 1; j <= top; j++)
        {
            if (S[j].first >= d[faa])
                f[u] = (f[u] + 1LL * S[j].second * pre[i - 1] % mod * last[i + 1] % mod) % mod;
            f[u] = (f[u] + 1LL * S[j].second * last[i + 1] % mod * query(root,0,inf + inf,d[u] + d[faa] - S[j].first + inf,inf + inf) % mod) % mod;
        }
        addtag(root,f[son[i]]);
        for (int j = 1; j <= top; j++)
            insert(root,0,inf + inf,S[j].first + inf,1LL * S[j].second * pre[i - 1] % mod);
    }
    insert(root,0,inf + inf,d[u] + inf,pre[R[u] - 1]);
}

int main()
{
    scanf("%lld",&T);
    while (T--)
    {
        scanf("%lld",&n);
        init();
        for (ll i = 1; i <= n; i++)
            scanf("%lld",&a[i]);
        for (ll i = 1; i < n; i++)
        {
            ll x,y;
            scanf("%lld%lld",&x,&y);
            add(x,y);
            add(y,x);
        }
        dfs(1,0);
        now = 0;
        root = newnode();
        dp(1,0);
        printf("%lld\n",f[1]);
    }

    return 0;
}
