#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define NMAX 10000

static int n;
static int A[NMAX + 10];
static int B[NMAX + 10];
static int W[NMAX + 10];
static int H[NMAX + 10];

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d", A + i, B + i, W + i, H + i);
    }  // for

    int x, y;
    int answer = -1;
    scanf("%d%d", &x, &y);

    for (int i = 1; i <= n; i++) {
        if (A[i] <= x && x <= A[i] + W[i] && B[i] <= y && y <= B[i] + H[i])
            answer = i;
    }  // for

    printf("%d\n", answer);

    return 0;
}  // function main
