// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
inline void chkmin(T &dest, T src) {
    if (src < dest)
        dest = src;
}

#define NMAX 100000
#define INFTY 1e15

struct State;

struct Owen {
    Owen() : deleted(false), next(NULL), prev(NULL) {}

    int x, v;
    bool deleted;
    State *state;
    Owen *next, *prev;

    bool operator<(const Owen &b) const {
        return x < b.x;
    }
};

inline double eval(Owen *a, Owen *b) {
    if (!b)
        return INFTY;
    if (b->x == a->x)
        return 0;

    assert(b->x > a->x);

    int delta_s = b->x - a->x;
    int delta_v = a->v - b->v;

    if (delta_v <= 0)
        return INFTY;
    return (double) delta_s / delta_v;
}

inline double eval(Owen *a) {
    return eval(a, a->next);
}

struct State {
    State(Owen *a)
        : ans(eval(a)), pos(a) {
        a->state = this;
    }

    double ans;
    Owen *pos;
};

struct cmp {
    bool operator()(const State *a, const State *b) const {
        return a->ans > b->ans;
    }
};

static int n, k;
static Owen owen[NMAX + 10];
static priority_queue<State *, vector<State *>, cmp> q;

void initialize() {
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &owen[i].x, &owen[i].v);
    }

    sort(owen + 1, owen + n + 1);

    for (int i = 1; i < n; i++) {
        owen[i].next = owen + i + 1;
        q.push(new State(owen + i));
    }

    for (int i = 2; i <= n; i++) {
        owen[i].prev = owen + i - 1;
    }
}

inline void cut(Owen *a) {
    if (a->prev) {
        a->prev->next = a->next;

        if (a->next)
            q.push(new State(a->prev));
        else
            a->prev->state = NULL;
    }

    if (a->next)
        a->next->prev = a->prev;

    a->deleted = true;
}

int main() {
#ifdef NDEBUG
    freopen("monument.in", "r", stdin);
    freopen("monument.out", "w", stdout);
#endif
    initialize();

    if (k == n) {
        puts("Forever");
        return 0;
    }

    while (k--) {
        State *u;
        do {
            u = q.top();
            q.pop();
        } while (u->pos->state != u);

        Owen *a = u->pos;
        Owen *b = a->next;
        assert(b);

        double wa = INFTY, wb = INFTY;

        if (a->prev) {
            chkmin(wa, eval(a->prev, b));
            chkmin(wb, eval(a->prev));
        }

        if (b->next) {
            chkmin(wb, eval(a, b->next));
            chkmin(wa, eval(b));
        }

        if (wa > wb)
            cut(a);
        else
            cut(b);
    }

    Owen *u = NULL;
    for (int i = 1; i <= n; i++) {
        if (!owen[i].deleted) {
            u = owen + i;
            break;
        }
    }

    double answer = INFTY;
    while (u) {
        if (u->next)
            chkmin(answer, eval(u));
        u = u->next;
    }

    if (answer > 1e14)
        puts("Forever");
    else
        printf("%.8lf\n", answer);

    return 0;
}
