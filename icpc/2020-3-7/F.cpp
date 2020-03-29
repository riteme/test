#include <cstdio>
#include <cstring>

#include <bitset>
#include <algorithm>

using namespace std;

#define NMAX 262144

typedef bitset<NMAX> bits;

int read() {
    char buf[8];
    scanf("%s", buf);
    if (buf[0] != '-') {
        buf[1] = buf[2];
        buf[2] = buf[3];
        buf[3] = buf[4];
        buf[4] = buf[5];
        buf[5] = 0;
    } else {
        buf[2] = buf[3];
        buf[3] = buf[4];
        buf[4] = buf[5];
        buf[5] = buf[6];
        buf[6] = 0;
    }
    return atoi(buf);
}

int n, target;

void solve() {
    target = read();
    target += NMAX - 20000;
    scanf("%d", &n);
    bits mask;
    mask[NMAX - 20000] = 1;
    for (int i = 0; i < n; i++) {
        int offset = read();
        if (offset < 0)
            mask |= mask >> -offset;
        else if (offset > 0)
            mask |= mask << offset;
    }

    int ans = 0;
    for (int i = 1; i < NMAX; i++)
        if (mask[i] && abs(target - i) < abs(target - ans))
            ans = i;

    ans -= NMAX - 20000;
    bool f = ans < 0;
    ans = abs(ans);
    char buf[16];
    sprintf(buf, "%.5d", ans);
    if (f) putchar('-');
    putchar(buf[0]);
    putchar('.');
    putchar(buf[1]);
    putchar(buf[2]);
    putchar(buf[3]);
    putchar(buf[4]);
    putchar('\n');
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }

    return 0;
}