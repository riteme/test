#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef vector<int> Line;
typedef vector<Line> Face;
typedef vector<Face> Cube;

static Cube d;

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int V, G, N;
    cin >> V >> G >> N;

    int t[N], v[N], g[N];
    for (int i = 0; i < N; i++) { cin >> t[i] >> v[i] >> g[i]; }  // for

    d.resize(N);
    for (int x = 0; x < N; x++) {
        d[x].resize(G + 1);
        for (int y = 0; y <= G; y++) { d[x][y].resize(V + 1); }  // for
    }                                                            // for

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= G; j++) {
            for (int k = 0; k <= V; k++) {
                if (i == 0) {
                    d[i][j][k] = g[i] <= j and v[i] <= k ? t[i] : 0;
                } else {
                    d[i][j][k] =
                        g[i] <= j and v[i] <= k
                            ? std::max(d[i - 1][j][k],
                                       d[i - 1][j - g[i]][k - v[i]] + t[i])
                            : d[i - 1][j][k];
                }
            }  // for
        }      // for
    }          // for

    int solution = d[N - 1][G][V];

    cout << solution << endl;

    return 0;
}  // function main
