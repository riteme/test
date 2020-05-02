#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ctime>

#include <algorithm>

using namespace std;

#define EPS 1e-8

int n;
double r;

struct point {
  double x, y;
  bool in;
} p[100005], o;

inline double sqr(double x) { return x * x; }

inline double dis(point a, point b) {
  return hypot(a.x - b.x, a.y - b.y);
}

inline bool cmp(double a, double b) { return fabs(a - b) < EPS; }

point geto(point a, point b, point c) {
  double a1, a2, b1, b2, c1, c2;
  point ans;
  a1 = 2 * (b.x - a.x), b1 = 2 * (b.y - a.y),
  c1 = sqr(b.x) - sqr(a.x) + sqr(b.y) - sqr(a.y);
  a2 = 2 * (c.x - a.x), b2 = 2 * (c.y - a.y),
  c2 = sqr(c.x) - sqr(a.x) + sqr(c.y) - sqr(a.y);
  if (cmp(a1, 0)) {
    ans.y = c1 / b1;
    ans.x = (c2 - ans.y * b2) / a2;
  } else if (cmp(b1, 0)) {
    ans.x = c1 / a1;
    ans.y = (c2 - ans.x * a2) / b2;
  } else {
    ans.x = (c2 * b1 - c1 * b2) / (a2 * b1 - a1 * b2);
    ans.y = (c2 * a1 - c1 * a2) / (b2 * a1 - b1 * a2);
  }
  return ans;
}

void solve() {
//   scanf("%d", &n);
//   for (int i = 1; i <= n; i++) scanf("%lf%lf", &p[i].x, &p[i].y);
//   for (int i = 1; i <= n; i++) swap(p[rand() % n + 1], p[rand() % n + 1]);
  o = p[1];
  r = 0;
  for (int i = 1; i <= n; i++) {
    if ((p[i].in && dis(o, p[i]) < r + EPS) ||
        (!p[i].in && dis(o, p[i]) > r - EPS) )
        continue;
    o.x = (p[i].x + p[1].x) / 2;
    o.y = (p[i].y + p[1].y) / 2;
    r = dis(p[i], p[1]) / 2;
    for (int j = 2; j < i; j++) {
    //   if (dis(o, p[j]) < r || cmp(dis(o, p[j]), r)) continue;
        if ((p[j].in && dis(o, p[j]) < r + EPS) ||
            (!p[j].in && dis(o, p[j]) > r - EPS))
            continue;
      o.x = (p[i].x + p[j].x) / 2;
      o.y = (p[i].y + p[j].y) / 2;
      r = dis(p[i], p[j]) / 2;
      for (int k = 1; k < j; k++) {
        // if (dis(o, p[k]) < r || cmp(dis(o, p[k]), r)) continue;
        if ((p[k].in && dis(o, p[k]) < r + EPS) ||
            (!p[k].in && dis(o, p[k]) > r - EPS))
            continue;
        o = geto(p[i], p[j], p[k]);
        r = dis(o, p[i]);
      }
    }
  }
  printf("%.3lf %.3lf\n%.3lf\n", o.x, o.y, r);
}

int main() {
    int n0, m0;
    while (scanf("%d%d", &n0, &m0) != EOF) {
        n = n0 + m0;
        for (int i = 1; i <= n; i++)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        for (int i = 1; i <= n0; i++)
            p[i].in = true;
        for (int i = n0 + 1; i <= n; i++)
            p[i].in = false;
        srand(time(0));
        // random_shuffle(p + 1, p + n0 + 1);
        // random_shuffle(p + n0 + 1, p + n + 1);
        random_shuffle(p + 1, p + n + 1);
        solve();
    }
    return 0;
}