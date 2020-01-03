#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAXN = 1005;
const double eps = 1e-12;
const double tpi = acos(-1.0);
int n;
double Ans[MAXN];
double Sum[MAXN];
struct Circle {
    double x, y, r;
    inline double f(const double& t) {
        return (t * r + sin(t) * x - cos(t) * y) * r;
    }
    inline double oint(const double& theta_l, const double theta_r) {
        return r * (r * (theta_r - theta_l) + x * (sin(theta_r) - sin(theta_l)) - y * (cos(theta_r) - cos(theta_l)));
//		return f(theta_r) - f(theta_l);
    }
    inline bool operator == (const Circle& o) const {
        return (x==o.x)&&(y==o.y)&&(r==o.r);
    }
    inline bool operator < (const Circle& o) const {
        return (x==o.x)?((y==o.y)?(r<o.r):(y<o.y)):(x<o.x);
    }
}C[MAXN];
inline double defabs(const double&x) {
    return (x<0)?(-x):x;
}
int tot;
int N;
pair<double, bool> Pt[(MAXN<<1)+5];
inline double sdCross(const double xa, const double ya, const double xb, const double yb) {
	return xa * yb - ya * xb;
}
inline double revCross(const Circle& x, const double& a, const double& b) {
	return sdCross(-x.r*cos(a), -x.r*sin(a), -x.r*cos(b), -x.r*sin(b));
}
inline double defCross(const Circle& x, const double& a, const double& b) {
	return sdCross(x.x+x.r*cos(a), x.y+x.r*sin(a), x.x+x.r*cos(b), x.y+x.r*sin(b));
}
bool dcmp(const pair<double,bool>&a, const pair<double,bool>&b) {
	static double t;
	t = a.first - b.first;
	return (fabs(t)<=eps)?0:((t<0)?1:0);
}
inline void Calc(const int& x) {
    tot = 0;
    register int Sm = 0;
    register double DistX, DistY, Dist, Angle, Cosine, Theta, Thetb;
    for (register int i = 1; i <= n; ++i) {
        if (i == x) continue;
        DistX = C[i].x - C[x].x;
        DistY = C[i].y - C[x].y;
        Dist = sqrt(DistX * DistX + DistY * DistY);
        if (C[x].r + Dist <= C[i].r + eps) {
        	++Sm;
        	continue;
        }
		if (C[i].r + Dist <= C[x].r + eps || Dist >= C[i].r + C[x].r - eps) continue;
        Angle = atan2(DistY, DistX),
        Cosine = acos((Dist*Dist+C[x].r*C[x].r-C[i].r*C[i].r)/(2.0*Dist*C[x].r));
        if (!Cosine) continue;
        Theta = Angle - Cosine;
        Thetb = Angle + Cosine;
        if (Theta < -tpi) Theta += tpi * 2;
        if (Thetb >= tpi) Thetb -= tpi * 2;
        if (Theta > Thetb - eps) ++Sm;
        Pt[++tot] = make_pair(Theta, 0);
        Pt[++tot] = make_pair(Thetb, 1);
    }
    Pt[0] = make_pair(-tpi, 0);
    Pt[++tot] = make_pair(tpi, 1);
    sort(Pt + 1, Pt + tot, dcmp);
    for (register int i = 1; i <= tot; ++i) { 
		Ans[Sm+1] += C[x].oint(Pt[i-1].first, Pt[i].first);
//  or  Ans[Sm+1] += (Pt[i].first - Pt[i-1].first) * C[x].r * C[x].r - revCross(C[x], Pt[i-1].first, Pt[i].first) + defCross(C[x], Pt[i-1].first, Pt[i].first);
        (Pt[i].second)?(--Sm):(++Sm);
    }
}
int main() {
    scanf("%d", &n);
    N = n;
    for (register int i = 0, j = 1; j <= n; ++j) {
        ++i;
        scanf("%lf%lf%lf", &C[i].x , &C[i].y, &C[i].r);
    }
    sort(C + 1, C + 1 + n);
    n = unique(C + 1, C + 1 + n) - C - 1;
    for (register int i = 1; i <= n; ++i) {
        Calc(i);
    }
    for (register int i = 1; i <= N; ++i) {
        printf("[%d] = %.3lf\n", i, max(0.0, (Ans[i] - Ans[i+1])/2));
    }
    return 0;
}
