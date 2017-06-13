#include <cassert>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 1000000
#define MOD 998244353

typedef long long i64;

#define BUFFERSIZE 65536
static size_t _pos = BUFFERSIZE;
static char _buf[BUFFERSIZE];

inline char _getchar() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFFERSIZE, stdin);
    }

    return _buf[_pos++];
}

template <typename T>
inline void read(T &x) {
    x = 0;
    char c = _getchar();

    while (!isdigit(c))
        c = _getchar();
    while (isdigit(c)) {
        x = x * 10 + (c - '0');
        c = _getchar();
    }
}

static int n;
static i64 ans;
static int perm[NMAX + 10], pos[NMAX + 10];
static i64 ucnt, lcnt, empty;
static i64 unlock[NMAX + 10], lock[NMAX + 10], fac[NMAX + 10];

inline bool okl(int i) {
    return pos[i] > 1 && !perm[pos[i] - 1];
}

inline void add(i64 &dest, i64 src) {
    dest += src % MOD;

    if (dest >= MOD)
        dest -= MOD;
    if (dest < 0)
        dest += MOD;
}

void initialize() {
    // scanf("%d", &n);
    read(n);

    for (int i = 1; i <= n; i++) {
        // scanf("%d", perm + i);
        read(perm[i]);
        pos[perm[i]] = i;
    }

    lcnt = okl(1);
    ucnt = pos[1] == 0;
    fac[0] = fac[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (pos[i]) {
            if (okl(i)) {
                add(lock[1], i - 1);
                lcnt++;
            }
        } else {
            add(unlock[1], i - 1);
            ucnt++;
        }
    }

    i64 loc = 0, unloc = 0;
    for (int i = 1; i < n; i++) {
        empty += !perm[i] && !perm[i + 1];
        loc += okl(i);
        unloc += pos[i] == 0;

        add(lock[i + 1], lock[i] + loc - (lcnt - loc));
        add(unlock[i + 1], unlock[i] + unloc - (ucnt - unloc));
        fac[i + 1] = fac[i] * (i + 1) % MOD;
    }
}

int main() {
#ifdef USE_FILE_IO
    freopen("country.in", "r", stdin);
    freopen("country.out", "w", stdout);
#endif
    initialize();

    for (int i = 1; i <= n; i++) {
        if (pos[i]) {
            if (pos[i] == n)
                continue;
            if (!perm[pos[i] + 1])
                add(ans, unlock[i] * fac[ucnt - 1]);
            else
                add(ans, abs(perm[pos[i] + 1] - i) * fac[ucnt]);
        } else {
            add(ans, unlock[i] * fac[ucnt - 2] % MOD * empty);
            add(ans, lock[i] * fac[ucnt - 1]);
        }
    }

    printf("%lld\n", ans);
    return 0;
}
