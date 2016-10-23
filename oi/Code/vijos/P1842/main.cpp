#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define NMAX 100000
// #define NMAX 100
#define MOD 99999997

static int n;
// static int realn;
static int seq1[NMAX + 10];
static int tmp1[NMAX + 10];
static int seq2[NMAX + 10];
// static int tmp2[NMAX + 10];
static int tmp3[NMAX + 10];
static int map[NMAX + 10];
static int fenwick[NMAX + 10];

inline void modify(int x) {
    for (; x <= n; x += x & (-x)) {
        fenwick[x]++;
    }
}

inline int query(int r) {
    int answer = 0;

    for (; r; r -= r & (-r)) {
        answer += fenwick[r];
    }

    return answer;
}

static bool cmp1(const int a, const int b) {
    return seq1[a] < seq1[b];
}

static bool cmp2(const int a, const int b) {
    return seq2[a] < seq2[b];
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", seq1 + i);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", seq2 + i);
    }

    for (int i = 1; i <= n; i++) {
        tmp1[i] = i;
        tmp3[i] = i;
    }
    // memcpy(tmp2, seq2, sizeof(seq2));

    sort(tmp1 + 1, tmp1 + n + 1, cmp1);
    sort(tmp3 + 1, tmp3 + n + 1, cmp2);
    // sort(tmp2 + 1, tmp2 + n + 1);
    // realn = unique(tmp2 + 1, tmp2 + n + 1) - tmp2 - 1;

    for (int i = 1; i <= n; i++) {
        map[tmp3[i]] = tmp1[i];
    }  // for

    for (int i = 1; i <= n; i++) {
        // int id = lower_bound(tmp2 + 1, tmp2 + realn + 1, seq2[i]) - tmp2;
        seq1[map[i]] = i;
    }
}

int main() {
    initialize();

    int answer = 0;
    for (int i = n; i >= 1; i--) {
        answer += query(seq1[i] - 1);
        answer %= MOD;

        modify(seq1[i]);
    }

    printf("%d\n", answer);

    return 0;
}
