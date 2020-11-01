#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>

using namespace std;

constexpr int NMAX = 300;
constexpr int DLEFT = 0;
constexpr int DRIGHT = 1;
constexpr int DUP = 2;
constexpr int DDOWN = 3;

const char *NO_WIN = "no window at given position";
const char *NO_FIT = "window does not fit";
const char *MOVING = "moved %d instead of %d";

struct win_t {
    win_t() : x(0), y(0) {}
    win_t(int _x, int _y, int _w, int _h)
        : x(_x), y(_y), w(_w), h(_h) {}

    int x, y, w, h;

    int left() {
        return x;
    }
    int right() {
        return x + w - 1;
    }
    int top() {
        return y;
    }
    int bottom() {
        return y + h - 1;
    }

    bool contain(int x0, int y0) {
        return x <= x0 && x0 < x + w &&
            y <= y0 && y0 < y + h;
    }
    bool contain(win_t &w0) {
        return contain(w0.left(), w0.top()) &&
            contain(w0.left(), w0.bottom()) &&
            contain(w0.right(), w0.top()) &&
            contain(w0.right(), w0.bottom());
    }

    bool overlap(win_t &w0) {
        int l = max(left(), w0.left());
        int r = min(right(), w0.right());
        if (r < l)
            return false;

        l = max(top(), w0.top());
        r = min(bottom(), w0.bottom());
        return l <= r;
    }

    win_t join(win_t &w0) {
        int l = min(left(), w0.left());
        int r = max(right(), w0.right());
        int t = min(top(), w0.top());
        int b = max(bottom(), w0.bottom());
        return {l, t, r - l + 1, b - t + 1};
    }
};

int _cur;
char op[64];
win_t desktop;
vector<win_t> win;

template <typename ... TArgs>
void report(const char *fmt, const TArgs& ... args) {
    printf("Command %d: %s - ", _cur, op);
    printf(fmt, args...);
    puts("");
}

int click(int x, int y) {
    for (int i = 0; i < win.size(); i++) {
        if (win[i].contain(x, y))
            return i;
    }

    report(NO_WIN);
    return -1;
}

bool fit(win_t &w, int ex = -1) {
    if (!desktop.contain(w))
        goto fuck;

    for (int i = 0; i < win.size(); i++) {
        if (i != ex && win[i].overlap(w))
            goto fuck;
    }

    return true;

fuck:
    report(NO_FIT);
    return false;
}

void wopen(int x, int y, int w, int h) {
    win_t w0 = {x, y, w, h};
    if (!fit(w0))
        return;
    win.push_back(w0);
}

void wclose(int x, int y) {
    int z = click(x, y);
    if (z < 0)
        return;
    win.erase(win.begin() + z);
}

void wresize(int x, int y, int w, int h) {
    int z = click(x, y);
    if (z < 0)
        return;

    win_t tmp = win[z];
    win[z].w = w;
    win[z].h = h;
    if (!fit(win[z], z)) {
        win[z] = tmp;
        return;
    }
}

vector<win_t> mov;

bool check() {
    for (auto &w : mov) {
        if (!desktop.contain(w))
            return false;
    }
    return true;
}

void push(int dir) {
    function<bool(int, int)> cmp[] = {
        [](int i, int j) { return win[i].x > win[j].x; },
        [](int i, int j) { return win[i].x < win[j].x; },
        [](int i, int j) { return win[i].y > win[j].y; },
        [](int i, int j) { return win[i].y < win[j].y; }
    };

    vector<int> s(win.size());
    iota(s.begin(), s.end(), 0);
    sort(s.begin(), s.end(), cmp[dir]);

    for (int i : s)
    for (int j : s) {
        if (j == i)
            break;

        win_t m = win[j].join(mov[j]);
        if (!m.overlap(mov[i]))
            continue;

        if (dir == DLEFT)
            mov[i].x = m.left() - mov[i].w;
        else if (dir == DRIGHT)
            mov[i].x = m.right() + 1;
        else if (dir == DUP)
            mov[i].y = m.top() - mov[i].h;
        else
            mov[i].y = m.bottom() + 1;
    }
}

void push(int z, int dx, int dy, int dir) {
    mov = win;
    mov[z].x += dx;
    mov[z].y += dy;
    push(dir);
}

int sgn(int x) {
    return x < 0 ? -1 : (x > 0);
}

void wmove(int x, int y, int dx, int dy) {
    int z = click(x, y);
    if (z < 0)
        return;

    int dir = dx ? (dx > 0 ? DRIGHT : DLEFT) : (dy > 0 ? DDOWN : DUP);
    int vx = sgn(dx), vy = sgn(dy);
    int d = abs(dx + dy);
    int l = 0, r = d;
    while (l < r) {
        int m = (l + r) / 2 + 1;
        push(z, vx * m, vy * m, dir);
        if (check())
            l = m;
        else
            r = m - 1;
    }

    if (l != d)
        report(MOVING, l, d);

    push(z, vx * l, vy * l, dir);
    win.swap(mov);
}

int main() {
    scanf("%d%d", &desktop.w, &desktop.h);

    for (_cur = 1; scanf("%s", op) != EOF; _cur++) {
        if (op[0] == 'O') {
            int x, y, w, h;
            scanf("%d%d%d%d", &x, &y, &w, &h);
            wopen(x, y, w, h);
        } else if (op[0] == 'C') {
            int x, y;
            scanf("%d%d", &x, &y);
            wclose(x, y);
        } else if (op[0] == 'R') {
            int x, y, w, h;
            scanf("%d%d%d%d", &x, &y, &w, &h);
            wresize(x, y, w, h);
        } else if (op[0] == 'M') {
            int x, y, dx, dy;
            scanf("%d%d%d%d", &x, &y, &dx, &dy);
            wmove(x, y, dx, dy);
        }
    }

    printf("%zu window(s):\n", win.size());
    for (auto &w : win) {
        printf("%d %d %d %d\n", w.x, w.y, w.w, w.h);
    }

    return 0;
}
