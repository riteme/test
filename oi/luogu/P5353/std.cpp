#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int MAXN = 4e6 + 5;
const double LIM = 1e16;
const float Alpha = 0.7;

int n;
char S[MAXN];
int fa[MAXN];
int rk[MAXN], sa[MAXN];

namespace SufTree{
	double val[MAXN];
	int siz[MAXN];
	int ch[MAXN][2];
	int tr[MAXN], cnt;
	int rt;
	
	void Update(int x) {
		siz[x] = 1 + siz[ch[x][0]] + siz[ch[x][1]];
	}
	
	int Bad(int x) {
		return 1.0 * siz[ch[x][0]] > Alpha * siz[x] || 1.0 * siz[ch[x][1]] > Alpha * siz[x];
	}
	
	int Comp(int x, int y) {
		return S[x] < S[y] || (S[x] == S[y] && val[fa[x]] < val[fa[y]]);
	}
	
	void Pia(int x) {
		if (!x) return;
		Pia(ch[x][0]);
		tr[++cnt] = x;
		Pia(ch[x][1]);
		ch[x][0] = ch[x][1] = 0;
	}
	
	void Rebuild(int &x, int l, int r, double lv, double rv) {
		if (l > r) return;
		int mid = (l + r) >> 1;
		double midv = (lv + rv) / 2;
		x = tr[mid];
		val[x] = midv;
		Rebuild(ch[x][0], l, mid - 1, lv, midv);
		Rebuild(ch[x][1], mid + 1, r, midv, rv);
		Update(x);
	}
	
	void Maintain(int &x, double lv, double rv) {
		if (Bad(x)) {
//			cerr << "*" << x;
			cnt = 0;
			Pia(x);
			Rebuild(x, 1, cnt, lv, rv);
		}
	}
	
	void Insert(int &x, int idx, double lv, double rv) {
		if (!x) {
			x = idx;
			siz[x] = 1;
			ch[x][0] = ch[x][1] = 0;
			val[x] = (lv + rv) / 2;
			return;
		}
		if (Comp(idx, x)) Insert(ch[x][0], idx, lv, val[x]);
		else Insert(ch[x][1], idx, val[x], rv);
		Update(x);
		Maintain(x, lv, rv);
	}
	
	void Calc(int x) {
		if (!x) return;
		Calc(ch[x][0]);
		sa[++cnt] = x;
		Calc(ch[x][1]);
	}
	
	void Build() {
		for (int i = 1; i <= n; i++) {
			Insert(rt, i, 1, LIM);
		}
		cnt = 0;
		Calc(rt);
		for (int i = 1; i <= n; i++) rk[sa[i]] = i;
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) scanf("%d", fa + i);
	scanf("%s", S + 1);
	SufTree::Build();
	for (int i = 1; i <= n; i++) printf("%d ", sa[i]);
	return 0;
}
