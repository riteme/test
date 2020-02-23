#include <cstdio>
#include <cctype>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
size_t _pos = BUFFERSIZE, _sz;
char _buf[BUFFERSIZE];

char _getc() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        _sz = fread(_buf, 1, BUFFERSIZE, stdin);
    }
    return _pos < _sz ? _buf[_pos++] : 0;
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

#define NMAX 400000

struct Edge {
    int u, v, cnt;

    int to(int x) const {
        return u == x ? v : u;
    }
};

int n, p, M, m;
int L[NMAX + 10], R[NMAX + 10];
vector<Edge*> C[NMAX + 10], I[NMAX + 10];
vector<int> ins[NMAX + 10], del[NMAX + 10];

void initialize() {
    read(n); read(p); read(M); read(m);

    for (int i = 0; i < n; i++) {
        int u, v;
        read(u); read(v);
        auto e = new Edge{u, v, 0};
        C[u].push_back(e);
        C[v].push_back(e);
    }

    for (int i = 1; i <= p; i++) {
        read(L[i]); read(R[i]);
        ins[L[i]].push_back(i);
        del[R[i]].push_back(i);
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        read(u); read(v);
        auto e = new Edge{u, v, 0};
        I[u].push_back(e);
        I[v].push_back(e);
    }
}

int main() {
    initialize();

    int cov = 0, ind = 0, i;
    for (i = 1; i <= M; i++) {
        for (int u : ins[i]) {

        }

        if (cov == n && ind == 0)
            break;

        for (int u : del[i]) {

        }
    }

    if (i <= M) {
        int cnt = 0;
        for (int j = 1; j <= p; j++)
            cnt += L[j] <= i && i <= R[j];

        printf("%d %d\n", cnt, i);
        for (int j = 1; j <= p; j++)
        if (L[j] <= i && i <= R[j])
            printf("%d ", j);
        puts("");
    } else puts("-1");

    return 0;
}