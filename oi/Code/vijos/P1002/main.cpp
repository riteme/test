#include <climits>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define MMAX 100
#define LMAX 1000000

static int l, s, t, m;
static int stone[MMAX + 10];
static vector<int> f(LMAX + 10, INT_MAX);
static vector<int> a(LMAX + 10, 0);
static vector<bool> marked(LMAX + 10, false);

int main() {
    ios::sync_with_stdio(false);

    cin >> l >> s >> t >> m;

    for (int i = 1; i <= m; i++) { cin >> stone[i]; }  // for

    int cnt = 0;
    if (s == t) {
        for (int i = 1; i <= m; i++) {
            if (stone[i] % s == 0) { cnt++; }
        }  // for
    } else {
        stone[0] = 0;
        std::sort(&stone[1], &stone[m + 1]);

        int k = s * t;
        int offest = 0;

        for (int i = 1; i <= m; i++) {
            int dist = stone[i] - offest - stone[i - 1];

            if (dist > k) { offest += k; }

            stone[i] -= offest;
            a[stone[i]] = 1;
        }  // for

        marked[0] = true;
        f[0] = 0;
        for (int i = 0; i <= l - s - offest; i++) {
            if (marked[i]) {
                for (int j = i + s; j <= i + t and j <= l - offest; j++) {
                    marked[j] = true;

                    if (f[i] + a[j] < f[j]) { f[j] = f[i] + a[j]; }
                }
            }
        }  // for

        cnt = f[l - offest];
    }

    cout << cnt;

    return 0;
}  // function main
