#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n, c;
    cin >> n >> c;

    int w[n];
    for (int i = 0; i < n; i++) { cin >> w[i]; }  // for

    int d[c + 1];
    memset(d, 0, sizeof(int) * (c + 1));

    for (int i = 0; i < n; i++) {
        for (int j = c; j >= w[i]; j--) {
            d[j] = std::max(d[j], d[j - w[i]] + w[i]);
        }  // for
    }      // for

    cout << d[c] << endl;

    return 0;
}  // function main
