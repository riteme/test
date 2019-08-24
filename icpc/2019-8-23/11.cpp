#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int u32;
#define INF 0x3f3f3f3f
const int maxn = 1e6 + 10;
const int mod = 998244353;
ll tim;
#define S 1000000
int ma[4][1001000];
int ma2[4][1001000];
int pw[4][1100000];
bool vv[4][1010000];

ll pow(ll a, ll b, ll m)
{
    ll ff=0;
    if(m==7)ff=1;
    else if(m==17)ff=2;
     if ( ff && b <= 1000000 && a + 1 == m ) {
        return pw[ff][b];
    }
     //tim++;
    //printf ( "%lld %lld %lld\n" , a , b , m );
    ll ans = 1;
    while(b)
    {
        if(b & 1)ans = (ans) * (a) % m;
        b>>=1;
        a = (a) * (a) % m;
    }
    return ans;
}
ll extgcd(ll a, ll b, ll& x, ll& y)
//求解ax+by=gcd(a, b)
//返回值为gcd(a, b)
{
    ll d = a;
    if(b)
    {
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }
    else x = 1, y = 0;
    return d;
}
int i7[100], i17[100];
ll mod_inverse(ll a, ll m)
//求解a关于模上m的逆元
//返回-1表示逆元不存在
{
    ll x, y;
    ll d = extgcd(a, m, x, y);
    if (x < 0) x+= m;
    return d == 1 ? x : -1;
}

int tb2[9000000],tb7[900],tb17[900];

ll Mul(ll n, ll pi, ll pk)//计算n! mod pk的部分值  pk为pi的ki次方
//算出的答案不包括pi的幂的那一部分
{
    //printf ( "%lld %lld %lld\n" , n , pi , pk );
    if(!n)return 1;
    ll ff;
    if(pi==2)ff=1;
    else if(pi==7)ff=2;
    else ff=3;
    if ( n <= 1000000 && ma[ff][n]<INF ) return ma[ff][n];
    int p = (n >> 19) ^ (n & ((1<<19)-1));
    if (ma2[ff][p]<INF) return ma2[ff][p];
    ll ans = 1;
    if(n / pk)
    {
        //if ( pi == 2 ) printf ( "$$\n" );
        if ( pi == 7 ) ans = 6;
        else if ( pi == 17 ) ans = 16;
        //    for(ll i = 2; i <= pk; i++) //求出循环节乘积
        //        if(i % pi)ans = ans * i % pk;
        //if ( pi == 2 ) printf ( "$$$$$$$$$$$$$$$$$$%lld\n" , ans );
        //else ans = fp2(ans, n / pk, pk); //循环节次数为n / pk
        else ans = 1; //循环节次数为n / pk
    }
    ll ret;
    if ( pi != 2 ) {
        if ( pi == 7 ) ret = ans * tb7[n%7] * Mul(n / pi, 7, 7) % 7;
        else ret = ans * tb17[n%17] * Mul(n / pi, 17, 17) % 17;
       // for(ll i = 2; i <= n % pk; i++)
        //    if(i % pi)ans = ans * i % pk;
    }
    else {
        ret = u32(ans) * u32(tb2[n & 8388607]) * u32(Mul(n >> 1, 2, pk)) & 8388607;
    }
    if ( n <= 1000000 ) ma[ff][n] = ret;
    else ma2[ff][p] =ret;
    return ret;//递归求解
}

