// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <ctime>

#include <unordered_set>
#include <algorithm>

using namespace std;

#define NMAX 1000000
#define LIMIT 60

static int n, MOD, on;
static int origin[NMAX + 10];
static int seq[NMAX + 10];

void initialize() {
    auto seed = time(0);
    fprintf(stderr, "seed = %ld\n", seed);
    srand(seed);
    scanf("%d%d", &MOD, &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", seq + i);
        origin[i] = seq[i];
    }

    on = n;
}

inline int sub(int a, int b) {
    int ret = a - b;
    return ret < 0 ? ret + MOD : ret;
}

inline void add(int &a, int b) {
    a += b;

    if (a >= MOD)
        a -= MOD;
}

static unordered_set<int> set;

bool solve1(int &s, int &d) {
    // for (int i = 1; i <= n; i++) {
    //     printf("%d ", seq[i]);
    // }
    // printf("\n");

    for (int i = 1; i <= n; i++) {
        s = seq[i];
        for (int j = 1; j <= n; j++) {
            if (i == j)
                continue;

            d = sub(seq[j], seq[i]);
            // printf("%d %d %d\n", seq[i], seq[j], d);

            int u = seq[i];
            set.clear();
            set.insert(u);
            for (int k = 2; k <= n; k++) {
                add(u, d);
                set.insert(u);
            }

            bool flag = true;
            for (int k = 1; flag && k <= n; k++) {
                if (!set.count(seq[k]))
                    flag = false;
            }

            if (flag)
                return true;
        }
    }

    return false;
}

static int cnt;
static int tmp[NMAX + 10];

bool solve2(int &s, int &d) {
    while (n > 10) {
        if (cnt > LIMIT)
            return false;
        cnt++;

        int w = 2 * seq[rand() % n + 1] % MOD;
        set.clear();
        memcpy(tmp, seq, sizeof(int) * (n + 10));

        for (int i = 1; i <= n; i++) {
            set.insert(seq[i]);
        }

        for (int i = 1; i <= n; i++) {
            if (set.count((w - seq[i] + MOD) % MOD))
                seq[i] = -1;
        }

        int j = 0;
        for (int i = 1; i <= n; i++) {
            if (seq[i] >= 0)
                seq[++j] = seq[i];
        }

        // printf("j = %d\n", j);

        if (j <= 1) {
            memcpy(seq, tmp, sizeof(int) * (n + 10));
            continue;
        }

        n = j;
    }

    return solve1(s, d);
}

int main() {
#ifdef USE_FILE_IO
    freopen("mountain.in", "r", stdin);
    freopen("mountain.out", "w", stdout);
#endif
    initialize();
    
    if (n == 1) {
        printf("%d 0\n", seq[1]);
        return 0;
    }

    int s, d;
    if (!solve2(s, d)) {
        puts("-1");
        return 0;
    }

    n = on;
    s = origin[1];
    int c = 0;
    for (int i = 1; i <= n; i++) {
        if (!binary_search(
                origin + 1, origin + n + 1, (origin[i] + d) % MOD
            )) {
            c++;
            s = origin[i];
        }
    }

    if (c <= 1)
        printf("%d %d", s, MOD - d);
    else
        puts("-1");

    return 0;
}
