#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int V, G, N;
    cin >> V >> G >> N;

    int t[N], v[N], g[N];
    for (int i = 0; i < N; i++) { cin >> t[i] >> v[i] >> g[i]; }  // for

    int d[N][G + 1], n[N][G + 1];
    memset(d, 0, sizeof(d));
    memset(n, 0, sizeof(n));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= G; j++) {
            if (i == 0) {
                if (g[i] <= j && v[i] <= V) {
                    d[i][j] = t[i];
                    n[i][j] = v[i];
                }
            } else {
                d[i][j] = d[i - 1][j];
                n[i][j] = n[i - 1][j];

                if (g[i] <= j) {
                    int tMax = std::max(d[i - 1][j], d[i - 1][j - g[i]] + t[i]);

                    if (tMax != d[i - 1][j] && n[i - 1][j - g[i]] + v[i] <= V) {
                        d[i][j] = tMax;
                        n[i][j] = n[i - 1][j - g[i]] + v[i];
                    }
                }
            }
        }  // for
    }      // for

    int solution = 0;

    for (int x = 0; x < N; x++) {
        for (int y = 0; y <= G; y++) {
            cout << d[x][y] << ' ';
            if (d[x][y] > solution) { solution = d[x][y]; }
        }  // for
        cout << endl;
    }  // for

    cout << endl;

    for (int x = 0; x < N; x++) {
        for (int y = 0; y <= G; y++) { cout << n[x][y] << ' '; }  // for
        cout << endl;
    }  // for

    cout << solution << endl;

    return 0;
}  // function main