ll C(ll n, ll m,ll l, ll p, ll pi, ll pk)//计算组合数C(n, m) mod pk的值 pk为pi的ki次方
{    //tim++;
    if(m+l > n)return 0;
    //ll a=1,b=1,c=1,d=1;
    ll a = Mul(n, pi, pk), b = Mul(m, pi, pk), c = Mul(l, pi, pk),d = Mul(n-m-l,pi,pk);
    ll k = 0, ans;//k为pi的幂值
    for(ll i = n; i; ) {
        i /= pi;
        k += i;
    }
    for(ll i = m; i; ){
        i /= pi;
        k -= i;
    }
    for(ll i = l; i; ){
        i /= pi;
        k -= i;
    }
    for(ll i = n - m-l; i; i /= pi)k -= i / pi;
    if (pk==7) {
    ans = a * i7[b] * i7[c] * i7[d] * pow(pi, k, pk) % 7;//ans就是n! mod pk的值
    ans = ans * (p / 7) % p * i7[p / 7 %7] % p;//此时用剩余定理合并解
    }else if (pk==17){
    ans = a * i17[b] * i17[c] * i17[d] * pow(pi, k, pk) % 17;//ans就是n! mod pk的值
    ans = ans * (p / 17) % p * i17[p / 17 %17] % p;//此时用剩余定理合并解
    }else{
    ans = a * mod_inverse(b, pk) % pk * mod_inverse(c, pk) % pk *mod_inverse(d,pk)%pk* pow(pi, k, pk) % pk;//ans就是n! mod pk的值
    ans = ans * (p / pk) % p * mod_inverse(p / pk, pk) % p;//此时用剩余定理合并解
    }
    return ans;
}

ll aa[100] , pp[100];
ll Lucas(ll n, ll m,ll k, ll p)
{
    ll x = p;
    ll ans = 0;
    aa[0] = 2; pp[0] = 8388608;
    aa[1] = 7; pp[1] = 7;
    aa[2] = 17; pp[2] = 17;
    for(ll i = 0; i <= 2; i++)
    {
        ans = (ans + C(n, m,k, p, aa[i], pp[i])) % p;
    }
    return ans;
}

int main()
{
    //freopen ("11.in","r",stdin);
    ll t1 , t2 , p , q , n , m;
    ll i , ans , x , y , v;
    pw[1][0] = pw[2][0] = 1;
    for ( i = 1 ; i <= 1000000 ; i++ ) {
        pw[1][i] = (pw[1][i-1]*6)%7;
        pw[2][i] = (pw[2][i-1]*16)%17;
    }
    tb2[0] = 1;
    for ( i = 1 ; i <= 8388608 ; i++ ) {
        if ( i&1 ) tb2[i] = tb2[i-1]*i&8388607;
        else tb2[i] = tb2[i-1];
    }
    tb7[0] = 1;
    for ( i = 1 ; i <= 7 ; i++ ) {
        if ( i % 7 ) tb7[i] = tb7[i-1]*i%7;
        else tb7[i] = tb7[i-1];
    }
    tb17[0] = 1;
    for ( i = 1 ; i <= 17 ; i++ ) {
        if ( i % 17 ) tb17[i] = tb17[i-1]*i%17;
        else tb17[i] = tb17[i-1];
    }
    i7[0] = i17[0] = -1;
    i7[1] = i17[1] = 1;
    for (int i = 2; i < 7; i++) i7[i] = 7 - 7/i*i7[7%i]%7;
    for (int i = 2; i < 17; i++) i17[i] = 17 - 17/i*i17[17%i]%17;
    memset(ma,0x3f,sizeof(ma));
    memset(ma2,0x3f,sizeof(ma2));
    while ( scanf ( "%lld%lld%lld%lld%lld%lld" , &t1 , &t2 , &p , &q , &n , &m ) != EOF ) {
        ans = 1;
        for ( i = 1 ; i <= m ; i++ ) {
            scanf ( "%lld%lld%lld" , &x , &y , &v );
            //printf ( "%lld\n" , i );
            if ( x % p == 0 && y % q == 0 ) {
                x /= p; y /= q;
                ans = (ans * pow ( v , Lucas(n,x,y,mod-1)* pow(t1,x,mod-1)%(mod-1)*pow(t2,y,mod-1)%(mod-1), mod ) ) % mod;
            }
        }
        printf ( "%lld\n" , ans );
    }
    //printf ( "%lld\n" , tim );
    return 0;
}
