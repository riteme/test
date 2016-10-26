#include <cmath>
#include <cstdio>

inline int gcd(int a, int b) {
    while (b) {
        int tmp = a;
        a = b;
        b = tmp % b;
    }

    return a;
}

static int a0, a1, b0, b1;
static int base;

inline int test(int x) {
    return x / gcd(x, b0) == base && gcd(x, a0) == a1;
}

static int query() {
    base = b1 / b0;

    int answer = 0;
    int bound = sqrt(b1) + 0.5;
    for (int i = 1; i <= bound; i++) {
        if (b1 % i == 0) {
            answer += test(i);

            if (i != b1 / i)
                answer += test(b1 / i);
        }
    }

    return answer;
}

int main() {
    int n;
    scanf("%d", &n);

    while (n--) {
        scanf("%d%d%d%d", &a0, &a1, &b0, &b1);

        printf("%d\n", query());
    }
}
