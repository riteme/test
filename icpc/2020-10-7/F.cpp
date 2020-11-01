#include <cmath>
#include <cstdio>
#include <cstring>

#include <queue>
#include <random>
#include <algorithm>

using namespace std;

using d8 = double;

const d8 PI = acos(-1);
constexpr int NMAX = 1000;

d8 randf() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_real_distribution<d8> dist(0.0, 1.0);
    return dist(gen);
}

struct vec {
    d8 x, y;

    d8 len() const {
        return hypot(x, y);
    }

    vec operator*(d8 k) const {
        return {x * k, y * k};
    }

    d8 operator*(const vec &z) const {
        return x * z.x + y * z.y;
    }

    vec operator+(const vec &z) const {
        return {x + z.x, y + z.y};
    }

    vec operator-(const vec &z) const {
        return {x - z.x, y - z.y};
    }
};

int n;
vec P[NMAX + 10];

d8 eval(const vec &o) {
    d8 r = 0;
    for (int i = 1; i <= n; i++) {
        r += (P[i] - o).len();
    }
    return r;
}

void _main() {
    scanf("%d", &n);

    vec O = {0, 0};
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", &P[i].x, &P[i].y);
        O = O + P[i];
    }
    O = O * (1.0 / n);

    d8 s0 = 0;
    for (int i = 1; i <= n; i++) {
        vec d = P[i] - O;
        s0 += d * d;
    }
    s0 = sqrt(s0 / n);

    constexpr d8 e = 0.999;
    constexpr int D = 50;
    constexpr int M = 20;
    constexpr int C = 500000;

    vec ans = O;
    d8 mi = eval(O);

    for (int _ = 0; _ < M; _++) {
        d8 T = 1;
        d8 s = s0 / 2;

        queue<vec> q;
        q.push(O);

        int cnt = 0;
        do {
            vec u = q.front();
            q.pop();

            for (int _ = 0; _ < D; _++) {
                cnt++;

                d8 t = randf() * 2 * PI;
                d8 dx = cos(t) * s;
                d8 dy = sin(t) * s;

                vec v = {u.x + dx, u.y + dy};
                d8 w = eval(v);
                if (w < mi) {
                    mi = w;
                    ans = v;
                    q.push(v);
                } else {
                    d8 p = exp((mi - w) / T);
                    if (randf() < p)
                        q.push(v);
                }
            }

            T *= e;
            s *= e;
        } while (cnt < C && q.size() && T > 0);
    }

    printf("%.10lf %.10lf\n", ans.x, ans.y);

    /*
    d8 x = eval({0, 1.732051});
    d8 y = mi;
    printf("x=%.10lf, y=%.10lf\n", x, y);
    printf("Δ=%.10lf\n", fabs((y - x) / x));
    */
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        _main();
    }
    return 0;
}
