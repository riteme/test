#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <ctime>
using namespace std;
const int NUM = 30;
const int RAD = 1000;
struct point {
    double x, y, val;
    point() {}
    point(double _x, double _y) : x(_x), y(_y) {}
} p[101], May[NUM], e1, e2;
int n;
double dis(point a, point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double judge(point t)  //评价函数，得到点t的评价值val
{
    double len = 0;
    for (int i = 0; i < n; i++)
        len += dis(t, p[i]);
    return len;
}
double Rand() {
    return rand() % (RAD + 1) / (1.0 * RAD);
}  //随机产生0-1的浮点数
point Rand_point(point a, point b)  //在a,b框定的四边形内随机生成点
{
    point tmp = point(a.x + (b.x - a.x) * Rand(), a.y + (b.y - a.y) * Rand());
    tmp.val = judge(tmp);
    return tmp;
}
void solve(double D) {
    for (int i = 0; i < NUM; i++)
        May[i] = Rand_point(e1, e2);  //步骤2
    while (D > 0.1)                   //步骤 3
    {
        for (int i = 0; i < NUM; i++)
            for (int j = 0; j < NUM; j++) {
                point tmp = Rand_point(point(May[i].x - D, May[i].y - D),
                                       point(May[i].x + D, May[i].y + D));
                if (tmp.val < May[i].val) {
                    May[i] = tmp;
                }
            }
        D *= 0.9;
    }
    double ans = 1LL << 45;
    point p;
    for (int i = 0; i < NUM; i++)
        if (May[i].val < ans) {
            ans = May[i].val;
            p = May[i];
        }
    printf("%.6f, %.6f", p.x, p.y);
}
int main() {
    srand(time(0));
    e1 = point(-10001, -10001);
    e2 = point(10001, 10001);
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++) {
            scanf("%lf%lf", &p[i].x, &p[i].y);
            e1.x = min(e1.x, p[i].x);  //框定初始范围
            e1.y = min(e1.y, p[i].y);
            e2.x = max(e2.x, p[i].x);
            e2.y = max(e2.y, p[i].y);
        }  
        solve(max(e2.y-e1.y,e2.x-e1.x));  
    }  
}  
