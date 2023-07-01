#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 7000;

int n, K;
int a[NMAX + 10];
int s[NMAX + 10];
int rev[NMAX + 10];

int c2(int m) {
    return m * (m + 1) / 2;
}

int locate(int v) {
    for (int i = 1; i <= n; i++) {
        if (a[i] == v)
            return i;
    }
    return -1;
}

int main() {
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
    }
    for (int i = n; i >= 1; i--) {
        rev[i] = rev[i + 1];
        for (int j = i + 1; j <= n; j++) {
            if (a[i] > a[j])
                rev[i]++;
        }
    }

    for (int i = 1; i <= n; i++) {
        int b = 0;
        for (int j = i + 1; j <= n; j++) {
            if (a[j] < a[i])
                b++;
        }
        int c = b + 1 + c2(n - i);

        // printf("b=%d, c=%d, K=%d, i=%d\n", b, c, K, i);
        if (b < K && K <= c) {
            K -= b;
            int m = rev[i + 1] + 1;
            // printf("m=%d\n", m);
            if (K == m)
                break;
            else if (K > m)
                K--;
        } else {
            memcpy(s + 1, a + 1, sizeof(int) * n);
            sort(s + i, s + n + 1);
            int v;
            if (K <= b)
                v = s[i + K - 1];
            else
                v = s[i + K - c + b];
            // printf("v=%d\n", v);
            reverse(a + i, a + locate(v) + 1);
            break;
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%d ", a[i]);
    }
    puts("");

    return 0;
}
