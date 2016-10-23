/**
 * 最开始觉得数据范围是不是太小了，后来发现自己Too YOUND Too NAIVE...
 * 最初看的时候忘记了游客来到的时间，可能需要客车停下来等待
 *
 * 首先不考虑优化，纯模拟O(n)可以计算到每一个点的时间
 * 现在来做k次优化......
 * maxrange[i]表示从i开始到maxrange[i]均不需要等人来齐，O(n)的递推
 * 那么每优化一条路i，就会导致[i + 1, maxrange[i]]的endtime需要更新
 * 同时[1, maxrange[i]]的maxrange也需要更新
 *
 * 刚才考虑的是后事，现在要做的就是贪心地选出该被优化的路径
 * 一条路的修改会导致所有与这条路相关的人的等待时间减少
 * 实际上就是终点在[i, maxrange[i]]中的人 (这一步是关键)
 * (即使起点在i之后也会有关系，因为从i到它的起点是不需要等其它人的，所以车子来得越早越好)
 * 因此做个前缀和暴力找一下就好了......
 *
 * 由于优化之间是互不影响的，所以可以贪心
 */

#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000
#define MMAX 10000
// #define NMAX 100
// #define MMAX 100

typedef long long int64;

static int n, m;
static int64 k;
static int64 dist_to_next[NMAX + 10];
static int64 starttime[MMAX + 10];
static int from[MMAX + 10];
static int to[MMAX + 10];
static int64 pre[NMAX + 10];
static int64 mintime[NMAX + 10];
static int64 endtime[MMAX + 10];
static int maxrange[NMAX + 10];

static void initialize() {
    scanf("%d%d%lld", &n, &m, &k);

    for (int i = 1; i < n; i++) {
        scanf("%lld", dist_to_next + i);
    }  // for

    for (int i = 1; i <= m; i++) {
        int64 t;
        int a, b;
        scanf("%lld%d%d", &t, &a, &b);

        starttime[i] = t;
        from[i] = a;
        to[i] = b;
        pre[b]++;
        mintime[a] = max(mintime[a], t);
    }  // for

    for (int i = 1; i <= n; i++) {
        pre[i] += pre[i - 1];
    }  // for
}

inline int64 optimize(int x) {
    return pre[maxrange[x]] - pre[x];
}

int main() {
    initialize();

    for (int i = 2; i <= n; i++) {
        endtime[i] = max(endtime[i - 1], mintime[i - 1]) + dist_to_next[i - 1];
    }  // for

    int pos = 2;
    for (int i = 1; i < n; i++) {
        pos = max(pos, i + 1);
        while (pos < n && endtime[pos] > mintime[pos]) {
            pos++;
        }  // while

        maxrange[i] = pos;
    }  // for

    int64 answer = 0;
    for (int i = 1; i <= m; i++) {
        answer += endtime[to[i]] - starttime[i];
    }  // for

    int64 opt = 0;
    while (k--) {
        int pivot = 0;
        for (int i = 1; i < n; i++) {
            if (dist_to_next[i] == 0)
                continue;
            if (optimize(i) > optimize(pivot))
                pivot = i;
        }  // for

        if (pivot == 0)
            break;

        opt += optimize(pivot);
        dist_to_next[pivot]--;

        int right = maxrange[pivot];
        for (int i = pivot + 1; i <= min(right, n - 1); i++) {
            endtime[i] =
                max(endtime[i - 1], mintime[i - 1]) + dist_to_next[i - 1];
        }  // for

        int pos = 2;
        for (int i = 1; i <= min(right, n - 1); i++) {
            pos = max(pos, i + 1);
            while (pos < n && endtime[pos] > mintime[pos]) {
                pos++;
            }  // while

            maxrange[i] = pos;
        }  // for
    }      // while

    printf("%lld\n", answer - opt);

    return 0;
}  // function main
