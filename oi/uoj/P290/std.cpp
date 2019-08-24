#include <cstdio>
#include <cstring>
using namespace std;
using u32 = unsigned;
using u64 = unsigned long long;
constexpr u32 maxn = 500005, maxm = 1000005, kcz = 998244353;
int nx[maxm], v[maxm], p[maxn], e[maxn];
bool mk[maxn];
char buff[20000000];
u32 qread() {
	static char *curr = buff;
	u32 res = 0;
	while (*curr < '0') ++curr;
	do res = (res << 1) + (res << 3) + *curr - '0';
	while ('0' <= *++curr);
	return res;
}
bool dfs(u32 x) {
	for (u32 i = e[x]; i; i = nx[i]) {
		u32 y=v[i];
		if (y!=p[x])
		if(p[y])
		{
			v[i ^ 1] = p[y];
			for (u32 j = x; j != y; j = p[j]) {
				if (mk[j]) return true;
				mk[j] = true;
			}
		}
		else {
			p[y] = x;
			if (dfs(y)) return true;
		}
	}
	return false;
}

int main() {
	static u32 f[maxn]{ 1,1 }, c[maxn];
	fread(buff, 1, 20000000, stdin);
	u32 top = 2, T = qread();
	while (T--) {
		u32 n = qread(), m = qread();
		memset(e, 0, sizeof(e[0])*(n + 1));
		for (u32 ec = 1, i = 1; i <= m; ++i) {
			u32 l = qread(), r = qread();
			v[++ec] = r, nx[ec] = e[l], e[l] = ec;
			v[++ec] = l, nx[ec] = e[r], e[r] = ec;
		}
		if (m > n + (n >> 1)) {
			puts("0");
			continue;
		}
		memset(mk, 0, sizeof(mk[0])*(n + 1));
		p[1] = -1;
		memset(p + 2, 0, sizeof(p[0])*(n));
		if (dfs(1)) {
			puts("0");
			continue;
		}
		for (; top < n; ++top) f[top] = (f[top - 1] + (u64)f[top - 2] * (top - 1)) % kcz;
		memset(c, 0, sizeof(c[0])*(n + 1));
		for (u32 i = 2; i <= n; ++i) if (!mk[i]) ++c[i], ++c[p[i]];
		u32 res = 1;
		for (u32 i = 1; i <= n; ++i) res = (u64)res*f[c[i]] % kcz;
		printf("%u\n", res);
	}
}
