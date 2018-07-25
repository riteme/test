#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define CMAX 1000000

static int BLOCKSIZE;

struct Modification {
    int pos;
    int prev;
    int color;
};

struct Interval {
    void reset(int l, int r, int t) {
        left = l;
        right = r;
        time = t;
        x = l / BLOCKSIZE;
        y = r / BLOCKSIZE;
        answer = 0;
    }

    int left;
    int right;
    int time;
    int x, y;
    int answer;
};

static bool cmp(const Interval *a, const Interval *b) {
    return a->x < b->x ||
           ((a->x == b->x && a->y < b->y) ||
            (a->x == b->x && a->y == b->y && a->time < b->time));
}

static int n, q;
static vector<int> G[NMAX + 10];
static int timestamp;
static int in[NMAX + 10];
static int out[NMAX + 10];
static bool marked[NMAX + 10];
static int seq[NMAX + 10];
static int mcnt, qcnt;
static Modification modify[NMAX + 10];
static Interval query[NMAX + 10];
static Interval *ptr[NMAX + 10];

static void dfs(int x) {
    marked[x] = true;
    in[x] = ++timestamp;

    for (size_t i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (!marked[v]) {
            dfs(v);
        }
    }

    out[x] = timestamp;
}

static void initialize() {
    scanf("%d", &n);
    BLOCKSIZE = max(int(pow(n, 5.0 / 3.0)), 1);

    for (int i = 1; i <= n; i++) {
        scanf("%d", seq + i);
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(1);

    scanf("%d", &q);

    for (int i = 1; i <= q; i++) {
        int command;
        scanf("%d", &command);

        if (command == 1) {
            int x;
            scanf("%d", &x);
            int l = in[x];
            int r = out[x];

            qcnt++;
            query[qcnt].reset(l, r, mcnt);
            ptr[qcnt] = query + qcnt;
        } else {
            int p, c;
            scanf("%d%d", &p, &c);
            p = in[p];

            mcnt++;
            modify[mcnt].pos = p;
            modify[mcnt].color = c;
        }
    }

    sort(ptr + 1, ptr + qcnt + 1, cmp);
}

static int answer;
static int cnt[CMAX + 10];
static int lastx = 1, lasty = 1, lastt = 0;

inline void add_color(int c) {
    cnt[c]++;
    if (cnt[c] == 1)
        answer++;
}

inline void del_color(int c) {
    cnt[c]--;
    if (cnt[c] == 0)
        answer--;
}

inline void expand_left(int x) {
    add_color(seq[x]);
}

inline void expand_right(int x) {
    add_color(seq[x]);
}

inline void shrink_left(int x) {
    del_color(seq[x]);
}

inline void shrink_right(int x) {
    del_color(seq[x]);
}

inline void perform(int x) {
    Modification &mod = modify[x];

    if (lastx <= mod.pos && mod.pos <= lasty) {
        del_color(seq[mod.pos]);
        add_color(mod.color);
    }

    mod.prev = seq[mod.pos];
    seq[mod.pos] = mod.color;
}

inline void undo(int x) {
    Modification &mod = modify[x];

    if (lastx <= mod.pos && mod.pos <= lasty) {
        del_color(seq[mod.pos]);
        add_color(mod.prev);
    }

    seq[mod.pos] = mod.prev;
}

int main() {
    initialize();

    expand_right(1);
    for (int i = 1; i <= qcnt; i++) {
        Interval *current = ptr[i];
        
        for (int p = lastt + 1; p <= current->time; p++) {
            perform(p);
        }

        for (int p = lastt; p > current->time; p--) {
            undo(p);
        }

        for (int p = lastx - 1; p >= current->left; p--) {
            expand_left(p);
        }

        for (int p = lasty + 1; p <= current->right; p++) {
            expand_right(p);
        }
        
        for (int p = lastx; p < current->left; p++) {
            shrink_left(p);
        }

        for (int p = lasty; p > current->right; p--) {
            shrink_right(p);
        }

        current->answer = answer;
        lastx = current->left;
        lasty = current->right;
        lastt = current->time;
    }

    for (int i = 1; i <= qcnt; i++)  {
        printf("%d\n", query[i].answer);
    }

    return 0;
}
