#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef vector<int> Line;
typedef vector<Line> Face;
// typedef vector<Face> Cube;

static Face d;

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int V, G, N;
    cin >> V >> G >> N;

    int t[N], v[N], g[N];
    for (int i = 0; i < N; i++) { cin >> t[i] >> v[i] >> g[i]; }  // for

    d.resize(G + 1);
    for (int x = 0; x <= G; x++) { d[x].resize(V + 1); }  // for

    for (int i = 0; i < N; i++) {
        for (int j = G; j >= g[i]; j--) {
            for (int k = V; k >= v[i]; k--) {
                d[j][k] = std::max(d[j][k], d[j - g[i]][k - v[i]] + t[i]);
            }  // for
        }      // for
    }          // for

    int solution = d[G][V];

    cout << solution << endl;

    return 0;
}  // function main
