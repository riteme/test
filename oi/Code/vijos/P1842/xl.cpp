#include <cstdio>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define MOD 99999997

static int n;
static int seq1[NMAX + 10];
static int sorted1[NMAX + 10];
static int seq2[NMAX + 10];
static int sorted2[NMAX + 10];
static int pos[NMAX + 10];

static bool cmp1(const int a, const int b) {
    return seq1[a] < seq1[b];
}

static bool cmp2(const int a, const int b) {
    return seq2[a] < seq2[b];
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%d", seq1 + i);
    for (int i = 1; i <= n; i++)
        scanf("%d", seq2 + i);
    for (int i = 1; i <= n; i++)
        sorted1[i] = sorted2[i] = i;

    sort(sorted1 + 1, sorted1 + n + 1, cmp1);
    sort(sorted2 + 1, sorted2 + n + 1, cmp2);
    for (int i = 1; i <= n; i++) {
        seq1[sorted1[i]] = seq2[sorted2[i]] = i;
        pos[i] = sorted2[i];
    }

    for (int i = 1; i <= n; i++)
        seq2[pos[seq1[i]]] = i;
}

static int fenwick[NMAX + 10];

inline int query(int r) {
    int result = 0;

    for (; r; r -= r & (-r))
        result += fenwick[r];

    return result;
}

inline void modify(int x, int v) {
    for (; x <= n; x += x & (-x))
        fenwick[x] += v;
}

int main() {
    initialize();

    int answer = 0;
    for (int i = n; i >= 1; i--) {
        answer += query(seq2[i] - 1);
        answer %= MOD;
        modify(seq2[i], 1);
    }

    printf("%d\n", answer);

    return 0;
}
