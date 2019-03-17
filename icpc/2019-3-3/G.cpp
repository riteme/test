#define NDEBUG

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

#include <set>
#include <algorithm>

using namespace std;

#define NMAX 200000
#define IN 1
#define OUT 2
#define EPS 1e-11

typedef long long i64;
typedef double d8;

struct Range {
	int l, r;

	bool operator<(const Range &b) const {
		return r < b.l;
	}
};

static int n;
static i64 H, t[NMAX + 10], p[NMAX + 10];
static struct Point {
	i64 y;
	int id, type;

	bool operator<(const Point &b) const {
		return y < b.y || (y == b.y && type < b.type);
	}
} seq[2 * NMAX + 10];
static set<Range> q;

/*inline bool sect(double x1, double y1, double x2, double y2, double y) {
	double vx = x2 - x1, vy = y2 - y1;
	assert(fabs(vy) >= EPS);
	double x = x1 + vx / vy * (y - y1);
	return x1 - EPS < x && x < x2 + EPS;
}*/

inline d8 delta(int i) {
	return (t[i + 1] - t[i]) / fabs(p[i] - p[i + 1]);
}

int main() {
	scanf("%d%lld", &n, &H);
	for (int i = 1; i <= n; i++)
		scanf("%lld%lld", t + i, p + i);
	for (int i = 1; i <= n; i++) {
		seq[2*i - 1] = {p[i] - H, i, IN};
		seq[2*i] = {p[i], i, OUT};
	}
	seq[2*n+1] = {-H, 0, IN};
	seq[2*n+2] = {0, 0, OUT};
	sort(seq + 1, seq + 2 * n + 3);
	d8 ans = 0, sum = 0, k = 0, last = -1e9;
	for (int _i = 1; _i <= 2*n+2; _i++) {
		auto &cur = seq[_i];
		int i = cur.id;
        sum += k * (cur.y - last);
        last = cur.y;
		ans = max(ans, sum);
		if (cur.type == IN) {
			if (i && p[i - 1] > p[i]) k += delta(i - 1);
			else if (i && p[i - 1] < p[i]) k -= delta(i - 1);
			if (i < n && p[i + 1] > p[i]) k += delta(i);
			else if (i < n && p[i + 1] < p[i]) k -= delta(i);

			if (q.empty())
				q.insert({i, i});
            else {
                int l = i, r = i;
                auto ri = q.upper_bound({i, i});
                if (ri == q.end()) {
                    auto li = q.rbegin();
                    if (i - 1 == li->r) {
                        l = li->l;
                        q.erase(q.find(*li));
                    }
                } else {
                    if (ri != q.begin()) {
                        auto li = prev(ri);
                        if (i - 1 == li->r) {
                            l = li->l;
                            q.erase(li);
                        }
                    }
                    if (i + 1 == ri->l) {
                        r = ri->r;
                        q.erase(ri);
                    }
                }
                q.insert({l, r});

                if (l < i && p[i - 1] == p[i]) sum += t[i] - t[i - 1];
                if (i < r && p[i + 1] == p[i]) sum += t[i + 1] - t[i];
            }
		} else {
			if (i && p[i - 1] > p[i]) k -= delta(i - 1);
			else if (i && p[i - 1] < p[i]) k += delta(i - 1);
			if (i < n && p[i + 1] > p[i]) k -= delta(i);
			else if (i < n && p[i + 1] < p[i]) k += delta(i);

			auto iter = q.lower_bound({i, i});
			assert(iter != q.end());
			int l = iter->l, r = iter->r;
			//printf("[%d, %d]\n", l, r);
			if (l < i && p[i - 1] == p[i]) sum -= t[i] - t[i - 1];
			if (i < r && p[i + 1] == p[i]) sum -= t[i + 1] - t[i];
			q.erase(iter);
			if (i > l) q.insert({l, i - 1});
			if (i < r) q.insert({i + 1, r});
		}
		ans = max(ans, sum);
		//printf("i = %d, k = %.4lf, sum = %.4lf\n", i, k, sum);
	}
	printf("%.12lf\n", ans);
	return 0;
}
