#include <cstdio>

#define NMAX 10000

static int x[NMAX + 10];
static int y[NMAX + 10];
static int w[NMAX + 10];
static int h[NMAX + 10];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%d%d%d%d", x + i, y + i, w + i, h + i);

    int X, Y;
    int answer = -1;
    scanf("%d%d", &X, &Y);
    for (int i = 1; i <= n; i++)
        if (x[i] <= X && X <= x[i] + w[i] &&
            y[i] <= Y && Y <= y[i] + h[i])
            answer = i;

    printf("%d\n", answer);
    return 0;
}
