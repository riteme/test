#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>

#define DEBUG(args...) fprintf(stderr, args)

typedef long long LL;

#define FOR(i, l, r) for(int i = (l), i##_end = (r); i <= i##_end; ++i)
#define REP(i, l, r) for(int i = (l), i##_end = (r); i <  i##_end; ++i)
#define DFR(i, l, r) for(int i = (l), i##_end = (r); i >= i##_end; --i)
#define DRP(i, l, r) for(int i = (l), i##_end = (r); i >  i##_end; --i)

template<class T>T Min(const T &a, const T &b) {return a < b ? a : b;}
template<class T>T Max(const T &a, const T &b) {return a > b ? a : b;}
template<class T>bool Chkmin(T &a, const T &b) {return a > b ? a = b, 1 : 0;}
template<class T>bool Chkmax(T &a, const T &b) {return a < b ? a = b, 1 : 0;}

class fast_input {
private:
	static const int SIZE = 1 << 15 | 1;
	char buf[SIZE], *front, *back;

	void Next(char &c) {
	    if(front == back) back = (front = buf) + fread(buf, 1, SIZE, stdin);
		c = front == back ? (char)EOF : *front++;
	}

public :
	template<class T>void operator () (T &x) {
		char c, f = 1;
		for(Next(c); !isdigit(c); Next(c)) if(c == '-') f = -1;
		for(x = 0; isdigit(c); Next(c)) x = x * 10 + c - '0';
		x *= f;
	}
	void operator () (char &c, char l = 'a', char r = 'z') {
		for(Next(c); c > r || c < l; Next(c)) ;
	}
}input;

struct tuple {
	int c, v, e, d;
	tuple() {}
	tuple(int c, int v, int e, int d) : c(c), v(v), e(e), d(d) {}
	bool operator < (const tuple &o) const {
		return v < o.v;
	}
	bool operator > (const tuple &o) const {
		return v > o.v;
	}
};

struct pair {
	int c, v;
	explicit pair(int c = 0, int v = 0) : c(c), v(v) {}
	bool operator < (const pair &o) const {
		return v < o.v;
	}
};

const int SN = 200000 + 47;

int set[SN];
int re[SN], cnt[SN];
tuple veg[SN];
pair choose[SN];
LL ans[SN];
int ask[SN], maxp;

int Find(int);

int main() {

#ifdef Cai
	freopen("s.in", "r", stdin);
#endif

	int n, m, q, x, y, z, w, u, cv = 0, cc = 0;

	input(n), input(m), input(q);
	FOR(i, 1, n) {
		input(x), input(y), input(z), input(w);
		u = !w ? 100000 : w == 1 ? z / w - 1 : z / w + (z % w != 0);		
		veg[++cv] = tuple(z - 1, x, u, w);
		veg[++cv] = tuple(1, x + y, u + (w == 1), 0);
	}
	FOR(i, 1, q) input(ask[i]), Chkmax(maxp, ask[i]);

	FOR(i, 1, cv) Chkmin(veg[i].e, maxp);

	std::sort(veg + 1, veg + cv + 1, std::greater<tuple>());

	FOR(i, 1, maxp) set[i] = i, re[i] = m;

	FOR(i, 1, cv) {
		x = Find(veg[i].e), y = veg[i].c, z = veg[i].d;
		while(x && y) {
			w = y - (x - 1) * z;
			if(re[x] > w) {
				choose[++cc] = pair(w, veg[i].v);
				ans[maxp] += 1LL * w * veg[i].v;
				re[x] -= w, y -= w;
			}
			else {
				choose[++cc] = pair(re[x], veg[i].v);
				ans[maxp] += 1LL * re[x] * veg[i].v;
				y -= re[x], re[x] = 0, set[x] = x - 1;
			}
			x = Find(x - 1);
		}
	}

	std::sort(choose + 1, choose + cc + 1);

	x = 1, y = maxp;
	while(x < y) {
		if(!re[x]) {++x; continue;}
		if(re[y] == m) {--y; continue;}
		if(re[x] <= m - re[y]) {re[y] += re[x]; re[x] = 0; continue;}
		re[x] -= m - re[y]; re[y] = m;
	}
	
	FOR(i, 1, maxp) cnt[i] = m - re[i];

	x = 1;
	DFR(i, maxp, 1) {
		ans[i - 1] = ans[i];
		while(cnt[i] > 0) 
			if(choose[x].c >= cnt[i]) {
				ans[i - 1] -= 1LL * cnt[i] * choose[x].v;
				choose[x].c -= cnt[i], cnt[i] = 0;
			}
			else {
				ans[i - 1] -= 1LL * choose[x].c * choose[x].v;
				cnt[i] -= choose[x].c, choose[x].c = 0, ++x;
			}
	}

	FOR(i, 1, q) printf("%lld\n", ans[ask[i]]);

	return 0;

}

int Find(int x) {
	return set[x] == x ? x : set[x] = Find(set[x]);
}

/*
g++ -o s s.cpp -O2; for((i = 1; i <= 25; ++i)) do cp vegetables$i.in s.in; ./s > s.out; diff vegetables$i.ans s.out -w > s.res; echo $i : $?; done;
*/

