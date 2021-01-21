#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using d8 = long double;

constexpr int TMAX = 500;

d8 H, L, W, P;

bool check(d8 R) {
	d8 x = R;
	d8 y = R + L;
	d8 vx = W / 2;
	d8 vy = H;

	if (x >= vx)
		return false;
	
	d8 len = hypotl(vx, vy);
	vx /= len;
	vy /= len;
	d8 proj = x * vx + y * vy;

	if (proj <= P) {
		d8 d = sqrtl(fmaxl(0.0, x * x + y * y - proj * proj));
		return d >= R;
	} else {
		d8 d = hypotl(x - W / 2, y - H);
		return d >= R;
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%Lf%Lf%Lf", &H, &L, &W);
		P = hypotl(H, W / 2);

		d8 lo = 0, hi = 1e20;
		for (int _ = 0; _ < TMAX; _++) {
			d8 mi = (lo + hi) * 0.5;
			if (check(mi))
				lo = mi;
			else
				hi = mi;
		}

		d8 ans = (lo + hi) * 0.5;
		printf("%.15Lf\n", ans);
	}
	return 0;
}
