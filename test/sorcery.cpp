#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
#define MOD 1000000007
#define L 1000

using namespace std;
typedef long long LL;
inline int read() {
	int num = 0, k = 1; 
	char ch = getchar(); 
	while (ch > '9' || ch < '0') {if (ch == '-') k = -1; ch = getchar();}
	while (ch <= '9' && ch >= '0') {num *= 10, num += ch - 48; ch = getchar();}
	return num * k;
}

static struct Matrix {
	int x, y, matrix[L + 5][L + 5];
	void reset(int _x, int _y) {
		x = _x, y = _y;
		memset(matrix,0,sizeof(matrix));
		return;
	}
}Ans, a;
Matrix cf (Matrix a, Matrix b) {
	Matrix c;
	c.reset(a.x, b.y);
	for (int i = 0; i < a.x; i ++)
		for (int j = 0; j < b.y; j ++)
			for (int k = 0; k < a.y; k ++)
				c.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j] % MOD, c.matrix[i][j] %= MOD;
	return c;
}
Matrix ksm(Matrix a, LL n) {
	Matrix tmp, ans;
	tmp = a;
	ans.reset(a.x, a.x);
	for (int i = 0; i < a.x; i ++)
		ans.matrix[i][i] = 1;
	while (n) {
		if (n & 1)
			ans = cf(ans, tmp);
		tmp = cf(tmp, tmp);
		n >>= 1;
	}
	return ans;
}

LL dp[L + 5][L + 5], ans = 0;
int n, m, l;

struct ACauto {
	int fail[L + 5], son[L + 5][L + 5], cnt;
	bool cant[L + 5];
	void reset() {
		memset(cant,0,sizeof(cant));
		memset(son,0,sizeof(son));
		memset(fail,0,sizeof(fail));
		fail[0] = 1;
		for (int i = 0; i < 26; i ++)
			son[0][i] = 1;
		cnt = 1;
		return;
	}
	void insert(char *s, int len) {
		int p = 1;
		for (int l = 0; l < len; l ++)
			if (son[p][s[l] - 97])
				p = son[p][s[l] - 97];
			else
				p = son[p][s[l] - 97] = ++ cnt;
		cant[p] = 1;
		return;
	}
	void buildfail() {
		queue <int> q;
		q.push(1);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = 0; i < 26; i ++)
				if (son[u][i]) {
					if (cant[u])
						cant[son[u][i]] = 1;
					int now = fail[u];
					while (!son[now][i]) now = fail[now];
					fail[son[u][i]] = son[now][i];
					q.push(son[u][i]);
				}
		}
		return;
	}
}S;
char s[L + 5][L + 5], s1[L + 5][L + 5];
void work1() {
	dp[0][1] = 1;
	for (int i = 0; i < l; i ++) {
		for (int j = 1; j <= n; j ++) {
			int len = strlen(s[j]);
			if (len + i > l)
				continue;
			for (int p = 1; p <= S.cnt; p ++)
				if (!S.cant[p] && dp[i][p]) {
					int now = p;
					bool flag = 1;
					for (int k = 0; k < len; k ++) {
						if (S.son[now][s[j][k] - 97]) 
							now = S.son[now][s[j][k] - 97];
						else {
							now = S.fail[now];
							while (!S.son[now][s[j][k] - 97]) 
								now = S.fail[now];
							now = S.son[now][s[j][k] - 97];
						}
						if (S.cant[now])
							flag = 0;
					}
					if (flag)
						dp[i + len][now] = dp[i][p] + dp[i + len][now], dp[i + len][now] %= MOD;
				}
		}
	}
	for (int i = 1; i <= S.cnt; i ++)
		if (!S.cant[i])
			ans += dp[l][i], ans %= MOD;
	printf("%lld\n", ans);
	return;
}
void fuck() {
	Ans.reset(1, S.cnt << 1 | 1);
	Ans.matrix[0][1] = 1;
	a.reset(S.cnt << 1 | 1, S.cnt << 1 | 1);
	for (int i = 1; i <= n; i ++) {
		printf("%d\n", i);
		int len = strlen(s[i]);
		if (len == 1) {
			for (int j = 1; j <= S.cnt; j ++)
				if (!S.cant[j]){
					if (S.son[j][s[i][0] - 97]) 
						a.matrix[j + S.cnt][S.son[j][s[i][0] - 97] + S.cnt] ++;
					else {
						int now = S.fail[j];
						while (!S.son[now][s[i][0] - 97])  
							now = S.fail[now];
						now = S.son[now][s[i][0] - 97];
						a.matrix[j + S.cnt][now + S.cnt] ++;
					}}
		} else 
		if (len == 2) {
			for (int j = 1; j <= S.cnt; j ++) 
				if (!S.cant[j]){
					int now = j;
					bool flag = 1;
					for (int k = 0; k < 2; k ++) {
						if (S.son[now][s[i][k] - 97]) 
							now = S.son[now][s[i][k] - 97];
						else {
							now = S.fail[now];
							while (!S.son[now][s[i][k] - 97]) 
								now = S.fail[now];
							now = S.son[now][s[i][k] - 97];
						}
						if (S.cant[now])
							flag = 0;
					}
					if (flag)
						a.matrix[j][now + S.cnt] ++;
				}
		}
	}
	for (int j = 1; j <= S.cnt; j ++)
		a.matrix[j + S.cnt][j] ++;
	a = ksm(a, l);
	Ans = cf(Ans, a);
	for (int i = 1; i <= S.cnt; i ++)
		if (!S.cant[i])
			ans = ans + Ans.matrix[0][i + S.cnt], ans %= MOD;
	return;
}

int main() {
	fuck();
	freopen("sorcery.in","r",stdin);
	freopen("sorcery.out","w",stdout);
	n = read(), m = read(), l = read();
	for (int i = 1; i <= n; i ++)
		scanf("%s", s[i]);
	for (int i = 1; i <= m; i ++)
		scanf("%s", s1[i]);
	S.reset();
	for (int i = 1; i <= m; i ++)
		S.insert(s1[i], strlen(s1[i]));
	S.buildfail();
	return 0;
}
