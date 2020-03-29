#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000

int n, K;
int a[NMAX + 10];

int main() {
    while (scanf("%d%d", &n, &K) != EOF) {
        for (int i = 1; i <= n; i++)
            scanf("%d", a + i);

        a[0] = -1;
        if (K == 1) puts("Alice");
        else {
            int sg = 0;
            for (int i = n; i >= 1; i -= 2)
                sg ^= a[i] - a[i - 1] - 1;

            if (K == 2 && (n & 1))
                sg ^= a[1] ^ (a[1] - 1);

            puts(!!sg ? "Alice" : "Bob");
        }
    }
    return 0;
}