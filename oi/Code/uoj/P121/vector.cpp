#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define DMAX 100

struct ModuleVector {
    int d;
    char mod;
    char dem[DMAX];
};

inline bool test_zero(const ModuleVector &a, const ModuleVector &b) {
    char sum = 0;

    if (a.mod == 2)
        for (int i = 0; i < a.d; i++)
            sum = (sum + a.dem[i] & b.dem[i]) & 1;
    else
        for (int i = 0; i < a.d; i++)
            sum = (sum + a.dem[i] * b.dem[i]) % a.mod;

    return sum == 0;
}

static int n, d, k;
static ModuleVector vec[NMAX + 10];

static void initialize() {
    scanf("%d%d%d", &n, &d, &k);

    for (int i = 1; i <= n; i++) {
        vec[i].d = d;
        vec[i].mod = k;

        for (int j = 0; j < d; j++) {
            int v;
            scanf("%d", &v);
            vec[i].dem[j] = v % k;
        }
    }
}

int main() {
    initialize();

    bool found = false;
    for (int i = 1; i <= n && !found; i++) {
        for (int j = i + 1; j <= n && !found; j++) {
            if (test_zero(vec[i], vec[j])) {
                printf("%d %d\n", i, j);
                found = true;
            }
        }
    }

    if (!found)
        puts("-1 -1");

    return 0;
}
