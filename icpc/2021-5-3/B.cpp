#include <cstdio>
#include <cassert>
#include <cstring>

#include <tuple>
#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int KMAX = 50;
constexpr int NMAX = 1000000;
constexpr i64 INF = 0xffffffffffff;

enum Direction : int {
    N = 0, NE, E, SE, S, SW, W, NW, NMOVE, N_DIR
};

struct vec {
    constexpr vec() : x(0), y(0) {}
    constexpr vec(i64 _x, i64 _y) : x(_x), y(_y) {}

    i64 x, y;

    bool operator==(const vec &z) const {
        return x == z.x && y == z.y;
    }

    bool operator!=(const vec &z) const {
        return x != z.x || y != z.y;
    }

    bool operator<(const vec &z) const {
        return tie(x, y) < tie(z.x, z.y);
    }
};

constexpr vec dir[] = {
    {1, 0},  // y = c
    {1, 1},  // x - y = c
    {0, 1},  // x = c
    {-1, 1}  // x + y = c
};

vec sect(vec u1, vec v1, vec u2, vec v2) {
    // assert(v1 != v2);

    if (v1.x == 0) {
        i64 x = u1.x;
        i64 dx = u2.x - x;
        return vec(x, u2.y - dx * v2.y);
    }
    if (v2.y == 0) {
        i64 y = u1.y;
        i64 dy = u2.y - y;
        return vec(u2.x - dy * v2.x, y);
    }
    if (v2.x == 0 || v2.y == 0)
        return sect(u2, v2, u1, v1);

    i64 dx = u2.x - u1.x;
    i64 dy = u2.y - u1.y;
    // assert((dx + dy) % 2 == 0);

    i64 d = (dx + dy) / 2;
    return vec(u1.x + d, u1.y + v1.x * d);
}

struct Edge {
    int v, w;
};

int D, K, n, cnt;
bool allow[N_DIR];
vec p[KMAX + 10];
vec q[NMAX + 10];
i64 ans = INF;

i64 eval(i64 x, i64 y) {
    //                         N  NE  E  SE   S  SW   W  NW  O
    constexpr i64 dx[N_DIR] = {0,  1, 1,  1,  0, -1, -1, -1, 0};
    constexpr i64 dy[N_DIR] = {1,  1, 0, -1, -1, -1,  0,  1, 0};

    i64 rax = INF;
    for (int j = 0; j < N_DIR; j++) if (/*j != i && */allow[j]) {
        x -= dx[j];
        y -= dy[j];

        for (int i = 0; i < NMOVE; i++) if (allow[i]) {
            // if (dx[i] == -dx[j] && dy[i] == -dy[j])
            //     continue;

            for (int k = i + 1; k < NMOVE; k++) if (/*k != i && k != j && */allow[k]) {
                // if (dx[i] == -dx[k] && dy[i] == -dy[k])
                //     continue;
                // if (dx[j] == -dx[k] && dy[j] == -dy[k])
                //     continue;

                i64 a = dx[i], b = dx[k];
                i64 c = dy[i], d = dy[k];
                i64 det = a * d - b * c;
                if (det == 0)
                    continue;

                i64 t1 = d * x - b * y;
                i64 t2 = a * y - c * x;
                if (t1 % det || t2 % det)
                    continue;

                if (t1 * det < 0 || t2 * det < 0)
                    continue;

                i64 cost = (t1 + t2) / det;
                if (j < NMOVE)
                    cost++;
                rax = min(rax, cost);
            }

            i64 c = dx[i] * y - dy[i] * x;
            if (c == 0) {
                i64 d = dx[i] * x + dy[i] * y;
                if (d >= 0) {
                    i64 cost = max(abs(x), abs(y));
                    if (j < NMOVE)
                        cost++;
                    rax = min(rax, cost);
                }
            }
        }

        x += dx[j];
        y += dy[j];
    }

    return rax;
}

void add(i64 x0, i64 y0) {
    // assert(x0 % 2 == 0);
    // assert(y0 % 2 == 0);
    x0 /= 2;
    y0 /= 2;
    // if (visited.count({x0, y0}))
    //     return;
    // visited.insert({x0, y0});

    i64 sum = 0;
    for (int i = 1; i <= K; i++) {
        sum += eval(x0 - p[i].x / 2, y0 - p[i].y / 2);
        if (sum > ans)
            return;
    }

    ans = min(ans, sum);
}

void test(vec o) {
    int C = 10;
    for (i64 dx = -C; dx <= C; dx++)
    for (i64 dy = -C; dy <= C; dy++)
    if (abs(dx) + abs(dy) <= C) {
        i64 x = o.x + dx;
        i64 y = o.y + dy;
        if (x % 2 || y % 2)
            continue;

        // add(x, y);
        q[cnt++] = {x, y};
    }
}

void build() {
    for (int i = 1; i <= K; i++) {
        test(p[i]);
    }

    for (vec a : dir)
    for (vec b : dir)
    if (a != b)
    for (int i = 1; i <= K; i++)
    for (int j = i + 1; j <= K; j++) {
        vec o = sect(p[i], a, p[j], b);
        test(o);
    };

    // printf("%d\n", cnt);
    sort(q, q + cnt);
    cnt = unique(q, q + cnt) - q;

    srand(0x19260817);
    random_shuffle(q, q + cnt);
    for (int i = 0; i < cnt; i++) {
        add(q[i].x, q[i].y);
    }
}

int main() {
    scanf("%d", &D);

    allow[NMOVE] = true;
    for (int i = 0; i < D; i++) {
        char s[4];
        scanf("%s", s);
        if (strcmp(s, "N") == 0)
            allow[N] = true;
        else if (strcmp(s, "NE") == 0)
            allow[NE] = true;
        else if (strcmp(s, "E") == 0)
            allow[E] = true;
        else if (strcmp(s, "SE") == 0)
            allow[SE] = true;
        else if (strcmp(s, "S") == 0)
            allow[S] = true;
        else if (strcmp(s, "SW") == 0)
            allow[SW] = true;
        else if (strcmp(s, "W") == 0)
            allow[W] = true;
        else if (strcmp(s, "NW") == 0)
            allow[NW] = true;
    }

    scanf("%d", &K);
    for (int i = 1; i <= K; i++) {
        scanf("%lld%lld", &p[i].x, &p[i].y);
        p[i].x *= 2;
        p[i].y *= 2;
    }

    build();

    assert(ans < INF);
    printf("%lld\n", ans);
    return 0;
}