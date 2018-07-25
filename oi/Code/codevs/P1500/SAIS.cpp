#pragma GCC optimize("O3")

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
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

#define MEMORYSIZE 20000000
static int _memory[MEMORYSIZE];
static size_t _memcnt = 0;
void *operator new(std::size_t size) {
    int *mem = _memory + _memcnt;
    _memcnt += size;
    return mem;
}

#define BUFFERSIZE 150000

static char buffer[BUFFERSIZE];
static int str[BUFFERSIZE];

#define L_TYPE 0
#define S_TYPE 1

inline bool is_lms_char(int *type, int x) {
    return x > 0 && type[x] == S_TYPE && type[x - 1] == L_TYPE;
}

inline bool equal_substring(int *S, int x, int y, int *type) {
    do {
        if (S[x] != S[y])
            return false;
        x++, y++;
    } while (!is_lms_char(type, x) && !is_lms_char(type, y));

    return S[x] == S[y];
}

inline void induced_sort(int *S, int *SA, int *type, int *bucket, int *lbucket,
                         int *sbucket, int n, int SIGMA) {
    for (int i = 0; i <= n; i++)
        if (SA[i] > 0 && type[SA[i] - 1] == L_TYPE)
            SA[lbucket[S[SA[i] - 1]]++] = SA[i] - 1;
    for (int i = 1; i <= SIGMA; i++)  // Reset S-type bucket
        sbucket[i] = bucket[i] - 1;
    for (int i = n; i >= 0; i--)
        if (SA[i] > 0 && type[SA[i] - 1] == S_TYPE)
            SA[sbucket[S[SA[i] - 1]]--] = SA[i] - 1;
}

static int *sort_suffix(int *S, int length, int SIGMA) {
    int n = length - 1;
    int *type = new int[n + 1];
    int *position = new int[n + 1];
    int *name = new int[n + 1];
    int *SA = new int[n + 1];
    int *bucket = new int[SIGMA + 1];
    int *lbucket = new int[SIGMA + 1];
    int *sbucket = new int[SIGMA + 1];

    memset(bucket, 0, sizeof(int) * (SIGMA + 1));
    for (int i = 0; i <= n; i++)
        bucket[S[i]]++;
    for (int i = 1; i <= SIGMA; i++) {
        bucket[i] += bucket[i - 1];
        lbucket[i] = bucket[i - 1];
        sbucket[i] = bucket[i] - 1;
    }

    type[n] = S_TYPE;
    for (int i = n - 1; i >= 0; i--) {
        if (S[i] < S[i + 1])
            type[i] = S_TYPE;
        else if (S[i] > S[i + 1])
            type[i] = L_TYPE;
        else
            type[i] = type[i + 1];
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (type[i] == S_TYPE && type[i - 1] == L_TYPE)
            position[cnt++] = i;

    fill(SA, SA + n + 1, -1);
    for (int i = 0; i < cnt; i++)
        SA[sbucket[S[position[i]]]--] = position[i];
    induced_sort(S, SA, type, bucket, lbucket, sbucket, n, SIGMA);

    fill(name, name + n + 1, -1);
    int lastx = -1, namecnt = 1;
    bool flag = false;
    for (int i = 1; i <= n; i++) {
        int x = SA[i];

        if (is_lms_char(type, x)) {
            if (lastx >= 0 && !equal_substring(S, x, lastx, type))
                namecnt++;
            if (lastx >= 0 && namecnt == name[lastx])
                flag = true;

            name[x] = namecnt;
            lastx = x;
        }
    }  // for
    name[n] = 0;

    int *S1 = new int[cnt];
    int pos = 0;
    for (int i = 0; i <= n; i++)
        if (name[i] >= 0)
            S1[pos++] = name[i];

    int *SA1;
    if (!flag) {
        SA1 = new int[cnt];

        for (int i = 0; i < cnt; i++)
            SA1[S1[i]] = i;
    } else
        SA1 = sort_suffix(S1, cnt, namecnt);

    lbucket[0] = sbucket[0] = 0;
    for (int i = 1; i <= SIGMA; i++) {
        lbucket[i] = bucket[i - 1];
        sbucket[i] = bucket[i] - 1;
    }
    fill(SA, SA + n + 1, -1);
    for (int i = cnt - 1; i >= 0; i--)
        SA[sbucket[S[position[SA1[i]]]]--] = position[SA1[i]];
    induced_sort(S, SA, type, bucket, lbucket, sbucket, n, SIGMA);

    return SA;
}

static int lcp[BUFFERSIZE];
static int rnk[BUFFERSIZE];

static void compute_lcp(int length, int *SA) {
    int j = 0;
    for (int i = 0; i <= length; i++) {
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
    int length = read_string(buffer);
    buffer[length] = '$';

    for (int i = 0; i <= length; i++)
        str[i] = buffer[i];
    int *SA = sort_suffix(str, length + 1, 256);

    for (int i = 0; i <= length; i++) {
        rnk[SA[i]] = i;
    }  // for

    compute_lcp(length, SA);

    for (int i = 1; i <= length; i++)
        putint(SA[i] + 1);
    *out_tail++ = '\n';
    for (int i = 2; i <= length; i++)
        putint(lcp[i]);

    fwrite(_BUFFER, 1, out_tail - _BUFFER, stdout);
    return 0;
}  // function main
