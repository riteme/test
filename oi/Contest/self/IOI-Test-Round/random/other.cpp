#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#define maxn 65
using namespace std;
long long n;
long long num[maxn][maxn];
long long frn[maxn][maxn];
long long mode = 1000000007;
long long px, py;
void bk(long long a, long long b)
{
	if(!b) 
	{
		px = 1, py = 0;
		if(a < 0) px = -1;
		return ;
	}
	long long ns = a / b;
	bk(b, a % b);
	long long lpx = px;
	px = py, py = lpx - ns * py;
	px %= mode, py %= mode;
	long long ngt = a * px + b * py;
}
long long get()
{	//行列式 
	int flag = 1;
	long long ans = 1;
	for(long long i = 2; i <= n; i++)
	{
		long long pl = 0;
		for(long long j = i; j <= n; j++)
			if(num[j][i] != 0) 
			{
				pl = j;
				break;
			}
		if(!pl) return 0;
		if(pl != i) flag *= -1;
		for(long long j = 2; j <= n; j++)
			swap(num[pl][j], num[i][j]);
		bk(mode, num[i][i]);
		for(long long j = i + 1; j <= n; j++)
		{
			long long ns = py * num[j][i];
			ns %= mode;
			for(long long k = i; k <= n; k++)
				num[j][k] -= ((num[i][k] * ns)), 
				num[j][k] %= mode;
		}
		ans *= num[i][i];
		ans %= mode;
	}
	ans += mode;
	return ans * flag;
}
void ade(long long u, long long v, long long t)
{
	num[u][u] += t, num[v][v] += t, num[u][v] -= t, num[v][u] -= t;
}
long long m;
long long lk[2000][2], w[maxn];
int main()
{
	scanf("%lld%lld", &n, &m);
	for(long long i = 1; i <= m; i++)
		scanf("%lld%lld%lld", &lk[i][0], &lk[i][1], &w[i]), 
		ade(lk[i][0], lk[i][1], 1);
	for(long long i = 1; i <= n; i++)
		for(long long j = 1; j <= n; j++)
			frn[i][j] = num[i][j];
	long long as = get();
	bk(mode, as);
	long long nbk = py;
	long long ans = 0;
	for(long long i = 1; i <= m; i++)
	{
		for(long long j = 1; j <= n; j++)
			for(long long k = 1; k <= n; k++)
				num[j][k] = frn[j][k];
		ade(lk[i][0], lk[i][1], -1);
		long long nans = as - get();
		nans *= w[i], nans %= mode;
		ans += nans, ans %= mode;
	}
	ans *= nbk, ans %= mode;
	ans += mode, ans %= mode;
	printf("%lld\n", ans);
	return 0;
} 
