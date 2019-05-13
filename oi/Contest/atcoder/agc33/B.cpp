#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200000

static int H, W, n, x0, y0;
static char S[NMAX + 10], T[NMAX + 10];

int main() {
    scanf("%d%d%d%d%d%s%s", &H, &W, &n, &x0, &y0, S + 1, T + 1);
    bool ok = true;
    int x = x0, y = y0;
    for (int i = 1; i <= n; i++) {
        if (S[i] == 'L') y--;
        if (y < 1 || y > W) ok = false;
        if (y < W && T[i] == 'R') y++;
    }
    x = x0, y = y0;
    for (int i = 1; i <= n; i++) {
        if (S[i] == 'R') y++;
        if (y < 1 || y > W) ok = false;
        if (y > 1 && T[i] == 'L') y--;
    }
    x = x0, y = y0;
    for (int i = 1; i <= n; i++) {
        if (S[i] == 'U') x--;
        if (x < 1 || x > H) ok = false;
        if (x < H && T[i] == 'D') x++;
    }
    x = x0, y = y0;
    for (int i = 1; i <= n; i++) {
        if (S[i] == 'D') x++;
        if (x < 1 || x > H) ok = false;
        if (x > 1 && T[i] == 'U') x--;
    }
    puts(ok ? "YES" : "NO");
    return 0;
}
