#include <cstdio>
#include <cstring>
#include <climits>

#include <set>
#include <deque>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define rep(i, l, r) for (int i = l; i <= (r); i++)

typedef long long i64;

static int n, L;
static int w[NMAX + 10], h[NMAX + 10];
static i64 f[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &L);

    rep(i, 1, n) {
        scanf("%d%d", h + i, w + i);
    }
}

struct State {
    State(int _x, int _y) : x(_x), y(_y) {}

    int x, y;

    i64 val() const {
        return f[x] + h[y];
    }

    bool operator<(const State &b) const {
        return val() < b.val() ||
               (val() == b.val() && x < b.x) ||
               (val() == b.val() && x == b.x && y < b.y);
    }
};

void pop(multiset<State> &s, int x, int y) {
    multiset<State>::iterator iter = s.find(State(x, y));
    s.erase(iter);
}

int main() {
    initialize();

    int l = 0, s = 0;
    deque<int> q;
    multiset<State> p;
    rep(i, 1, n) {
        s += w[i];
        while (s > L) {
            if (!q.empty())
                pop(p, l, q.front());

            s -= w[++l];

            if (!q.empty() && l == q.front())
                q.pop_front();
            else
                p.insert(State(l, q.front()));
        }

        while (!q.empty() && h[q.back()] <= h[i]) {
            int y = q.back();
            q.pop_back();
            int x = q.empty() ? l : q.back();
            pop(p, x, y);
        }

        p.insert(State(q.empty() ? l : q.back(), i));
        q.push_back(i);
        f[i] = p.begin()->val();
    }

    printf("%lld\n", f[n]);

    return 0;
}
