#include <bits/stdc++.h>
using namespace std;
 
inline char gc() {
	static char now[1 << 16], *S, *T;
	if(S == T) {T = (S = now) + fread(now, 1, 1 << 16, stdin); if(S == T) return EOF;}
	return *S ++;
}
#define gc getchar
inline int read() {
	int x = 0, f = 1; char c = gc();
	while(c < '0' || c > '9') {(c ^ '-') ? 0 : (f = 0); c = gc();}
	while(c >= '0' && c <= '9') {x = (x << 3) + (x << 1) + (c ^ 48); c = gc();}
	return f ? x : ((~ x) + 1);
}
struct node {int l, r, id;};
typedef vector<node> VN;
typedef vector<node>::iterator VNit;
typedef vector<int> VI;
typedef vector<int>::iterator VIit;
typedef long long ll;
#define pb push_back
#define N 200010
VN que[N];
VI pos[N];
int n, m, q, a[N];
namespace task1 {
	int f[1010][1010], nxt[1010][1010], s[1010][1010];
	inline int getmid(int ql, int qr, int k) {
		int l = ql, r = qr, mid, res = l - 1;
		while (l <= r) {
			mid = (l + r) >> 1;
			if (qr - f[mid][k] + 2 > 0) res = mid, l = mid + 1;
			else r = mid - 1;
		}
		return res;
	}
	inline void work() {
		for (int j = 1; j <= m; ++ j) {
			for (int i = 1, p = 1; i <= n; ++ i) {
				p = max(p, i);
				while (p <= n && (a[p] ^ j)) ++ p;
				nxt[i][j] = p;
			}
		}
		for (int i = 1; i <= n + 2; ++ i) f[i][0] = n + 2;
		for (int j = 1; j <= m; ++ j) {
			for (int i = 1; i <= n + 2; ++ i) f[i][j] = n + 2;
			for (int i = 1; i <= n; ++ i) {
				f[i][j] = min(f[f[i][j - 1]][j - 1], nxt[i][j] + 1);
//				if(j == 3) printf("f[%d] = %d\n", i, f[i][j]);
			}
		}
		for (int j = 1; j <= m; ++ j) {
			s[0][j] = 0;
			for (int i = 1; i <= n; ++ i) {
				s[i][j] = s[i - 1][j] + f[i][j];
			}
		}
		for (int i = 1; i <= q; ++ i) {
			int l = read(), r = read(), k = read();
			int mid = getmid(l, r, k);
			if (mid < l) puts("0");
			else printf("%d\n", (mid - l + 1) * (r + 2) - (s[mid][k] - s[l - 1][k]));
		}
	}
}
node f[N][2]; int cnt[2];
 
inline int erfen(int p, int val) {
	int l = 1, r = cnt[p], mid;
	while(l <= r) {
		mid = (l + r) >> 1;
		if(f[mid][p].l <= val && val <= f[mid][p].r) return mid;
		if(val < f[mid][p].l) r = mid - 1;
		else l = mid + 1;
	}
	return n + 2;
}
node g[N]; ll sum[N];
 
