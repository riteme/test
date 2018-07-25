#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 2000
#define LOGN 11

static int n;
static int seq[NMAX + 10];
static int left[NMAX + 10];
static int right[NMAX + 10];
static int bepos;
static int before[NMAX + 10];
static int table[NMAX * 2 + 10];
static int afpos;
static int after[NMAX + 10];
static int st[NMAX + 10][LOGN + 1];

static int _high[NMAX + 10];

inline int highbit(int x) {
    if (_high[x] >= 0)
        return _high[x];

    int k = LOGN;
    while (!(x & (1 << k))) {
        k--;
    }

    _high[x] = k;
    return k;
}

static void initialize_st() {
    for (int i = 1; i <= n; i++)
        st[i][0] = right[i] - left[i] + 1;

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= n; i++) {
            if (i + (1 << (j - 1)) <= n)
                st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            else
                st[i][j] = st[i][j - 1];
        }
    }
}

inline int querymax(int l, int r) {
    if (l == r)
        return st[l][0];

    int k = highbit(r - l + 1);
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}

bool cmp(const int a, const int b) {
    return seq[a] < seq[b] || (seq[a] == seq[b] && a < b);
}

static void initialize() {
    scanf("%d", &n);
    for (int i = 0; i <= n; i++)
        _high[i] = -1;

    for (int i = 1; i <= n; i++)
        scanf("%d", seq + i);

    for (int i = 1; i <= n; i++) {
        left[i] = right[i] = i;

        bepos = afpos = 0;
        memset(table, 0, sizeof(table));

        for (int j = i - 1; j >= 1; j--) {
            if (cmp(j, i))
                before[++bepos] = 1;
            else
                before[++bepos] = -1;
        }

        for (int j = i + 1; j <= n; j++) {
            if (cmp(j, i))
                after[++afpos] = -1;
            else
                after[++afpos] = 1;
        }

        for (int j = 0; j <= bepos; j++) {
            if (j > 0)
                before[j] += before[j - 1];
            table[before[j] + n] = i - j;
        }

        for (int j = 0; j <= afpos; j++) {
            if (j > 0)
                after[j] += after[j - 1];

            if (table[after[j] + n]) {
                int l = table[after[j] + n];

                if (i + j - l > right[i] - left[i]) {
                    left[i] = l;
                    right[i] = i + j;
                }
            }
        }
    }

    initialize_st();
}

int main() {
    freopen("beautiful.in", "r", stdin);
    freopen("beautiful.out", "w", stdout);
    initialize();

    int q;
    scanf("%d", &q);

    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);

        printf("%d\n", querymax(l, r));
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}
