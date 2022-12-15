#include <cstdio>
#include <cstdlib>

int a[2000][2000];
bool used[1000 * 1000 + 10];
int b[1000 * 1000 + 10];

bool isprime(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int choose(int x, int y, int m) {
    for (int k = m; k >= 2; k -= 2) {
        if (used[k])
            continue;
        if ((!x || !isprime(x + k)) && (!y || !isprime(y + k)))
            return k;
    }
    abort();
}

int main() {
    int n;
    scanf("%d", &n);

    if (n == 3) {
        puts("3 9 1 \n5 7 8\n4 2 6");
        return 0;
    }

    int k = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] = k;
            used[k] = true;
            k += 2;
            if (k > n * n) {
                a[1][1] = k - 2;
                a[i][j] = 1;
                goto out1;
            }
        }
    }
out1:
    int m = n * n;
    if (m % 2 == 1)
        m--;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] % 2 == 0)
                continue;
            if (i < n && a[i + 1][j] == 0) {
                k = choose(a[i][j], (j > 1 ? a[i + 1][j - 1] : 0), m);
                a[i + 1][j] = k;
                used[k] = true;
            }
            if (j < n && a[i][j + 1] == 0) {
                k = choose(a[i][j], (i > 1 ? a[i - 1][j + 1] : 0), m);
                a[i][j + 1] = k;
                used[k] = true;
            }
        }
    }
    k = 2;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] == 0) {
                while (used[k]) {
                    k += 2;
                }
                a[i][j] = k;
                used[k] = true;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", a[i][j]);
        }
        puts("");
    }

    return 0;
}