inline void print_f(int j, int now) {
	printf("j = %d:\n", j);
	for (int i = 1; i <= cnt[now]; ++ i) {
		printf("l = %d, r = %d, f = %d\n", f[i][now].l, f[i][now].r, f[i][now].id);
	}
}
 
 
inline void update_f(int j) {
	int now = (j & 1), pre = (now ^ 1);
	cnt[now] = 0;
	f[n + 2][pre].id = n + 2;
	for (int i = 1; i <= cnt[pre]; ++i) {
		f[++ cnt[now]][now] = f[i][pre];
		f[cnt[now]][now].id = f[erfen(pre, f[i][pre].id)][pre].id;
	}
	
	int l = 1, r = 1, tot = 0;
	while (l <= cnt[now]) {
		while (r < cnt[now] && f[r + 1][now].id == f[r][now].id) ++ r;
		f[++ tot][now] = (node) {f[l][now].l, f[r][now].r, f[l][now].id};
		++ r; l = r;
	}
	cnt[now] = tot;
	
//	if (j == 3) print_f(3, 1);
	
	if(pos[j].begin() == pos[j].end()) {
		for (int i = 1; i <= cnt[now]; ++ i) {
			sum[i] = sum[i - 1] + 1ll * f[i][now].id * (f[i][now].r - f[i][now].l + 1);
		}
		return ;
	}
	
	l = 1;
	int p = 1; tot = 0;
	for (VIit it = pos[j].begin(); it != pos[j].end(); ++ it) {
		r = (*it);
//		if (j == 3) printf("%d %d\n", l, r);
		while (f[p][now].r < l) g[++ tot] = f[p][now], ++ p;
		while (f[p][now].l <= r) {
			if (f[p][now].id > r + 1) {
//				if(j == 3 && tot == 6)printf("l = %d, r = %d\n", l, r);
//				if(j == 3 && tot == 6 && f[p][now].l < l && f[p][now].r <= r) puts("hahahwin");
				if (l <= f[p][now].l && f[p][now].r <= r) g[++ tot] = (node) {f[p][now].l, f[p][now].r, r + 1};
				else if (f[p][now].l < l && f[p][now].r <= r) g[++ tot] = (node) {l, f[p][now].r, r + 1};
				else if (f[p][now].l < l && f[p][now].r > r) g[++ tot] = (node) {l, r, r + 1};
				else if (l <= f[p][now].l && f[p][now].r > r) g[++ tot] = (node) {f[p][now].l, r, r + 1};
			} else {
				g[++ tot] = f[p][now];
				g[tot].l = max(g[tot].l, l);
				g[tot].r = min(g[tot].r, r);
			}
//			if(j == 3 && tot == 7) printf("## %d %d %d\n", f[p][now].l, f[p][now].r, f[p][now].id);
			if (f[p][now].r >= r) break ;
			++ p;
		}
		l = r + 1;
	}
	
	if (g[tot].r < f[p][now].r) g[tot + 1] = (node) {g[tot].r + 1, f[p][now].r, f[p][now].id}, ++ tot;
	
	while(p < cnt[now]) ++ p, g[++ tot] = f[p][now];
	
//	for (int i = 1; i <= tot; ++i) printf("g %d %d %d\n", g[i].l, g[i].r, g[i].id);
	
	l = 1, r = 1; cnt[now] = 0;
	while (l <= tot) {
		while (r < tot && g[r + 1].id == g[r].id) ++ r;
		f[++ cnt[now]][now] = (node) {g[l].l, g[r].r, g[l].id};
		++ r; l = r;
	}
	
//	if (j == 3) print_f(3, 1);
	
	for (int i = 1; i <= cnt[now]; ++ i) {
		sum[i] = sum[i - 1] + 1ll * f[i][now].id * (f[i][now].r - f[i][now].l + 1);
	}
}
 
inline int getmid(int p, int ql, int qr, int rr) {
	int l = ql, r = qr, mid, res = l - 1;
	while (l <= r) {
		mid = (l + r) >> 1;
		if (rr - f[mid][p].id + 2 > 0) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	return res;
}
 
ll ans[N];
inline ll getsum(int l, int r, int ql, int qr, int k) {
	ll res = 0; int now = (k & 1);
	if(f[qr][now].r > r) res += 1ll * f[qr][now].id * (r - f[qr][now].l + 1), -- qr;
	if(f[ql][now].l < l) res += 1ll * f[ql][now].id * (f[ql][now].r - l + 1), ++ ql;
	if(ql <= qr) res += sum[qr] - sum[ql - 1];
	return res;
}
inline void update_ans(int k) {
	int now = (k & 1);
	for (VNit it = que[k].begin(); it != que[k].end(); ++ it) {
		int l = it -> l, r = it -> r, id = it -> id;
		int ql = erfen(now, l), qr = erfen(now, r);
		int mid = getmid(now, ql, qr, r);
		if (mid < ql) ans[id] = 0;
		else ans[id] = 1ll * (min(f[mid][now].r, r) - l + 1) * (r + 2) - getsum(l, r, ql, mid, k);
	}
}
int main() {
//	freopen("K.in", "r", stdin);
//	freopen("K.out", "w", stdout);
	
	n = read(); m = read(); q = read();
	for (int i = 1; i <= n; ++ i) a[i] = read(), pos[a[i]].pb(i);
	
//	if (n <= 1000 && m <= 1000) {
//		task1::work();
//		return 0;
//	}
	
	for (int i = 1; i <= q; ++ i) {
		int l = read(), r = read(), k = read();
		que[k].pb((node) {l, r, i});
	}
	
	cnt[0] = cnt[1] = 0;
	f[++ cnt[0]][0] = (node) {1, n, n + 2};
	for (int j = 1; j <= m; ++j) {
		update_f(j);
		update_ans(j);
	}
	for (int i = 1; i <= q; ++i) printf("%lld\n", ans[i]);
	return 0;
}
