#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

constexpr int NMAX = 100000;
constexpr int INF = 0x3f3f3f3f;

int n;
char s1[NMAX + 10];
char s2[NMAX + 10];
char s3[NMAX + 10];
int f[NMAX + 10];

int cmp0(int i) {
    int cnt = 0;
    if (s1[i + 0] != '.')
        cnt++;
    if (s1[i + 1] != '#')
        cnt++;
    if (s1[i + 2] != '.')
        cnt++;
    if (s2[i + 0] != '#')
        cnt++;
    if (s2[i + 1] != '#')
        cnt++;
    if (s2[i + 2] != '.')
        cnt++;
    if (s3[i + 0] != '.')
        cnt++;
    if (s3[i + 1] != '#')
        cnt++;
    if (s3[i + 2] != '.')
        cnt++;
    return cnt;
}

int cmp1(int i) {
    int cnt = 0;
    if (s1[i + 0] != '#')
        cnt++;
    if (s1[i + 1] != '#')
        cnt++;
    if (s1[i + 2] != '#')
        cnt++;
    if (s1[i + 3] != '.')
        cnt++;
    if (s2[i + 0] != '#')
        cnt++;
    if (s2[i + 1] != '.')
        cnt++;
    if (s2[i + 2] != '#')
        cnt++;
    if (s2[i + 3] != '.')
        cnt++;
    if (s3[i + 0] != '#')
        cnt++;
    if (s3[i + 1] != '#')
        cnt++;
    if (s3[i + 2] != '#')
        cnt++;
    if (s3[i + 3] != '.')
        cnt++;
    return cnt;
}

int main() {
    scanf("%d%s%s%s", &n, s1 + 1, s2 + 1, s3 + 1);
    s1[n + 1] = '.';
    s2[n + 1] = '.';
    s3[n + 1] = '.';
    n++;
    f[0] = 0;
    for (int i = 1; i <= n; i++) {
        f[i] = INF;
        if (i - 3 >= 0)
            f[i] = min(f[i], f[i - 3] + cmp0(i - 2));
        if (i - 4 >= 0)
            f[i] = min(f[i], f[i - 4] + cmp1(i - 3));
    }
    printf("%d\n", f[n]);
    return 0;
}
