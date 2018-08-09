#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 10000

inline bool cmp(int e, int o) {
    printf("? %d %d\n", e, o);
    fflush(stdout);
    char c;
    do {
        c = getchar();
    } while (c != '<' && c != '>');
    return c == '<' ? true : false;
}

static int n, ec, oc, K;
static int E[NMAX + 10], O[NMAX + 10];
static int seq[NMAX + 10], pre[NMAX + 10];

int main() {
    scanf("%d", &n);
    ec = n / 2;
    oc = n - ec;

    K = 1;
    pre[1] = 1;
    pre[2] = oc + 1;
    for (int i = 1; i <= oc; i++)
        seq[i] = i;

    for (int i = 1; i <= ec; i++) {
        int l = 1, r = K;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (cmp(i, seq[pre[m]])) r = m;
            else l = m;
        }

        int j = pre[l];
        for (int k = pre[l]; k < pre[r + 1]; k++) {
            if (!cmp(i, seq[k])) swap(seq[j++], seq[k]);
        }

        K++;
        if (j >= pre[r]) {
            memmove(pre + r + 2, pre + r + 1, sizeof(int) * (K - r));
            pre[r + 1] = j;
        } else {
            memmove(pre + l + 2, pre + l + 1, sizeof(int) * (K - l));
            pre[l + 1] = j;
        }

        E[i] = 2 * (j - 1);
    }

    for (int i = 1; i <= oc; i++) {
        O[seq[i]] = 2 * i - 1;
    }

    putchar('!');
    for (int i = 1; i <= ec; i++)
        printf(" %d", E[i]);
    for (int i = 1; i <= oc; i++)
        printf(" %d", O[i]);

    return 0;
}
