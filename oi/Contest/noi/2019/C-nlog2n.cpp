// 76 on LOJ, O(n log^2 n)
#define NDEBUG

#include <cstdio>
#include <cstring>
#include <cctype>

#include <map>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
static size_t _pos = BUFFERSIZE;
static char _buf[BUFFERSIZE];

inline void _getc(char &c) {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFFERSIZE, stdin);
    }
    c = _buf[_pos++];
}

inline void read(int &x) {
    x = 0;
    char c;
    do _getc(c); while (!isdigit(c));
    do {
        x = x * 10 + (c - '0');
        _getc(c);
    } while (isdigit(c));
}

#define NMAX 200000
#define BITSIZE 600000

typedef long long i64;

static int n, K, L;
static int A[NMAX + 10], B[NMAX + 10], Ai[NMAX + 10], Bi[NMAX + 10];
static int seq[NMAX + 10], rev[NMAX * 2 + 10];
static map<int, int> id;

static struct BIT {
    int cnt[BITSIZE + 10], s;
    i64 sum[BITSIZE + 10];

    void clear() {
        s = 1;
        while (s < 2 * n) s <<= 1;
        memset(cnt + 1, 0, sizeof(int) * s);
        memset(sum + 1, 0, sizeof(i64) * s);
    }

    void modify(int i, i64 v) {
        for (int x = i; x <= s; x += x & -x) {
            cnt[x] += v > 0 ? 1 : -1;
            sum[x] += v;
        }
    }

    i64 query(int i) {
        i64 r = 0;
        for (int x = i; x; x -= x & -x) r += sum[x];
        return r;
    }

    int kth(int k) {
        if (k <= 0) return 0;
        int i = s, j = 0;
        for (; i; i >>= 1)
            if (i + j <= s && cnt[i + j] < k)
                j += i, k -= cnt[j];
        return j + 1;
    }
} pa, pb, sa, sb;

inline void reindex(int *a) {
    memcpy(Ai + 1, a + 1, sizeof(int) * n);
    for (int i = 1; i <= n; i++) a[i] = Ai[seq[i]];
}

inline void initialize() {
    //scanf("%d%d%d", &n, &K, &L);
    read(n); read(K); read(L);
    id.clear();
    for (int i = 1; i <= n; i++) {
        //scanf("%d", A + i);
        read(A[i]);
        id[A[i]]++;
    }
    for (int i = 1; i <= n; i++) {
        //scanf("%d", B + i);
        read(B[i]);
        id[B[i]]++;
        seq[i] = i;
    }
    int now = 1;
    for (auto &e : id) {
        rev[now] = e.first;
        int t = e.second;
        e.second = now;
        now += t;
    }
    sort(seq + 1, seq + n + 1, [](int x, int y) {
        return A[x] + B[x] > A[y] + B[y];
    });
    reindex(A); reindex(B);
    for (int i = 1; i <= n; i++) {
        Ai[i] = id[A[i]]++;
        rev[Ai[i]] = A[i];
        Bi[i] = id[B[i]]++;
        rev[Bi[i]] = B[i];
    }
    pa.clear(); pb.clear();
    sa.clear(); sb.clear();
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
#endif
    int T;
    //scanf("%d", &T);
    read(T);
    while (T--) {
        initialize();
#ifndef NDEBUG
        fprintf(stderr, "A:  [");
        for (int i = 1; i <= n; i++) fprintf(stderr, (i < n ? "%2d, " : "%2d"), A[i]);
        fprintf(stderr, "]\nB:  [");
        for (int i = 1; i <= n; i++) fprintf(stderr, (i < n ? "%2d, " : "%2d"), B[i]);
        fprintf(stderr, "]\n");
        fprintf(stderr, "Ai: [");
        for (int i = 1; i <= n; i++) fprintf(stderr, (i < n ? "%2d, " : "%2d"), Ai[i]);
        fprintf(stderr, "]\nBi: [");
        for (int i = 1; i <= n; i++) fprintf(stderr, (i < n ? "%2d, " : "%2d"), Bi[i]);
        fprintf(stderr, "]\n");
#endif
        i64 ans = 0, sum = 0;
        for (int i = 1; i <= n; i++) {
            sa.modify(Ai[i], A[i]);
            sb.modify(Bi[i], B[i]);
            sum += A[i] + B[i];
        }
        for (int x = 1; x <= min(n, 2 * K - L); x++) {
            sa.modify(Ai[x], -A[x]);
            sb.modify(Bi[x], -B[x]);
            pa.modify(Ai[x], A[x]);
            pb.modify(Bi[x], B[x]);
            if (x > K) {
                int i = pa.kth(1), j = pb.kth(1);
                pa.modify(i, -rev[i]);
                pb.modify(j, -rev[j]);
                sum -= rev[i] + rev[j];
            }
            int l = max(0, max(x - K, K - L - n + x)), c = min(x, K), r = min(c - L, n - K);
            if (x < L || l > r) continue;
            //fprintf(stderr, "l = %d, r = %d\n", l, r);
            while (l < r) {
                int y = (l + r) >> 1;
                int da = rev[sa.kth(n - y - K)] - rev[pa.kth(y - x + c + 1)];  // rev!. when c < K, K - c suf max selected
                int db = rev[sb.kth(n - x - K + L + y + 1)] - rev[pb.kth(c - L - y)];
                if (da <= db) r = y;
                else l = y + 1;
            }
            int i1 = pa.kth(l - x + c), i2 = sa.kth(n - K - l);
            int i3 = pb.kth(c - L - l), i4 = sb.kth(n - x - K + L + l);
            i64 ret = sum - pa.query(i1) - sa.query(i2) - pb.query(i3) - sb.query(i4);
            if (ret > ans) ans = ret;
#ifndef NDEBUG
            fprintf(stderr, "[%lld] x = %d, y = %d\n", ret, x, l);
            fprintf(stderr, "i1 = %d, i2 = %d, i3 = %d, i4 = %d\n", i1, i2, i3, i4);
#endif
        }
        printf("%lld\n", ans);
    }

    return 0;
}
