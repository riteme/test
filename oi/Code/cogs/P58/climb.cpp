#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 1000000

static int n, q;
static int h[NMAX + 10];

static void initialize() {
    scanf("%d", &n);
    for (int i = 0; i <= n; i++) {
        scanf("%d", h + i);
    }  // for
}

#define LOGN (20)
static int st[NMAX + 10][LOGN + 1];

static void initialize_st() {
    for (int i = 0; i <= n; i++)
        st[i][0] = h[i];

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 0; i <= n; i++) {
            int next = i + (1 << (j - 1));
            if (next <= n)
                st[i][j] = max(st[i][j - 1], st[next][j - 1]);
        }  // for
    }      // for
}

inline int high(int x) {
    int pos = 0;
    while (x >> (pos + 1) > 0)
        pos++;
    return pos;
}

static int query(int left, int right) {
    int k = high(right - left + 1);
    return max(st[left][k], st[right - (1 << k) + 1][k]);
}

int main() {
    freopen("climb.in", "r", stdin);
    freopen("climb.out", "w", stdout);
    initialize();
    initialize_st();

    scanf("%d", &q);
    while (q > 0) {
        int a, b;
        scanf("%d%d", &a, &b);

        printf("%d\n", query(a, b));

        q--;
    }  // while

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
