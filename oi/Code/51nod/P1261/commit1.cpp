#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define KMAX 500
#define MOD 1000000007

typedef long long int64;

static int64 n;
static int k;
static int f[2][10][KMAX];

int main() {
    scanf("%lld%d", &n, &k);
    
    int current = 0, last = 1;
    for (int i = 1; i <= 9; i++)
        f[1][i][i % k] = 1;

    for (int i = 2; i <= n; i++) {
        memset(&f[current][0][0], 0, sizeof(f) / 2);
            
        for (int m = 0; m < k; m++) {
            for (int d = 1; d <= 9; d++) {
                for (int nd = d; nd <= 9; nd++) {
                    f[current][nd][(m * 10 + nd) % k] += f[last][d][m];
                    f[current][nd][(m * 10 + nd) % k] %= MOD;
                }
            }
        }
        
        swap(current, last);
    }

    int answer = 0;
    for (int d = 1; d <= 9; d++)
        answer = (answer + f[last][d][0]) % MOD;

    printf("%d\n", answer);

    return 0;
}
