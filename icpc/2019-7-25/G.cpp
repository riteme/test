#pragma GCC optimize(3)
#include <cstdio>
#include <cstring>
#include <cctype>

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

#define NMAX 300000
#define INF 0x3f3f3f3f

typedef long long i64;

static int n;
static int a[NMAX + 10], l[NMAX + 10], r[NMAX + 10];
static int stk[NMAX + 10], p;
static i64 pre[NMAX + 10], ans;

inline void calcl(int k) {
    int m = 2 * a[k], j = k;
    for (int i = l[k] - 1; i < k; i++) {
        if (pre[j] < pre[i] + m) {
            int s = 1;
            while (j + s <= r[k] && pre[j + s] < pre[i] + m) s <<= 1;
            j += (s >>= 1);
            for (; s; s >>= 1) if (j + s <= r[k] && pre[j + s] < pre[i] + m) j += s;
            if (j == r[k]) return;
            j++;
        }
        ans += r[k] - j + 1;
    }
}

inline void calcr(int k) {
    int m = 2 * a[k], j = l[k] - 1;
    for (int i = k; i <= r[k]; i++) {
        if (pre[i] >= pre[j] + m) {
            int s = 1;
            while (j + s < k && pre[i] >= pre[j + s] + m) s <<= 1;
            j += (s >>= 1);
            for (; s; s >>= 1) if (j + s < k && pre[i] >= pre[j + s] + m) j += s;
            j++;
            if (j == k) {
                ans += i64(k - l[k] + 1) * (r[k] - i + 1);
                return;
            }
        }
        ans += j - l[k] + 1;
    }
}

int main() {
    int T;
    //scanf("%d", &T);
    read(T);
    a[0] = INF;
    while (T--) {
        //scanf("%d", &n);
        read(n);
        p = 1;
        for (int i = 1; i <= n; i++) {
            //scanf("%d", a + i);
            read(a[i]);
            pre[i] = pre[i - 1] + a[i];
            while (a[i] >= a[stk[p - 1]]) r[stk[--p]] = i - 1;
            l[i] = stk[p - 1] + 1;
            stk[p++] = i;
        }
        while (p > 1) r[stk[--p]] = n;
        ans = 0;
        for (int i = 1; i <= n; i++)
            if ((i << 1) < l[i] + r[i]) calcl(i);
            else calcr(i);
        printf("%lld\n", ans);
    }
    return 0;
}
