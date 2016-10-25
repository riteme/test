#include <cstdio>
#include <cstring>

#define BUFFERSIZE 65536
static size_t _pos = BUFFERSIZE;
static char _buffer[BUFFERSIZE];

inline char _getchar() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buffer, 1, BUFFERSIZE, stdin);
    }

    return _buffer[_pos++];
}

template <typename T>
inline T read() {
    T x = 0;
    char c = _getchar();

    while (c < '0' || c > '9')
        c = _getchar();
    while ('0' <= c && c <= '9') {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x;
}

#define NMAX 1000000

typedef long long int64;

static int n, m;
static int64 limit[NMAX + 10];
static int64 cnt[NMAX + 10];
static int left[NMAX + 10];
static int right[NMAX + 10];
static int64 require[NMAX + 10];

static void initialize() {
    // scanf("%d%d", &n, &m);
    n = read<int>();
    m = read<int>();

    for (int i = 1; i <= n; i++) {
        // scanf("%lld", limit + i);
        limit[i] = read<int64>();
    }

    for (int i = 1; i <= m; i++) {
        // scanf("%lld%d%d", require + i, left + i, right + i);
        require[i] = read<int64>();
        left[i] = read<int>();
        right[i] = read<int>();
    }
}

static bool test(int x) {
    memset(cnt, 0, sizeof(cnt));

    for (int i = 1; i <= x; i++) {
        cnt[left[i]] += require[i];
        cnt[right[i] + 1] -= require[i];
    }

    for (int i = 1; i <= n; i++) {
        cnt[i] += cnt[i - 1];

        if (cnt[i] > limit[i])
            return false;
    }

    return true;
}

int main() {
    initialize();

    int l = 1, r = m + 1;
    while (l + 1 < r) {
        int mid = (l + r) / 2;

        if (test(mid))
            l = mid;
        else
            r = mid;
    }

    if (l != r && test(l))
        l = r;

    if (l > m)
        puts("0");
    else
        printf("-1\n%d\n", l);

    return 0;
}
