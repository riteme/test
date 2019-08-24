#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> d(n);
    for (int i = 0; i < n; i++) { cin >> d[i]; }  // for

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (d[j] < d[i]) { cnt++; }
        }  // for
    }      // for

    cout << cnt;

    return 0;
}  // function main
