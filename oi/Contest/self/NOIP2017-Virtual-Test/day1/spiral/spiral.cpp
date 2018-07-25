#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 1000000

static int n;
static int perm[NMAX + 10];
static int pos[NMAX + 10];
static bool arr[NMAX + 10];
static bool dir[NMAX + 10];

inline void modify(int x) {
    for (; x; x -= x & -x) {
        arr[x] ^= 1;
    }
}

inline bool query(int x) {
    bool ret = 0;
    for (; x <= n; x += x & -x) {
        ret ^= arr[x];
    }

    return ret;
}

int main() {
#ifdef USE_FILE_IO
    freopen("spiral.in", "r", stdin);
    freopen("spiral.out", "w", stdout);
#endif
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", perm + i);
        pos[perm[i]] = i;
    }

    if (perm[1] == 2 && perm[2] == 1 &&
        is_sorted(perm + 3, perm + n + 1))
        swap(perm[1], perm[2]);
    else {
        modify(pos[1]);

        bool s = false;
        for (int i = 2; i <= n; i++) {
            dir[pos[i]] = s;
            s ^= query(pos[i]);
            modify(pos[i]);
        }

        int p = 0;
        for (int i = 1; i <= n; i++) {
            if ((dir[i] && i < n && perm[i] > perm[i + 1]) ||
                (!dir[i] && i > 1 && perm[i] > perm[i - 1]))
            if (perm[i] > perm[p])
                p = i;
        }

        if (dir[p])
            swap(perm[p], perm[p + 1]);
        else
            swap(perm[p], perm[p - 1]);
    }

    for (int i = 1; i <= n; i++) {
        printf("%d ", perm[i]);
    }
    putchar('\n');

    return 0;
}
