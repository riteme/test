#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    int t[110];
    for (int i = 1; i <= n; i++) { cin >> t[i]; }  // for

    int finc[110];  // Increasing sequence
    int fdec[110];  // Decreasing sequence
    memset(finc, 0, sizeof(finc));
    memset(fdec, 0, sizeof(fdec));

    // Compute LIS
    finc[1] = 1;
    for (int i = 2; i <= n; i++) {
        int max = 0;

        for (int j = 1; j < i; j++) {
            if (t[j] < t[i] and max < finc[j]) { max = finc[j]; }
        }

        finc[i] = max + 1;
    }  // for

    // Compute LDS
    fdec[n] = 1;
    for (int i = n - 1; i >= 1; i--) {
        int max = 0;

        for (int j = n; j > i; j--) {
            if (t[j] < t[i] and max < fdec[j]) { max = fdec[j]; }
        }  // for

        fdec[i] = max + 1;
    }  // for

    int m = INT_MAX;
    for (int i = 1; i <= n; i++) {
        int k = finc[i] + fdec[i] - 1;
        if (n - k < m) { m = n - k; }
    }  // for

    cout << m;

    return 0;
}  // function main
