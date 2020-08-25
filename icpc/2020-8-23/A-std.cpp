#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <ctime>
#include <cassert>
#define lson (u << 1)
#define rson (u << 1 | 1)
#define cls(i, j) memset(i, j, sizeof i)
using namespace std;
typedef long long ll;
const double eps = 1e-6;
const double pi = acos(-1.0);
const int maxn = 1e5 + 10;
const int maxm = 1050;
const int inf = 0x3f3f3f3f;
const ll linf = 0x3fffffffffffffff;
const ll mod = 1e9 + 7;

int debug = 0;
map<ll, int> mapi;
int buf[11], k1;
ll S = (ll)1e11;
double dp[3000][40];

int a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
bool cmp(int a, int b) { return a > b; }
int prime[maxn], k;
bool vis[3000];

ll Hash(int *t){
    ll tem = 1, ans = 0;
    for(int i = 0; i < 11; i++){
        ans += tem * t[i];
        tem *= 37;
    }
    return ans;
}

int stack[11], k2;
ll states[3000];
int ks;
int table[3500][11];

void dfs(ll num, int limit, int next){
    if(next){
        memcpy(buf, stack, sizeof buf);
        sort(buf, buf + 11, cmp);
        ll hash_value = Hash(buf);
        states[ks++] = hash_value;
        memcpy(table[ks - 1], buf, sizeof buf);
        mapi[hash_value] = ks - 1;
    }
    if(next > 10) return;
    for(int i = 1; i <= limit; i++){
        num *= a[next];
        if(num > S) break;
        stack[k2++] = i;
        dfs(num, i, next + 1);
        stack[--k2] = 0;
    }
}

void shaffix(){
    bool vis[500000 + 10];
    int mid = (int)5e5 + 10;
    cls(vis, 0);
    for(int i = 2; i < mid; i++){
        if(vis[i]) continue;
        prime[k++] = i;
        for(ll j = (ll)i * 2; j < mid; j += i) vis[j] = 1;
    }
}

void cal(int id);

void dfs1(int id, int next){
    if(next > 10){
        int buf1[11], buf2[11];
        memcpy(buf1, stack, sizeof stack);
        for(int i = 0; i < 11; i++) buf2[i] = table[id][i] - buf1[i];
        sort(buf1, buf1 + 11, cmp);
        sort(buf2, buf2 + 11, cmp);
        if(!buf1[0] || !buf2[0]) return;
        ll hash_value1 = Hash(buf1), hash_value2 = Hash(buf2);
        int id1 = mapi[hash_value1], id2 = mapi[hash_value2];
        cal(id1), cal(id2);
        double prefix_left = 0, prefix_right = 0;
        for(int i = 0; i < 39; i++){
            dp[id][i + 1] += dp[id1][i] * prefix_right +
            prefix_left * dp[id2][i] + dp[id1][i] * dp[id2][i];
            prefix_left += dp[id1][i], prefix_right += dp[id2][i];
        }
        return;
    }
    for(int i = 0; i <= table[id][next]; i++){
        stack[k2++] = i;
        dfs1(id, next + 1);
        stack[--k2] = 0;
    }
}

void cal(int id){
    if(vis[id]) return;
    k2 = 0;
    dfs1(id, 0);
    int sum = 1;
    for(int i = 0; i < 11; i++) sum *= 1 + table[id][i];
    sum -= 2;
    for(int i = 1; i < 40; i++) dp[id][i] /= sum;
    vis[id] = 1;
    //printf("%d+\n", id);
}

void init(){
    shaffix();
    cls(vis, 0);
    vis[0] = 1;
    mapi.clear();
    //0...10 < 10^11
    cls(stack, 0);
    ks = k2 = 0;
    dfs(1, 40, 0);
    cls(dp, 0);
    dp[0][1] = 1;
    for(int i = 1; i < ks; i++) cal(i);
}

double solve(ll num){
    cls(buf, 0);
    k1 = 0;
    int mid = (int)sqrt((double)num);
    for(int i = 0; i < k && prime[i] <= mid; i++){
        if(num % prime[i]) continue;
        while(num % prime[i] == 0) ++buf[k1], num /= prime[i];
        mid = (int)sqrt((double)num);
        k1++;
    }
    if(num != 1) buf[k1++] = 1;
    sort(buf, buf + 11, cmp);
    ll hash_value = Hash(buf);
    double ans = 0;
    int id = mapi[hash_value];
    for(int i = 1; i < 40; i++) ans += dp[id][i] * i;
    return ans;
}

int main(){
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int T, kase = 0;
    init();
    scanf("%d", &T);
    ll n;
    while(T--){
        scanf("%lld", &n);
        double ans = solve(n);
        printf("Case #%d: %.6f\n", ++kase, ans);
    }
    return 0;
}
