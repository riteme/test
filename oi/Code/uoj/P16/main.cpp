#include <cstdio>
#include <cstring>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

#define NMAX 200000
#define MOD 10007

#define FMT "%lld"
typedef unsigned long long ntype;

// #define FMT "%d"
// typedef int ntype;

typedef vector<ntype>::iterator iterator_t;

static ntype n;
static ntype result = 0;
static ntype m = 0;
static ntype W[NMAX + 10];
static vector<ntype> G[NMAX + 10];

inline ntype read_int() {
    ntype v = 0;
    char c = getchar();
    while (c < '0' or c > '9') c = getchar();
    while ('0' <= c and c <= '9') {
        v = v * 10 + c - '0';
        c = getchar();
    }
    return v;
}

inline void read_edge() {
    ntype u, v;
    scanf(FMT FMT, &u, &v);
    // u = read_int();
    // v = read_int();

    G[u].push_back(v);
    G[v].push_back(u);
}

inline void read_weight(unsigned i) {
    scanf(FMT, &W[i]);
    // W[i] = read_int();
}

void compute_max();
void compute_sum();

int main() {
    scanf(FMT, &n);
    // n = read_int();

    for (ntype i = 0; i < n - 1; i++) read_edge();
    for (ntype i = 1; i <= n; i++) read_weight(i);

    compute_max();
    compute_sum();

    printf(FMT " " FMT, m, result);

    return 0;
}  // function main

void compute_max() {
    auto cmp = [](const ntype a, const ntype b) { return W[a] < W[b]; };

    for (auto &V : G) {
        if (V.size() < 2) continue;

        auto iter = std::max_element(V.begin(), V.end(), cmp);
        auto left = std::max_element(V.begin(), iter, cmp);
        auto right = std::max_element(std::next(iter), V.end(), cmp);

        ntype maxv;
        if (left == iter) {
            maxv = W[*right];
            // printf(FMT " and right " FMT "\n", *iter, *right);
        } else if (right == V.end()) {
            maxv = W[*left];
            // printf(FMT " and left " FMT "\n", *iter, *left);
        } else {
            maxv = std::max(W[*left], W[*right]);
            // printf(FMT " and " FMT " and " FMT "\n", *iter, *left, *right);
        }

        // printf(FMT " & " FMT "\n", W[*iter], maxv);

        ntype value = W[*iter] * maxv;
        if (m < value) m = value;
    }  // foreach in G
}

void compute_sum() {
    for (int i = 1; i <= n; i++) {
        ntype sum = 0;

        for (auto j : G[i]) sum += W[j];

        for (auto j : G[i]) {
            result += W[j] * (sum - W[j]);
            result %= MOD;
        }  // foreach in G[i]
    }      // for
}
