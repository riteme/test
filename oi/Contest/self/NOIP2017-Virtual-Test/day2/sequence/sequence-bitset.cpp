#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <climits>

#include <bitset>
#include <algorithm>

using namespace std;

#define NMAX 2000
#define BITSET_SIZE (NMAX + 1)

static int n;
static char str[NMAX + 10];
static bitset<BITSET_SIZE> f[NMAX + 10];
static bitset<BITSET_SIZE> cnt;

int main() {
    scanf("%s", str);
    n = strlen(str);
    
    f[0][0] = 1;
    bitset<BITSET_SIZE> t;
    for (int i = 0; i < n; i++) {
        for (int j = n; j >= 0; j--) {
            t.reset();

            if (str[i] != '0') {
                t[j + 1] = (f[j] << (NMAX - j)).count() & 1;
                t ^= (f[j] >> (j + 1)) << (j + 2);
            }

            if (str[i] != '1' && j > 0)
                t ^= f[j - 1];

            f[j] = t;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (f[i][j])
                cnt.flip(max(i, j));
        }
    }

    for (int i = 1; i <= n; i++) {
        putchar(cnt[i] + '0');
    }
    putchar('\n');

    return 0;
}
