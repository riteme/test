#pragma GCC optimize("O3")

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define _BUFFERSIZE 65536
static unsigned long _pos = _BUFFERSIZE;
static char _buffer[_BUFFERSIZE];

inline unsigned long read_string(char *dest) {
    unsigned long read = 0;
    while (true) {
        if (_pos == _BUFFERSIZE) {
            _pos = 0;
            fread(_buffer, 1, _BUFFERSIZE, stdin);
        }

        char c = _buffer[_pos++];
        if ('a' <= c && c <= 'z')
            dest[read++] = c;
        else
            break;
    }  // while

    return read;
}

#define BUFFERSIZE 150000
#define NMAX BUFFERSIZE

static char buffer[BUFFERSIZE];

#define rep(i, l, r) for (register int i = (l); i <= (r); ++i)
#define rrep(i, r, l) for (register int i = (r); i >= (l); --i)
#define PUTS(x) sa[cur[str[x]]--] = x
#define PUTL(x) sa[cur[str[x]]++] = x
#define LMS(x) (!type[x - 1] && type[x])
#define RESET memset(sa + 1, 0, sizeof(int) * (n + 1)); \
    memcpy(cur + 1, cnt + 1, sizeof(int) * m);
#define INDUCE rep(i, 1, m) cur[i] = cnt[i - 1] + 1; \
    rep(i, 1, n + 1) if (sa[i] > 1 && !type[sa[i] - 1]) PUTL(sa[i] - 1); \
    memcpy(cur + 1, cnt + 1, sizeof(int) * m); \
    rrep(i, n + 1, 1) if (sa[i] > 1 && type[sa[i] - 1]) PUTS(sa[i] - 1);
void sais(int n, int m, int *str, int *sa) {
    static int id[NMAX + 10];
    vector<bool> type(n + 2);
    type[n + 1] = true;
    rrep(i, n, 1) type[i] = str[i] == str[i + 1] ? type[i + 1] : str[i] < str[i + 1];
    int cnt[m + 1], cur[m + 1], idx = 1, y = 0, rt, lrt, *ns = str + n + 2, *nsa = sa + n + 2;
    memset(cnt, 0, sizeof(int) * (m + 1));
    rep(i, 1, n + 1) cnt[str[i]]++;
    rep(i, 1, m) cnt[i] += cnt[i - 1];
    RESET rep(i, 2, n + 1) if (LMS(i)) PUTS(i); INDUCE
    memset(id + 1, 0, sizeof(int) * n);
    rep(i, 2, n + 1) if (LMS(sa[i])) {
        register int x = sa[i];
        for (rt = x + 1; !LMS(rt); rt++) ;
        id[x] = y && rt + y == lrt + x && !memcmp(str + x, str + y, sizeof(int) * (rt - x + 1)) ? idx : ++idx;
        y = x, lrt = rt;
    }
    int len = 0, pos[(n >> 1) + 1];
    rep(i, 1, n) if (id[i]) {
        ns[++len] = id[i];
        pos[len] = i;
    }
    ns[len + 1] = 1, pos[len + 1] = n + 1;
    if (len == idx - 1) rep(i, 1, len + 1) nsa[ns[i]] = i;
    else sais(len, idx, ns, nsa);
    RESET rrep(i, len + 1, 1) PUTS(pos[nsa[i]]); INDUCE
}
static int str[NMAX * 3 + 10], sa[NMAX * 3 + 10];
static int lcp[BUFFERSIZE];
static int rnk[BUFFERSIZE];

static void compute_lcp(int length, int *SA) {
    int j = 0;
    for (int i = 1; i <= length + 1; i++) {
        if (rnk[i] == 0)
            continue;
        j--;
        if (j < 0)
            j = 0;
        while (buffer[SA[rnk[i]] + j] == buffer[SA[rnk[i] - 1] + j])
            j++;
        lcp[rnk[i]] = j;
    }  // for
}

//
// Output optimization by RatingAccelerator2
//
const int BufferSize = 1180000;

char _BUFFER[BufferSize];
char *out_tail = _BUFFER;

inline void putint(int x) {
    if (!x)
        *out_tail++ = '0';
    else {
        char s_pool[6], *s_tail = s_pool;
        while (x != 0)
            *s_tail++ = x % 10 + '0', x /= 10;
        while (s_tail-- != s_pool)
            *out_tail++ = *s_tail;
    }
    *out_tail++ = ' ';
}

int main() {
    // scanf("%s", buffer);
    int length = read_string(buffer + 1);
    buffer[length + 1] = 1;

    for (int i = 1; i <= length + 1; i++)
        str[i] = buffer[i];
    sais(length, 127, str, sa);

    for (int i = 1; i <= length + 1; i++) {
        rnk[sa[i]] = i;
    }  // for

    compute_lcp(length, sa);

    for (int i = 2; i <= length + 1; i++)
        putint(sa[i]);
    *out_tail++ = '\n';
    for (int i = 3; i <= length + 1; i++)
        putint(lcp[i]);

    fwrite(_BUFFER, 1, out_tail - _BUFFER, stdout);
    return 0;
}  // function main
