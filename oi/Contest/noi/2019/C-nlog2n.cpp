#include <cstdio>
#include <cstring>

#include <map>
#include <algorithm>

using namespace std;

#define NMAX 200000

typedef long long i64;


static int n, K, L;
static int A[NMAX + 10], B[NMAX + 10], Ai[NMAX + 10], Bi[NMAX + 10];
static int seq[NMAX + 10], rev[NMAX * 2 + 10];
static map<int, int> id;

static struct BIT {
    int cnt[NMAX * 2 + 10], s;
    i64 sum[NMAX * 2 + 10];

    void clear() {
        memset(cnt + 1, 0, sizeof(int) * 2 * n);
        memset(sum + 1, 0, sizeof(i64) * 2 * n);
        int i = 2 * n;
        while (i) {
            s = i & -i;
            i -= s;
        }
    }

    void modify(int i, i64 v) {
        for (int x = i; x <= 2 * n; x += x & -x) {
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
        for (; i; i >>= 1) if (i + j <= 2 * n && cnt[i + j] + cnt[j] < k)
            j += i, k -= cnt[j];
        return j + 1;
    }
} pa, pb, sa, sb;

inline void reindex(int *a) {
    memcpy(Ai + 1, a + 1, sizeof(int) * n);
    for (int i = 1; i <= n; i++) a[i] = Ai[seq[i]];
}

inline void initialize() {
    scanf("%d%d%d", &n, &K, &L);
    id.clear();
    for (int i = 1; i <= n; i++) {
        scanf("%d", A + i);
        id[A[i]] = 0;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", B + i);
        id[B[i]] = 0;
        seq[i] = i;
    }
    int now = 1;
    for (auto &e : id) {
        rev[now] = e.first;
        e.second = now++;
    }
    sort(seq + 1, seq + n + 1, [](int x, int y) {
        return A[x] + B[x] > A[y] + B[y];
    });
    reindex(A); reindex(B);
    for (int i = 1; i <= n; i++) {
        Ai[i] = id[A[i]];
        Bi[i] = id[B[i]];
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
    scanf("%d", &T);
    while (T--) {
        initialize();
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
            if (x < L) continue;
            int l = max(0, x - K), r = min(x - L, K - L);
            while (l < r) {
                int y = (l + r) >> 1;
                int da = sa.kth(n - x - y) - pa.kth(y + 1);
                int db = sb.kth(n - 2*x + L + y + 1) - pb.kth(x - L - y);
                if (da <= db) r = y;
                else l = y + 1;
            }
            int i1 = pa.kth(l), i2 = sa.kth(n - x - l);
            int i3 = pb.kth(x - L - l), i4 = sb.kth(n - 2*x + L + l);
            ans = max(ans,
                sum - pa.query(i1) - sa.query(i2) - pb.query(i3) - sb.query(i4));
        }
        printf("%lld\n", ans);
    }

    return 0;
}
