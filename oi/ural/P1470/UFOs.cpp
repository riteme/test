#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define NMAX 128

void initiailize();
void quit();

static int n;
static int m[NMAX + 1][NMAX + 1][NMAX + 1];

inline void insert(int x, int y, int z, int v) {
    for (int i = x; i <= n; i += (i & (-i))) {
        for (int j = y; j <= n; j += (j & (-j))) {
            for (int k = z; k <= n; k += (k & (-k))) {
                m[i][j][k] += v;
            }  // for
        }      // for
    }          // for
}

inline int query(int x, int y, int z) {
    int result = 0;

    for (int i = x; i > 0; i -= (i & (-i))) {
        for (int j = y; j > 0; j -= (j & (-j))) {
            for (int k = z; k > 0; k -= (k & (-k))) {
                result += m[i][j][k];
            }  // for
        }      // for
    }          // for

    return result;
}

int main() {
    initiailize();

    while (true) {
        int command;
        scanf("%d", &command);

        int x, y, z, k;
        int x1, y1, z1, x2, y2, z2;
        switch (command) {
            case 1: {
                scanf("%d %d %d %d", &x, &y, &z, &k);
                x++;
                y++;
                z++;

                insert(x, y, z, k);
                break;
            }
            case 2: {
                scanf("%d %d %d %d %d %d", &x1, &y1, &z1, &x2, &y2, &z2);
                x1++;
                y1++;
                z1++;
                x2++;
                y2++;
                z2++;

                int answer =
                    query(x2, y2, z2) - query(x1 - 1, y2, z2) -
                    query(x2, y1 - 1, z2) - query(x2, y2, z1 - 1) +
                    query(x1 - 1, y1 - 1, z2) + query(x1 - 1, y2, z1 - 1) +
                    query(x2, y1 - 1, z1 - 1) - query(x1 - 1, y1 - 1, z1 - 1);
                printf("%d\n", answer);
                break;
            }
            case 3: goto exit_point;
        }  // switch to command
    }      // while

exit_point:
    quit();
    return 0;
}  // function main

void initiailize() {
    scanf("%d", &n);

    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) {
            for (int z = 1; z <= n; z++) { m[x][y][z] = 0; }  // for
        }                                                     // for
    }                                                         // for
}

void quit() {}
