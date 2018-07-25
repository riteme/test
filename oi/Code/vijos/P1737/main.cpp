#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

typedef long long int64;

#define KMAX 50
#define NMAX 200000

static int n, k, p;
static int color[NMAX + 10];
static int price[NMAX + 10];
static int64 pre[KMAX + 10][NMAX + 10];
static int64 answer;

static void initialize() {
    scanf("%d%d%d", &n, &k, &p);

    for (int i = 1; i <= n; i++) {
        scanf("%d%d", color + i, price + i);
        pre[color[i]][i] = 1;
    }  // for

    for (int c = 0; c < k; c++) {
        for (int i = 1; i <= n; i++) {
            pre[c][i] += pre[c][i - 1];
        }  // for
    }      // for
}

int main() {
    initialize();

    int ptr = 0;
    for (int i = 1; i <= n; i++) {
        if (price[i] <= p)
            ptr = i;

        answer += pre[color[i]][ptr];

        if (ptr == i)
            answer--;
    }  // for

    printf("%lld\n", answer);

    return 0;
}  // function main
