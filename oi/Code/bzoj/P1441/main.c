#include <stdio.h>

typedef long long int64;

int64 gcd(int64 a, int64 b) {
    if (b == 0)
	return a;
    return gcd(b, a % b);
}

int main() {
    int n;
    scanf("%d", &n);

    int64 answer = 0;
    int i;
    for (i = 0; i < n; i++) {
	int64 x;
	scanf("%lld", &x);
	answer = gcd(x, answer);
    }

    printf("%lld\n", answer < 0 ? -answer : answer);

    return 0;
}
