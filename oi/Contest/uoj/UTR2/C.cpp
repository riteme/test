#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 10

static int n;
static int seq[NMAX + 10];

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", seq + i);
    }

    sort(seq + 1, seq + n + 1, greater<int>());
}

static bool marked[NMAX + 10];
static int perm[NMAX + 10];
static int tmp[NMAX + 10];

static double middle(int len) {
    memcpy(tmp, perm, sizeof(tmp));
    sort(tmp + 1, tmp + len + 1);

    if (len & 1)
        return tmp[len / 2 + 1];
    else
        return (static_cast<double>(tmp[len / 2]) + 
                static_cast<double>(tmp[len / 2 + 1])) * 0.5;
}

static bool dfs(int pos, double last) {
    if (pos > n)
        return true;

    for (int i = 1; i <= n; i++) {
        if (!marked[i]) {
            perm[pos] = seq[i];

            double mid = middle(pos);
            if (mid >= last) {
                marked[i] = true;
                perm[pos] = seq[i];

                if (dfs(pos + 1, mid))
                    return true;

                marked[i] = false;
            }
        }
    }

    return false;
}

int main() {
    initialize();
    
    if (dfs(1, 0.0)) {
        for (int i = 1; i <= n; i++) {
            printf("%d ", perm[i]);
        }
    } else
        puts("QwQ");

    return 0;
}
