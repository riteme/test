#include <bits/stdc++.h>

using namespace std;
 
#define ll long long
#define N 200010
#define U 1010
#define unit 600
#define pii pair <int, int> 
int n, m, q;
int vis[N], degree[N];
pii edge[N]; 
vector <int> vec[N];
int pos[N], posl[U], posr[U];
int isHasUnit[U], isHasSin[N];
int id[N];
int valBig[U][U], valBigOri[U][U]; 
int Hash[N], ran;
 
void read(int &res)
{
    res = 0;
    char c;
    while (!isdigit(c = getchar()));
    while (isdigit(c)) res = res * 10 + c - '0', c = getchar();
}
 
void force(int l, int r)
{
    for (int i = l, u, v; i <= r; ++i)
    {
        isHasSin[i] ^= 1;
        u = edge[i].first, v = edge[i].second;                            
        if (vis[u])
            valBig[id[u]][pos[i]] ^= Hash[v];
        if (vis[v])
            valBig[id[v]][pos[i]] ^= Hash[u];
    }
}
 
void update(int l, int r)
{
    if (pos[l] == pos[r]) force(l, r);
    else
    {
        force(l, posr[pos[l]]);
        for (int i = pos[l] + 1; i < pos[r]; ++i) isHasUnit[i] ^= 1;
        force(posl[pos[r]], r);
    }
}
 
int query(int u)
{
    int res = 0;
    if (vis[u])
    {
        for (int i = 1; i <= pos[m]; ++i)
        {
            res ^= valBig[id[u]][i];
            if (isHasUnit[i]) res ^= valBigOri[id[u]][i];
        }
    }
    else
    {
        for (auto it : vec[u])
        {
            if (isHasSin[it] ^ isHasUnit[pos[it]])
            {
                int v = edge[it].first == u ? edge[it].second : edge[it].first;
                res ^= Hash[v];
            }
        }
    }
    return res;
}
 
void Run()
{   
    for (int i = 1; i <= 100000; ++i)
    {
        ran *= 233;
        ran += 17;   
        Hash[i] = ran;
    }
    for (int i = 1; i <= 200000; ++i)
    {
        pos[i] = (i - 1) / unit + 1;
        if (i == 1 || pos[i] != pos[i - 1]) posl[pos[i]] = i;
        posr[pos[i]] = i;
    }
    int T; scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) degree[i] = 0, vis[i] = 0, vec[i].clear();
        for (int i = 1; i <= m; ++i) isHasSin[i] = 1;
        for (int i = 1; i <= pos[m]; ++i) isHasUnit[i] = 0;
        id[0] = 0;
        for (int i = 1, u, v; i <= m; ++i)
        {
            read(u), read(v);
            edge[i] = pii(u, v);
            ++degree[u];
            ++degree[v];
        }
        for (int i = 1; i <= n; ++i) if (degree[i] >= unit)
        {
            vis[i] = 1;
            id[i] = ++id[0]; 
            for (int j = 1; j <= pos[m]; ++j)
                valBig[id[i]][j] = 0, valBigOri[id[i]][j] = 0; 
        }
        for (int i = 1, u, v; i <= m; ++i)
         {
            u = edge[i].first; v = edge[i].second;
            if (vis[u])
            {
                valBig[id[u]][pos[i]] ^= Hash[v];
                valBigOri[id[u]][pos[i]] ^= Hash[v];
            }
            else vec[u].push_back(i);
            if (vis[v])
            {
                valBig[id[v]][pos[i]] ^= Hash[u];
                valBigOri[id[v]][pos[i]] ^= Hash[u];
            }
            else vec[v].push_back(i);
        }
        read(q);
        for (int qq = 1, op, x, y; qq <= q; ++qq)
        {
            read(op), read(x), read(y);
            if (op == 1) update(x, y);
            else putchar((query(x) == query(y)) + '0');
        }
        puts("");
    }
}
 
int main()
{
 
    Run();
    return 0;
}
