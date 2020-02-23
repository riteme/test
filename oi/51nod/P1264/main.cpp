#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

struct vec {
	vec() : x(0), y(0) {}
	vec(i64 _x, i64 _y) : x(_x), y(_y) {}

	i64 x, y;

	vec operator+(const vec &z) const {
		return {x + z.x, y + z.y};
	}

	vec operator-(const vec &z) const {
		return {x - z.x, y - z.y};
	}
};

i64 cross(const vec &u, const vec &v) {
	return u.x * v.y - u.y * v.x;
}

int sgn(i64 x) { return x < 0 ? -1 : (x > 0); }
bool on_segment(const vec &u, const vec &v, const vec &p) {
	return
	min(u.x, v.x) <= p.x && p.x <= max(u.x, v.x) &&
	min(u.y, v.y) <= p.y && p.y <= max(u.y, v.y);
}
bool is_intersect(const vec &p1, const vec &p2, const vec &p3, const vec &p4) {
	i64
	d1 = cross(p4 - p3, p1 - p3),
	d2 = cross(p4 - p3, p2 - p3),
	d3 = cross(p1 - p2, p1 - p3),
	d4 = cross(p1 - p2, p1 - p4);
	if (sgn(d1) * sgn(d2) < 0 && sgn(d3) * sgn(d4)< 0)
		return true;
	return
	(d1 == 0 && on_segment(p3, p4, p1)) ||
	(d2 == 0 && on_segment(p3, p4, p2)) ||
	(d3 == 0 && on_segment(p1, p2, p3)) ||
	(d4 == 0 && on_segment(p1, p2, p4));
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		vec p1, p2, p3, p4;
		scanf("%lld%lld%lld%lld%lld%lld%lld%lld",
			&p1.x, &p1.y,
			&p2.x, &p2.y,
			&p3.x, &p3.y,
			&p4.x, &p4.y);
		puts(is_intersect(p1, p2, p3, p4) ? "Yes" : "No");
	}
	return 0;
}
