#include <climits>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define MMAX 100
#define LMAX 100000

static int l, s, t, m;
static vector<int> stone(MMAX + 10);
static vector<char> f(LMAX + 10, MMAX + 10);
static vector<char> a(LMAX + 10, 0);
static vector<bool> marked(LMAX + 10, false);

int main() {
    ios::sync_with_stdio(false);

    cin >> l >> s >> t >> m;

    for (int i = 1; i <= m; i++) { cin >> stone[i]; }  // for

    int cnt = 0;
    if (s == t) {
        // Special judge
        for (int i = 1; i <= m; i++) {
            if (stone[i] % s == 0) { cnt++; }
        }  // for
    } else {
        stone[0] = 0;
        std::sort(&stone[1], &stone[m + 1]);

        int k = s * t;
        int offest = 0;

        // Regard the endpoint as stone in order to process it.
        stone[m + 1] = l;

        for (int i = 1; i <= m + 1; i++) {
            // Distance to last stone.
            int dist = stone[i] - offest - stone[i - 1];

            // If distance is greater than k, we can move this stone.
            if (dist > k) offest += dist - k;

            stone[i] -= offest;
            a[stone[i]] = 1;
        }  // for

        // However, the endpoint is not a stone.
        a[stone[m + 1]] = 0;

        // Array "marked" means to whether indicate a position is able to reach.
        marked[0] = true;

        // There's no stone at the beginning.
        f[0] = 0;
        for (int i = 0; i <= l - offest; i++) {
            if (marked[i]) {
                for (int j = i + s; j <= i + t; j++) {
                    marked[j] = true;

                    if (f[i] + a[j] < f[j]) { f[j] = f[i] + a[j]; }
                }
            }
        }  // for

        cnt = f[l - offest];

        // Find the minimum stones.
        for (int i = l - offest + 1; i <= l - offest + t; i++) {
            if (f[i] < cnt) { cnt = f[i]; }
        }  // for
    }

    cout << cnt;

    return 0;
}  // function main
