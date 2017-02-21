/**
 * 首先我觉得最后的时间应该是中位数，但是我无法证明
 * 但是另外一点，如果全部统一为x，那么令代价为H(x)
 * 你会发现H(x)是一个单峰函数
 * 并且是分段的，也就是意味着是一个下凸包
 * 对于叶子节点，它的H函数就是y = x
 * 对于内部节点，首先将儿子节点的加一条边修改其凸包
 * 然后将它们加合起来，就是该节点的H(x)
 * 如何加一条边？这边的权值为w
 * 假设最优值取在[L, R]中间
 * 考虑到边权可以无限增大，所以对于x >= R + w的，可以直接变为[L, R]，
 * 前提是需要花费x - R - w的代价
 * 对于[L + w, R + w]的x，走过w这条边后，就是儿子中[L, R]的情况
 * 由于边权最多减少w，所以只有[L, L + w]能够享受到[L, R]的好处
 * 对于小于L的x，先要花费w的代价往[L, R]靠近，然后保持原来的形状
 * 最后的操作就是向上平移左边凸包，右边添加三段，斜率分别为-1, 0, 1
 * 然后如何凸包加合？
 * 由于最右边的斜率始终是儿子个数
 * H(0)始终等于边权之和。
 * 每个转折点只会导致之前斜率+1，
 * 所以我们只用维护所有转折点的位置即可
 * 使用可并堆或者启发式合并来维护
 */

#define NDEBUG

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

#define NMAX 600000
#define CMAX 1000000000

typedef long long i64;

class ConvexHull {
 public:
    ConvexHull() : right(1) {
        q.push(0);
        q.push(0);
    }

    void move_y(i64 w) {
        i64 L, R;
        for (int i = 0; i < right; i++) {
            if (i == right - 1)
                R = q.top();
            q.pop();
        }  // for
        L = q.top();
        q.pop();
        q.push(L + w);
        q.push(R + w);
        right = 1;
    }

    size_t size() const {
        return q.size();
    }

    friend ConvexHull *merge_hull(ConvexHull *a, ConvexHull *b);
    friend i64 minimize(ConvexHull *h);

 private:
    i64 right;
    priority_queue<i64> q;
};  // class ConvexHull

ConvexHull *merge_hull(ConvexHull *a, ConvexHull *b) {
    if (!a)
        return b;
    if (!b)
        return a;
    if (a->size() < b->size())
        swap(a, b);

    a->right += b->right;
    while (!b->q.empty()) {
        a->q.push(b->q.top());
        b->q.pop();
    }  // while

    return a;
}

static int n;
static vector<int> G[NMAX + 10];
static i64 dist[NMAX + 10];
static ConvexHull *convex[NMAX + 10];
static vector<i64> seq;

i64 minimize(ConvexHull *h) {
    i64 sum = 0;
    for (int i = 2; i <= n; i++) {
        sum += dist[i];
    }  // for

    for (int i = 0; i < h->right; i++) {
        h->q.pop();
    }  // for

    while (!h->q.empty()) {
        seq.push_back(h->q.top());
        h->q.pop();
    }  // while

    i64 lastx = 0;
    for (i64 k = seq.size() - 1; k >= 0; k--) {
        sum -= (k + 1) * (seq[k] - lastx);
        lastx = seq[k];
    }  // for

    return sum;
}

void initialize() {
    int a, b;
    scanf("%d%d", &a, &b);
    n = a + b;

    for (int i = 2; i <= n; i++) {
        int father;
        i64 w;
        scanf("%d%lld", &father, &w);

        G[father].push_back(i);
        dist[i] = w;
    }  // for
}

void dfs(int x) {
    bool has_child = false;
    for (int v : G[x]) {
        has_child = true;
        dfs(v);
        convex[v]->move_y(dist[v]);
        convex[x] = merge_hull(convex[x], convex[v]);
    }  // foreach in G[x]

    if (!has_child)
        convex[x] = new ConvexHull;
}

int main() {
    initialize();
    dfs(1);
    printf("%lld\n", minimize(convex[1]));

    return 0;
}  // function main
