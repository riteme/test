/**
 * Vijos P1459 车展
 * tags: 二叉堆 中位数
 * time: O(n^2*logn) + O(n*m)
 * 使用二叉堆预处理中位数
 */

#pragma GCC optimize(2)

#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 1000
#define MMAX 200000

#define FMT "%lld"
typedef long long ntype;

namespace std {
template <>
struct less<ntype> {
    bool operator()(const ntype &a, const ntype &b) const {
        return a < b;
    }
};  // struct less<ntype>

template <>
struct greater<ntype> {
    bool operator()(const ntype &a, const ntype &b) const {
        return a > b;
    }
};  // struct greater<ntype>
}  // namespace std

template <typename T>
T abs(const T &value) {
    return value < 0 ? -value : value;
}

static ntype n, m;
static ntype h[NMAX + 10];
static ntype s[NMAX + 10];
static ntype p[NMAX + 10][NMAX + 10];
static ntype left[NMAX + 10][NMAX + 10];

typedef less<ntype> less_cmp;
typedef greater<ntype> greater_cmp;
static priority_queue<ntype, vector<ntype>, greater_cmp> q1;
static priority_queue<ntype, vector<ntype>, less_cmp> q2;

void initialize();
void compute_p();

int main() {
    initialize();
    compute_p();

    ntype l, r;
    ntype answer = 0;
    for (int i = 0; i < m; i++) {
        scanf(FMT FMT, &l, &r);

        ntype pivot = p[l][r];

        ntype result = 0;
        for (int j = l; j <= r; j++) {
            result += abs(h[j] - pivot);
        }  // for

        answer += result;
    }  // for

    for (int i = 0; i < 1000000000; i++)
        ;

    printf(FMT, answer);

    return 0;
}  // function main

void initialize() {
    scanf(FMT FMT, &n, &m);

    s[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf(FMT, h + i);
        s[i] = h[i] + s[i - 1];
    }
}

void compute_p() {
    for (int i = 1; i <= n; i++) {
        q1 = priority_queue<ntype, vector<ntype>, greater_cmp>();
        q2 = priority_queue<ntype, vector<ntype>, less_cmp>();

        p[i][i] = h[i];
        left[i][i] = 0;
        q2.push(h[i]);
        for (int j = i + 1; j <= n; j++) {
            q1.push(h[j]);

            while (q1.size() > q2.size()) {
                q2.push(q1.top());
                q1.pop();
            }  // while

            while (q1.top() < q2.top()) {
                ntype e1 = q1.top();
                ntype e2 = q2.top();

                q1.pop();
                q1.push(e2);
                q2.pop();
                q2.push(e1);
            }  // while

            p[i][j] = q2.top();
            left[i][j] = q2.size() - 1;
        }  // for
    }      // for
}
