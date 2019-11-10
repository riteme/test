// FSX nb!

#include <cstdio>
#include <climits>

void emit(int n, int s) {
    for (int i = s; i >= 1; i--)
    for (int j = i; j <= n; j += s)
        printf("%d ", j);
    puts("");
}

int main() {
    int n;
    scanf("%d", &n);
    int mi = INT_MAX, d;
    for (int i = 1; i <= n; i++) {
        int c = i + (n + i - 1) / i;
        if (mi > c) {
            mi = c;
            d = i;
        }
    }
    fprintf(stderr, "mi = %d, d = %d\n", mi, d);
    emit(n, d);
    return 0;
}
