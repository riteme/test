#include <cstdio>
#include <cctype>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
size_t _pos = BUFFERSIZE;
char _buf[BUFFERSIZE];

void _getc(char &c) {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFFERSIZE, stdin);
    }
    c = _buf[_pos++];
}

template <typename T>
void read(T &x) {
    x = 0;
    char c;
    do _getc(c); while (!isdigit(c));
    do {
        x = x * 10 + c - '0';
        _getc(c);
    } while (isdigit(c));
}

typedef long long i64;

#define NMAX 100000

struct Node {
    int l, r;
    int cnt;
    Node *lch, *rch;

    Node(int _l, int _r) : l(_l), r(_r), cnt(0), lch(NULL), rch(NULL) {
        if (l < r) {
            int m = (l + r) / 2;
            lch = new Node(l, m);
            rch = new Node(m + 1, r);
        }
    }

    void update() {
        cnt = lch->cnt + rch->cnt;
    }

    Node *modify(int i, int v) {
        __builtin_prefetch(lch, 1, 1);
        __builtin_prefetch(rch, 1, 1);

        auto x = new Node(*this);

        if (l == r)
            x->cnt += v;
        else {
            if (i <= lch->r)
                x->lch = lch->modify(i, v);
            else
                x->rch = rch->modify(i, v);
            x->update();
        }

        return x;
    }
};

int query(Node *lb, Node *ub, int l, int r) {
    __builtin_prefetch(lb->lch, 0, 2);
    __builtin_prefetch(lb->rch, 0, 2);
    __builtin_prefetch(ub->lch, 0, 2);
    __builtin_prefetch(ub->rch, 0, 2);

    if (l <= lb->l && lb->r <= r)
        return lb->cnt - ub->cnt;

    int ret = 0;
    if (l <= lb->lch->r)
        ret += query(lb->lch, ub->lch, l, r);
    if (r > lb->lch->r)
        ret += query(lb->rch, ub->rch, l, r);
    return ret;
}

i64 n, K;
struct Point {
    int x, y;
} p[NMAX + 10];
int sx[NMAX + 10], sy[NMAX + 10];
int idy[NMAX + 10];
Node *suf[NMAX + 10];

bool cmpx(int i, int j) {
    return p[i].x < p[j].x;
}

bool cmpy(int i, int j) {
    return p[i].y < p[j].y;
}

int dist[NMAX + 10];

void initialize() {
    scanf("%lld%lld", &n, &K);
    // read(n); read(K);

    int mp = 0;
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        // read(x); read(y);
        p[i].x = x + y;
        p[i].y = x - y;
        sx[i] = sy[i] = i;

        if (!mp || p[i].x < p[mp].x || (p[i].x == p[mp].x && p[i].y < p[mp].y))
            mp = i;
    }

    for (int i = 1; i <= n; i++)
        dist[i] = max(abs(p[i].x - p[mp].x), abs(p[i].y - p[mp].y));
    sort(dist + 1, dist + n + 1);

    sort(sx + 1, sx + n + 1, cmpx);
    sort(sy + 1, sy + n + 1, cmpy);
    for (int i = 1; i <= n; i++)
        idy[sy[i]] = i;

    suf[n + 1] = new Node(1, n);
    for (int i = n; i >= 1; i--)
        suf[i] = suf[i + 1]->modify(idy[sx[i]], +1);
}

i64 eval(int L) {
    i64 ret = 0;
    for (int i = 1, l = 1, r = 1; i <= n; i++) {
        while (p[sx[l]].x < p[sx[i]].x - L)
            l++;
        while (r <= n && p[sx[r]].x <= p[sx[i]].x + L)
            r++;

        p[0].y = p[sx[i]].y - L;
        int lb = lower_bound(sy + 1, sy + n + 1, 0, cmpy) - sy;
        p[0].y = p[sx[i]].y + L;
        int ub = upper_bound(sy + 1, sy + n + 1, 0, cmpy) - sy;
        ret += query(suf[l], suf[r], lb, ub - 1);

        if (ret > 2 * K + n + 3)
            break;
    }

    return (ret - n) / 2;
}

int main() {
    initialize();

    int l = 1, r = n;
    int c = 0;
    while (l + 1 < r) {
        c++;
        int m = (l + r) / 2;
        i64 cnt = eval(dist[m]);

        if (cnt < K)
            l = m;
        else
            r = m;
    }

    l = dist[l];
    r = dist[r];
    printf("%d %d %d\n", l, r, c);
    while (l < r) {
        c++;
        int m = (l + r) / 2;
        i64 cnt = eval(m);

        if (cnt < K)
            l = m + 1;
        else
            r = m;
    }

    // for (int i = 0; i < 20; i++)
    //     printf("[%d] %lld\n", i, eval(i));

    printf("%d\n", l);
    fprintf(stderr, "%d\n", c);
    return 0;
}