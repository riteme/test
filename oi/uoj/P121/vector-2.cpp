#include <cstdio>
#include <cstring>

#include <bitset>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define DMAX 100

typedef bitset<DMAX> Vector;

static int n, d, k;
static Vector vec[NMAX + 10];

static void initialize() {
    scanf("%d%d%d", &n, &d, &k);

    if (k == 3)
        return;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < d; j++) {
            int v;
            scanf("%d", &v);
            vec[i][j] = (v & 1);
        }
    }
}

int main() {
    initialize();

    if (k == 3)
        puts("No, you can't!");
    else {
        bool found = false;
        for (int i = 1; i <= n && !found; i++) {
            for (int j = i + 1; j <= n && !found; j++) {
                if (((vec[i] & vec[j]).count() & 1) == 0) {
                    printf("%d %d\n", i, j);
                    found = true;
                }
            }
        }

        if (!found)
            puts("-1 -1");
    }

    return 0;
}
