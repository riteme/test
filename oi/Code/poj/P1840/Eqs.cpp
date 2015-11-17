#include <cstring>
#include <climits>
#include <cstdio>
#include <cmath>
#include <list>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#define MOD 100007

struct Result {
    Result() : value(0), count(0) {}
    Result(int _v, int _c) : value(_v), count(_c) {}

    int value;
    int count;

    bool operator==(const int lhs) const { return value == lhs; }
};  // struct Result

typedef unsigned hash_t;

// typedef list<Result>::iterator iterator_t;
// static list<Result> hb[MOD];

typedef vector<Result>::iterator iterator_t;
static vector<Result> hb[MOD];

static int a1, a2, a3, a4, a5;

inline hash_t h(int v) {
    // return (v >= 0 ? v : -v) % MOD;
    int n = v >= 0 ? v : -v;
    return (n % MOD + n / MOD) % MOD;
}

inline int compute(int x1, int x2, int x3) {
    return a1 * x1 * x1 * x1 + a2 * x2 * x2 * x2 + a3 * x3 * x3 * x3;
}

inline int compute(int x4, int x5) {
    return -(a4 * x4 * x4 * x4 + a5 * x5 * x5 * x5);
}

/*inline*/ void increase(int v) {
    hash_t hx = h(v);
    iterator_t iter = std::find(hb[hx].begin(), hb[hx].end(), v);

    if (iter == hb[hx].end())
        hb[hx].push_back(Result(v, 1));
    else
        iter->count++;
}

/*inline*/ int count(int v) {
    hash_t hx = h(v);
    int cnt = 0;

    for (iterator_t beg = hb[hx].begin(); beg != hb[hx].end(); beg++) {
        if (v == beg->value) cnt += beg->count;
    }  // for

    return cnt;
}

int main(/*int argc, char *argv[]*/) {
    scanf("%d %d %d %d %d", &a1, &a2, &a3, &a4, &a5);

    for (int x1 = -50; x1 <= 50; x1++)
        if (x1 != 0)
            for (int x2 = -50; x2 <= 50; x2++)
                if (x2 != 0)
                    for (int x3 = -50; x3 <= 50; x3++)
                        if (x3 != 0) increase(compute(x1, x2, x3));

    int cnt = 0;
    for (int x1 = -50; x1 <= 50; x1++)
        if (x1 != 0)
            for (int x2 = -50; x2 <= 50; x2++)
                if (x2 != 0) cnt += count(compute(x1, x2));

    printf("%d", cnt);

    return 0;
}  // function main
