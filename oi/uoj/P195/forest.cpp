/**
 * 没有想到离线从左至右做扫描线来维护每棵树的形态
 * 对于每个0操作，它的父亲是上一个1操作，但是前提是这个1操作有效
 * 可以用1操作将操作序列分为很多段，每一段的0操作的父亲都是
 * 这一段开始的1操作
 * 如果1操作无效，那么这一段的0操作全部向前合并
 * 因此做法就大致出来了，首先是所有真实的点
 * 其次是所有1操作都建一个点，但没有点权
 * 这样将所有0操作新建的真实点与最靠近的1操作的虚点相连
 * 每次1操作激活时，将虚点与对应真实点相连
 * 失效时，则与最靠近的1号操作相连
 * 最后，单旋Splay身败名裂，被光荣的卡成n^2
 */

#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define QMAX 200000
#define LCTSIZE (QMAX + QMAX)

template <typename T>
inline void trymax(T &dest, const T src) {
    if (src > dest)
        dest = src;
}

template <typename T>
inline void trymin(T &dest, const T src) {
    if (src < dest)
        dest = src;
}

struct Command {
    int type;
    int a, b, c;
    int val;
};

static int n, q, t;
static struct {
    int left, right;
} range[QMAX + 10];
static Command comm[QMAX + 10];
static vector<Command *> bucket[QMAX + 10];
static vector<Command *> addlist[NMAX + 10];
static vector<Command *> dellist[NMAX + 10];

class LCT {
 public:
    void initialize() {
        memset(father, 0, sizeof(father));
        memset(child, 0, sizeof(child));
        memset(weight, 0, sizeof(weight));
        memset(sum, 0, sizeof(sum));
        memset(reversed, 0, sizeof(reversed));

        for (int i = 1; i <= t; i++) {
            weight[i] = 1;
        }
    }

    void splay(int x) {
        clear_marks(x);

        while (father[x] > 0) {
            int f = father[x];
            int pf = father[f];
            if (pf > 0) {
                if (x == child[f][L] && f == child[pf][L])
                    rotate(pf, L);
                else if (x == child[f][R] && f == child[pf][R])
                    rotate(pf, R);
            }

            if (x == child[f][L])
                rotate(f, L);
            else
                rotate(f, R);
        }
    }

    void access(int x) {
        assert(x < LCTSIZE);
        splay(x);
        father[child[x][R]] = -x;
        child[x][R] = 0;
        update(x);

        while (father[x]) {
            int top = -father[x];
            assert(top > 0);

            splay(top);
            father[child[top][R]] = -top;
            father[x] = top;
            child[top][R] = x;
            update(top);
            x = top;
        }
    }

    void make_root(int x) {
        access(x);
        splay(x);
        reversed[x] ^= 1;
    }

    void link(int u, int v) {
        access(u);
        splay(u);

        make_root(v);

        father[child[u][R]] = -u;
        father[v] = u;
        child[u][R] = v;
        update(u);
    }

    void cut(int x) {
        int fa = find_father(x);
        assert(fa);

        access(fa);
        splay(x);
        father[x] = 0;
    }

    void select_path(int u, int v) {
        make_root(u);
        access(v);
        splay(u);
    }

    bool is_ancester(int u, int v) {
        if (u == v)
            return true;

        // root?
        make_root(1);
        access(v);
        access(u);
        splay(v);
        return father[v] == -u;
    }

    static constexpr int L = 0;
    static constexpr int R = 1;

    int father[LCTSIZE + 10];
    int child[LCTSIZE + 10][2];
    int weight[LCTSIZE + 10];
    int sum[LCTSIZE + 10];
    bool reversed[LCTSIZE + 10];

    void update(int x) {
        sum[x] = weight[x] +
                 (child[x][L] ? sum[child[x][L]] : 0) +
                 (child[x][R] ? sum[child[x][R]] : 0);
    }

