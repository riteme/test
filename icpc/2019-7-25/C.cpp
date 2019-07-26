//#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cctype>

#include <queue>
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

#define NMAX 250000
#define MMAX 500000

static int n, m, a[MMAX + 10];
static int L[NMAX + 10], R[NMAX + 10];
static int P[NMAX + 10], cnt;
static queue<int> q;

inline void detect(int i) {
    if (i + 1 <= m && a[i] && a[i + 1]) q.push(i);
    if (i - 1 >= 1 && a[i - 1] && a[i]) q.push(i - 1);
}

inline void proc() {
    while (!q.empty()) {
        int i = q.front();
        int x = a[i], y = a[i + 1];
        assert(x);
        assert(y);
        q.pop();
        if (!(L[x] <= L[y] && R[y] <= R[x]) && !a[L[x] - 1]) {
            a[L[x] - 1] = y;
            L[y] = min(L[y], L[x] - 1);
            detect(R[y]);
            detect(L[x] - 1);
        } else if (!(L[y] <= L[x] && R[x] <= R[y]) && !a[R[y] + 1]) {
            a[R[y] + 1] = x;
            R[x] = max(R[x], R[y] + 1);
            detect(R[y] + 1);
            detect(L[x]);
        }
    }
}

inline void print() {
    fprintf(stderr, "[");
    for (int i = 1; i <= m; i++) fprintf(stderr, i < m ? "%d " : "%d]\n", a[i]);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i < 2 * n; i++) {
            scanf("%d", a + i);
            if (a[i] < 0) a[i] = 0;
        }

        m = 2 * n - 1;
        a[1] = a[m] = 1;
        memset(L + 1, 0, sizeof(int) * n);
        memset(R + 1, 0, sizeof(int) * n);
        for (int i = 1; i <= m; i++) {
            if (!L[a[i]]) L[a[i]] = i;
            R[a[i]] = i;
            if (i < m && a[i] && a[i + 1]) q.push(i);
        }
        for (int i = 1; i <= n; i++) if (!L[i]) P[++cnt] = i;

        //fprintf(stderr, "T = %d\n", T + 1);
        //print();
        proc();
        //print();
        for (int i = 1; i <= m; i++) if (!a[i]) {
            assert(cnt);
            a[i] = P[cnt--];
            L[a[i]] = R[a[i]] = i;
            detect(i);
            //print();
            proc();
            //print();
        }

        for (int i = 1; i < 2 * n; i++) {
            printf("%d ", a[i]);
            assert(a[i]);
        }
        puts("");
    }
    return 0;
}
