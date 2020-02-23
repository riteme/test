#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define mxc 26
#define mxn 250000
#define mxv (mxn * 2)

typedef pair<int, int> pii;

struct SAM {
    int e[mxv][mxc], f[mxv], len[mxv], sz;
    int NEW(int tlen) {
        ++sz, f[sz] = 0, len[sz] = tlen;
        memset(e[sz], 0, sizeof e[sz]);
        return sz;
    }
    void clear() {
        sz = -1;
        NEW(-1);
        NEW(0);
        fill(e[0], e[0] + mxc, 1);
    }
    int add(int x, char c) {
        int y = e[x][c] ? 0 : NEW(len[x] + 1);
        while (x && !e[x][c])
            e[x][c] = y, x = f[x];
        if (!x) f[y] = 1;
        else {
            int a = e[x][c];
            if (len[x] + 1 == len[a]) f[y] = a;
            else {
                int b = NEW(len[x] + 1);
                copy(e[a],e[a] + mxc, e[b]);
                f[b] = f[a], f[a] = f[y] = b;
                while (x && e[x][c] == a)
                    e[x][c] = b, x = f[x];
            }
        }
        return y ? y : f[y];
    }
    pii to(int x, int l, char c) {
        while (!e[x][c]) l = len[x = f[x]];
        return {e[x][c], l + 1};
    }
};

#define NMAX mxn
#define SIGMA mxc

SAM sam;
char s[NMAX + 10];
bool has[1000];
int q;
char buf[NMAX + 10];

int main() {
    scanf("%s", s);
    sam.clear();
    int x = 1;
    for (int i = 0; s[i]; i++) {
        has[s[i]] = true;
        x = sam.add(x, s[i] - 'A');
    }

    scanf("%d", &q);
    while (q--) {
        scanf("%s", buf);
        x = 1;
        int cnt = 0, len = 0;
        for (int i = 0; buf[i]; i++) {
            if (!has[buf[i]]) {
                cnt = -1;
                break;
            }
            auto _ = sam.to(x, len, buf[i] - 'A');
            if (_.second <= len) {
                _ = sam.to(1, 0, buf[i] - 'A');
                x = _.first;
                len = _.second;
                cnt++;
            } else {
                x = _.first;
                len = _.second;
            }
        }
        if (cnt >= 0 && len) cnt++;
        printf("%d\n", cnt);
    }

    return 0;
}