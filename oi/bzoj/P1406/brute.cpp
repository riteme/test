#include <cstdio>

typedef long long i64;

int main() {
    i64 n;
    scanf("%lld", &n);

    bool flag = true;
    for (i64 x = 0; x < n; x++) {
        if (x * x % n == 1) {
            printf("%lld\n", x);
            flag = false;
        }
    }

    if (flag)
        printf("None\n");

    return 0;
}
