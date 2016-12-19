#include <cstdio>
#include <cmath>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 50000
#define EPSILON 0.00000001

template <typename T>
inline bool equiv(const T &a, const T &b) {
    return fabs(a - b) < EPSILON;
}

static int n;
static double A[NMAX + 10];
static double B[NMAX + 10];
static int sorted[NMAX + 10];

inline bool parrallel(const int &a, const int &b) {
    return equiv(A[a], A[b]) && B[b] > B[a];
}

inline bool covered(const int &x, const int &l, const int &r) {
    double delta1 = B[l] - B[x];
    double delta2 = A[r] - A[x];
    double delta3 = B[r] - B[x];
    double delta4 = A[l] - A[x];
    int reverse = (delta2 < 0 ? 1 : 0) + (delta4 < 0 ? 1 : 0);

    if (reverse & 1)
        return delta1 * delta2 >= delta3 * delta4;
    else
        return delta1 * delta2 <= delta3 * delta4;
}

static bool cmp(const int &a, const int &b) {
    return A[a] < A[b] || (equiv(A[a], A[b]) && B[a] < B[b]);
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", A + i, B + i);

        sorted[i] = i;
    }

    sort(sorted + 1, sorted + n + 1, cmp);
}

int main() {
    initialize();
    
    vector<int> stk;
    stk.push_back(sorted[1]);
    for (int i = 2; i <= n; i++) {
        int x = sorted[i];

        while ((!stk.empty() &&
                parrallel(stk[stk.size() - 1], x)) ||
               (stk.size() > 1 &&
                covered(stk[stk.size() - 1], stk[stk.size() - 2], x))
              ) {
            stk.pop_back();
        }

        stk.push_back(x);
    }

    sort(stk.begin(), stk.end());
    for (size_t i = 0; i < stk.size(); i++) {
        printf("%d ", stk[i]);
    }

    return 0;
}
