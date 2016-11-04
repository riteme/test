#include <cstdio>

#define NMAX 100000

typedef long long int64;

static int n;
static int64 seq[NMAX + 10];
static int64 modified[NMAX + 10];

static void move(int x) {
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (seq[i] & (1 << x))
            cnt++;
    for (int i = 1; i <= cnt; i++)
        modified[i] += (1 << x);
}

int main() {
    freopen("andor.in", "r", stdin);
    freopen("andor.out", "w", stdout);
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%lld", seq + i);

    for (int i = 0; i <= 20; i++)
        move(i);

    int64 answer = 0;
    for (int i = 1; i <= n; i++)
        answer += modified[i] * modified[i];
    printf("%lld\n", answer);
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
