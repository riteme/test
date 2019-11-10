// FSX nb!

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000000

static int n;
static int p[NMAX + 10], pos[NMAX + 10];

void rswap(int i, int j) {
    //fprintf(stderr, "swap %d, %d\n", i, j);
    swap(p[i], p[j]);
    pos[p[i]] = i;
    pos[p[j]] = j;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", p + i);
        pos[p[i]] = i;
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) if (p[i] != i) {
        cnt++;
        rswap(i, pos[i]);
    }
    puts((cnt & 1) == (3 * n & 1) ? "Petr" : "Um_nik");
    return 0;
}
