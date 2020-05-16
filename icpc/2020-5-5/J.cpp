#include <cstdio>
#include <cctype>
#include <cstring>
#include <cassert>

#include <random>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
size_t _pos = BUFFERSIZE;
char _buf[BUFFERSIZE];

char _getc() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buf, 1, BUFFERSIZE, stdin);
    }
    return _buf[_pos++];
}

template <typename T>
void read(T &x) {
    x = 0;
    char c;
    do c = _getc(); while (!isdigit(c));
    do {
        x = x * 10 + c - '0';
        c = _getc();
    } while (isdigit(c));
}

#define NMAX 200000

int n, q, K, S;
int a[NMAX + 10];
int pre[NMAX + 10], suf[NMAX + 10];

void build() {
    pre[0] = a[0];
    suf[n - 1] = a[n - 1];
    for (int i = 1; i < n - 1; i++)
        pre[i] = min(pre[i - 1], a[i]);
    for (int i = n - 2; i >= 0; i--)
        suf[i] = min(suf[i + 1], a[i]);
}

void do_swap(int i, int j) {
    swap(a[i], a[j]);
    pre[i] = min((i ? pre[i - 1] : n), a[i]);
    suf[j] = min((j < n - 1 ? suf[j + 1] : n), a[j]);
}

int query(int l, int r) {
    int ans = n;
    if (l)
        ans = min(ans, pre[l - 1]);
    if (r < n - 1)
        ans = min(ans, suf[r + 1]);
    return ans;
}

int main() {
    read(n); read(q); read(K); read(S);
    // scanf("%d%d%d%d", &n, &q, &K, &S);
    for (int i = 0; i < n; i++)
        // scanf("%d", a + i);
        read(a[i]);
    build();

    mt19937 gen;
    gen.seed(S);
    int last = 0;
    while (q--) {
        int op = gen() % K;
        int i = (gen() + last) % n;
        if (!op && i)
            do_swap(i - 1, i);
        else {
            int j = gen() % n;
            if (i > j)
                swap(i, j);
            int ans = query(i, j);
            last ^= ans;
        }
    }

    printf("%d\n", last);
    return 0;
}