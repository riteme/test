// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <random>
#include <algorithm>

using namespace std;

#define NMAX 1000000

static int n, m;
static int P[2 * NMAX + 10];
static int S[NMAX + 10];
static bool marked[2 * NMAX + 10];

#define PROCEDURE if (n & 1) { \
        for (int i = 1; i <= n - 1; i++) { \
            check(i, m - i); \
        } \
        check(0, 2 * n); \
        check(0, 1); \
        check(n, 2); \
        check(n, 2 * n - 1); \
        check(4, n + 1); \
        check(2 * n - 3, n + 1); \
    } else { \
        for (int i = 1; i <= n - 1; i++) { \
            check(m - i, i); \
        } \
        check(0, 2 * n); \
        check(0, 1); \
        check(n, 2); \
        check(n, 2 * n - 1); \
        check(4, n + 1); \
        check(2 * n - 3, n + 1); \
    }

void encode(int *A, int &a, int &b) {
    int s = 0;
    for (int i = 1; i <= n; i++) {
        s = (s + A[i]) % m;
    }

    bool flag = false;
    auto check = [&](int u, int v) {
        if (flag)
            return;

        a = (u + s) % m;
        b = (v + s) % m;

        if (marked[a] && marked[b])
            flag = true;
    };

    PROCEDURE
}

inline int automod(int a, int b) {
    int s = a % b;
    return s < 0 ? s + b : s;
}

int decode(int a, int b) {
    int s;
    int d = automod(b - a, m);

    auto check = [&](int u, int v) {
        int d1 = automod(v - u, m);

        if (d1 == d)
            s = automod(a - u, m);
    };

    PROCEDURE

    return s;
}

int mogician(int a, int b, int c, int d) {
    int s1 = decode(a, b);
    int s2 = decode(c, d);
    return automod(0 - s1 - s2, m);
}

static int a, b, c, d;
static int ans;

bool test() {
    random_device rd;
    shuffle(P, P + m, rd);
    int answer = P[0];

    memcpy(S + 1, P + 1, sizeof(int) * n);
    for (int i = 1; i <= n; i++) {
        marked[S[i]] = true;
    }

    encode(S, a, b);
    if (!marked[a] || !marked[b])
        return false;
    for (int i = 1; i <= n; i++) {
        marked[S[i]] = false;
    }

    memcpy(S + 1, P + n + 1, sizeof(int) * n);
    for (int i = 1; i <= n; i++) {
        marked[S[i]] = true;
    }

    encode(S, c, d);
    if (!marked[c] || !marked[d])
        return false;
    for (int i = 1; i <= n; i++) {
        marked[S[i]] = false;
    }

    ans = mogician(a, b, c, d);

    return ans == answer;
}

int main() {
    srand(time(0));
    scanf("%d", &n);
    m = 2 * n + 1;
    for (int i = 0; i <= 2 * n; i++) {
        P[i] = i;

    }

    int cnt = 1;
    while (true) {
        printf("%d\n", cnt);

        if (!test()) {
            printf("Hacked!\n");
            printf("S1 = {");
            for (int i = 1; i <= n; i++) {
                if (i < n)
                    printf("%d, ", P[i]);
                else
                    printf("%d}\n", P[i]);
            }

            printf("S2 = {");
            for (int i = n + 1; i <= 2 * n; i++) {
                if (i < 2 * n)
                    printf("%d, ", P[i]);
                else
                    printf("%d}\n", P[i]);
            }
            printf("answer = %d\n", P[0]);
            printf("a = %d, b = %d, c = %d, d = %d\n", a, b, c, d);
            printf("mogic = %d\n", ans);
            break;
        }

        cnt++;
    }

    return 0;
}
