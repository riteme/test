#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100

static int fa[NMAX + 10];

int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}

bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

static int n;

int main(int argc, char *argv[]) {
    n = atoi(argv[1]);
    int T = 10;
    for (int X = 0; ; X++) {
        memset(fa + 1, 0, sizeof(int) * n);
        int cnt = 1;
        for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++)
        if (__gcd(X + i, X + j) > 1) {
            int u = find(i), v = find(j);
            if (u != v) {
                cnt++;
                fa[u] = v;
            }
        }
        if (cnt == n) {
            printf("X = %d\n", X);
            for (int i = 2; i < n; i++) if (is_prime(i))
                printf("X ≡ %d (mod %d) [%d]\n", X % i, i, i - X % i);
            T--;
            if (!T) break;
        }
    }
    return 0;
}
