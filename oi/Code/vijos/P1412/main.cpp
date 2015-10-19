#include <iostream>
#include <algorithm>

using namespace std;

#define KMAX 50
#define VMAX 5000
#define NMAX 200

static int d[VMAX + 1][KMAX + 1];

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int K, V, N;
    cin >> K >> V >> N;

    int v[N], w[N];
    for (int i = 0; i < N; i++) { cin >> v[i] >> w[i]; }  // for

    for (int i = 0; i < N; i++) {
        for (int j = V; j >= v[i]; j--) {
            for (int k = K; k >= 0; k--) {
                d[j][k] = std::max(d[j][k], d[j - v[i]][k] + w[i]);
            }  // for
        }      // for
    }          // for

    cout << d[V][K] << endl;

    return 0;
}  // function main