    void pushdown(int x) {
        if (reversed[x]) {
            swap(child[x][L], child[x][R]);
            reversed[child[x][L]] ^= 1;
            reversed[child[x][R]] ^= 1;
            reversed[x] = 0;
        }
    }

    void clear_marks(int x) {
        if (father[x] > 0)
            clear_marks(father[x]);
        pushdown(x);
    }

    void rotate(int x, int d) {
        assert(x);
        assert(child[x][d]);
        assert(!reversed[x]);

        int y = child[x][d];
        child[x][d] = child[y][d ^ 1];
        child[y][d ^ 1] = x;

        if (child[x][d])
            father[child[x][d]] = x;
        father[y] = father[x];
        father[x] = y;
        if (father[y] > 0) {
            if (x == child[father[y]][L])
                child[father[y]][L] = y;
            else
                child[father[y]][R] = y;
        }

        update(x);
        update(y);
    }

    int find_father(int x) {
        access(x);
        splay(x);

        assert(!reversed[x]);
        int ret = child[x][L];
        pushdown(ret);
        while (child[ret][R]) {
            ret = child[ret][R];
            pushdown(ret);
        }

        return ret;
    }
};

static LCT lct;

void initialize() {
    scanf("%d%d", &n, &q);

    t = 1;
    int cnt = 1;
    range[1] = {1, n};
    comm[0] = {1, 1, n, 1, 1};
    addlist[1].push_back(comm);
    for (int i = 1; i <= q; i++) {
        Command &cur = comm[i];
        scanf("%d", &cur.type);

        switch (cur.type) {
            case 0: {
                scanf("%d%d", &cur.a, &cur.b);
                t++;
                cur.val = t;
                range[t] = {cur.a, cur.b};
            } break;

            case 1: {
                scanf("%d%d%d", &cur.a, &cur.b, &cur.c);
                cnt++;
                cur.val = cnt;
                trymax(cur.a, range[cur.c].left);
                trymin(cur.b, range[cur.c].right);

                if (cur.a <= cur.b) {
                    addlist[cur.a].push_back(&cur);
                    dellist[cur.b].push_back(&cur);
                }
            } break;

            case 2: {
                scanf("%d%d%d", &cur.a, &cur.b, &cur.c);
                cur.type = -1;
                bucket[cur.a].push_back(&cur);
            } break;
        }
    }

    lct.initialize();
    int last = t + 1;
    comm[0].type = 0;
    comm[0].val += t;
    for (int i = 1; i <= q; i++) {
        Command &cur = comm[i];

        if (cur.type == 0)
            lct.link(last, cur.val);
        else if (cur.type == 1) {
            cur.val += t;
            cur.type = last;
            lct.link(last, cur.val);
            last = cur.val;
        }
    }
}

int main() {
#ifdef USE_FILE_IO
    freopen("forest.in", "r", stdin);
#endif
    initialize();

    for (int i = 1; i <= n; i++) {
        for (auto cur : addlist[i]) {
            if (cur->type) {
                lct.make_root(cur->type);
                lct.cut(cur->val);
            }

            lct.link(cur->c, cur->val);
        }

        for (auto que : bucket[i]) {
            int u = que->b, v = que->c;
            if (u == v) {
                que->val = 0;
                continue;
            }

            if (u > v)
                swap(u, v);

            lct.make_root(1);
            lct.access(v);
            lct.access(u);
            lct.splay(v);

            que->val = lct.sum[v];
            if (lct.father[v] != -u) {
                lct.access(-lct.father[v]);
                lct.splay(u);
                que->val += lct.sum[u];
            }
        }

        for (auto cur : dellist[i]) {
            lct.make_root(cur->c);
            lct.cut(cur->val);
            lct.link(cur->type, cur->val);
        }
    }

    for (int i = 1; i <= q; i++) {
        if (comm[i].type == -1)
            printf("%d\n", comm[i].val);
    }

    return 0;
}
