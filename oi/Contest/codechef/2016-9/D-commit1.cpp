#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000

static int n, m;
static bool G[NMAX + 10][NMAX + 10];
static bool marked[NMAX + 10];
static int degree[NMAX + 10];
static vector<int> A, B;

enum ConnectionType {
    ALL,
    PAR,
    NONE,
};  // enum ConnectionType

static ConnectionType detect_connection(int x, const vector<int> &s) {
    int connected = 0;

    for (int i = 0; i < s.size(); i++)
        if (G[s[i]][x])
            connected++;

    if (connected == s.size())
        return ALL;
    if (connected == 0)
        return NONE;
    else
        return PAR;
}

static void initialize() {
    A.clear();
    B.clear();
    memset(marked, 0, sizeof(marked));
    memset(G, 0, sizeof(G));
    memset(degree, 0, sizeof(degree));

    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        G[a][b] = G[b][a] = true;
    }  // for

    for (int i = 1; i <= n; i++) {
        G[i][i] = true;
    }  // for
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();

        A.push_back(1);
        for (int i = 2; i <= n; i++) {
            if (!G[1][i]) {
                B.push_back(i);
                marked[i] = true;
            }
        }  // for

        bool flag = false;
        if (n < 2)
            flag = true;

        for (int i = 0; i < B.size() && !flag; i++) {
            if (detect_connection(B[i], B) != ALL)
                flag = true;
        }  // for

        for (int i = 2; i <= n; i++) {
            if (marked[i])
                continue;

            for (int j = 1; j <= n; j++) {
                if (marked[j])
                    continue;

                if (G[i][j])
                    degree[i]++;
            }  // for
        }      // for

        marked[1] = true;
        while (!flag) {
            int pivot = 0;
            for (int i = 1; i <= n; i++) {
                if (marked[i])
                    continue;

                if (degree[i] > degree[pivot])
                    pivot = i;
            }  // for

            if (pivot == 0)
                break;

            ConnectionType ac = detect_connection(pivot, A);
            ConnectionType bc = detect_connection(pivot, B);
            if (ac == ALL)
                A.push_back(pivot);
            else if (bc == ALL) {
                B.push_back(pivot);

                for (int i = 1; i <= n; i++)
                    if (G[i][pivot])
                        degree[i]--;
            } else
                flag = true;

            marked[pivot] = true;
        }  // while

        if (flag)
            puts("NO");
        else
            puts("YES");

        // for (int i = 0; i < A.size(); i++) {
        //     printf("%d ", A[i]);
        // }  // for
        // printf("\n");

        // for (int i = 0; i < B.size(); i++) {
        //     printf("%d ", B[i]);
        // }  // for
        // printf("\n");
    }  // while

    return 0;
}  // function main
