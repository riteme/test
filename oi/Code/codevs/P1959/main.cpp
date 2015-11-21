#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

static int n;
static int bound;
static int W[101];
static bool f[51][22501][101];

int main() {
    ios::sync_with_stdio(false);

    cin >> n;

    int sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> W[i];
        sum += W[i];
    }  // for
    bound = sum / 2;

    memset(f, false, sizeof(f));
    // memset(b, false, sizeof(b));

    f[0][0][0] = true;
    for (int i = 1; i <= n / 2 + (n % 2 == 1 ? 1 : 0); i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = W[j]; k <= bound; k++) {
                if (!f[i - 1][k - W[j]][j] and f[i - 1][k - W[j]][0]) {
                    f[i][k][0] = f[i][k][j] = true;
                }
            }  // for
        }      // for
    }          // for

    int m = 0;
    for (int i = bound; i >= 0; i--) {
        if (f[n / 2][i][0] or (n % 2 == 1 and f[n / 2 + 1][i][0])) {
            m = i;
            break;
        }
    }  // for

    // int m = 0;
    // for (int k = bound; k >= 0; k--) {
    //     if (!f[k]) continue;

    //     int cnt = std::count(&b[k][1], &b[k][n + 1], true);

    //     if ((cnt == n / 2 or cnt == n / 2 + (n % 2 == 1 ? 1 : 0)) and m < k)
    //     {
    //         m = k;
    //     }
    // }  // for

    // for (int i = 1; i <= bound; i++) { cout << f[i]; }  // for
    // cout << endl;

    // for (int x = 1; x <= n / 2 + (n % 2 == 1 ? 1 : 0); x++) {
    //     for (int y = 1; y <= bound; y++) { cout << f[x][y][0]; }  // for
    //     cout << endl;
    // }  // for

    cout << m << ' ' << sum - m;

    return 0;
}  // function main
