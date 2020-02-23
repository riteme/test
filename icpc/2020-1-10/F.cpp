#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200

struct vec {
    int x, y;

    vec operator+(const vec &z) const {
        return {x + z.x, y + z.y};
    }

    vec operator-(const vec &z) const {
        return {x - z.x, y - z.y};
    }
};

int dot(const vec &u, const vec &v) {
    return u.x * v.x + u.y * v.y;
}

int cross(const vec &u, const vec &v) {
    return u.x * v.y - u.y * v.x;
}

int n;
int cnt[NMAX + 10][NMAX + 10][3];
vec p[NMAX + 10];
double ans[NMAX + 10];

int sgn(int x) {
    return x ? (x > 0 ? 1 : -1) : 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &p[i].x, &p[i].y);

    for (int j = 1; j <= n; j++)
    for (int k = j + 1; k <= n; k++)
    for (int l = 1; l <= n; l++) if (l != j && l != k) {
        int d = sgn(cross(p[k] - p[j], p[l] - p[j]));
        if (d == 0)
            cnt[j][k][1] +=
            min(p[j].x, p[k].x) <= p[l].x && p[l].x <= max(p[j].x, p[k].x) &&
            min(p[j].y, p[k].y) <= p[l].y && p[l].y <= max(p[j].y, p[k].y);
        else
            cnt[j][k][d + 1]++;
    }

    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) if (j != i)
    for (int k = j + 1; k <= n; k++) if (k != i) {
        int cr = cross(p[k] - p[j], p[i] - p[j]);
        int d = sgn(cr);
        if (d == 0)
            continue;

        int c = cnt[j][k][d + 1] + cnt[j][k][1] - 1;
        ans[i] += (double) abs(cr) / (c + 1) / (c + 2) / (c + 3);
    }

    for (int i = 1; i <= n; i++)
        printf("%.10lf\n", ans[i]);
    return 0;
}