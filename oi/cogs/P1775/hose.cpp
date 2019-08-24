/**
 * Solution 1: Build blocks on operations (When x is not large, seems faster)
 * Solution 2: build blocks on x (Otherwise)
 */

#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#ifndef NDEBUG
#define TRACE printf("At %d (%s) traced.\n", __LINE__, __PRETTY_FUNCTION__)
#define DEBUG(msg, ...) printf(msg, __VA_ARGS__)
#else
#define TRACE
#define DEBUG
#endif  // IFNDEF NDEBUG

#ifndef NDEBUG
#define NMAX 100
#define BLOCKSIZE 2
#else
#define NMAX 50000
#define BLOCKSIZE 300
#endif  // IFNDEF NDEBUG

typedef long long ntype;

inline ntype gcd(ntype a, ntype b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

struct Query {
    int blockid;
    int left, right;
    ntype a, b;

    void minimize() {
        ntype factor = gcd(b, a);
        a /= factor;
        b /= factor;
    }

    void print() {
        minimize();
        printf("%lld/%lld\n", a, b);
    }
};  // struct Query

static bool cmp(const Query *a, const Query *b) {
    return a->blockid < b->blockid ||
           (a->blockid == b->blockid && a->right < b->right);
}

static int n, m;
static ntype hoses[NMAX + 10];
static Query ops[NMAX + 10];
static Query *sorted[NMAX + 10];
static ntype cnt[NMAX + 10];
static ntype current = 0;

static void initialize() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", hoses + i);
    }  // for

    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &ops[i].left, &ops[i].right);
        sorted[i] = ops + i;
    }  // for

    for (int i = 1; i <= n; i++)
        ops[i].blockid = ops[i].left / BLOCKSIZE;
    sort(sorted + 1, sorted + m + 1, cmp);
}

static void expand_right(int from, int to) {
    TRACE;
    assert(from < to);

    for (from++; from <= to; from++) {
        current += 2 * cnt[hoses[from]] + 1;
        cnt[hoses[from]]++;
    }  // for
}

static void expand_left(int from, int to) {
    TRACE;
    assert(from > to);

    for (from--; from >= to; from--) {
        current += 2 * cnt[hoses[from]] + 1;
        cnt[hoses[from]]++;
    }  // for
}

static void shrink_right(int from, int to) {
    TRACE;
    assert(from > to);

    for (; from > to; from--) {
        current -= 2 * cnt[hoses[from]] - 1;
        cnt[hoses[from]]--;
    }  // for
}

static void shrink_left(int from, int to) {
    TRACE;
    assert(from < to);

    for (; from < to; from++) {
        current -= 2 * cnt[hoses[from]] - 1;
        cnt[hoses[from]]--;
    }  // for
}

int main() {
    freopen("hose.in", "r", stdin);
    freopen("hose.out", "w", stdout);
    initialize();

    int last_left = sorted[1]->left;
    int last_right = sorted[1]->left;
    cnt[hoses[last_left]]++;
    current = 1;
    for (int pos = 1; pos <= m; pos++) {
        int left = sorted[pos]->left;
        int right = sorted[pos]->right;
        ntype length = right - left + 1;
        DEBUG("Processing [%d, %d]...\n", left, right);

        if (left == right) {
            sorted[pos]->a = 0;
            sorted[pos]->b = 1;
            continue;
        }

        if (left < last_left)
            expand_left(last_left, left);
        else if (left > last_left)
            shrink_left(last_left, left);

        if (right > last_right)
            expand_right(last_right, right);
        else if (right < last_right)
            shrink_right(last_right, right);

        sorted[pos]->a = current - length;
        sorted[pos]->b = length * (length - 1);
        last_left = left;
        last_right = right;
    }  // for

    for (int i = 1; i <= m; i++) {
        ops[i].print();
    }  // for

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
