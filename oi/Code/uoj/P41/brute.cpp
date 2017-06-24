#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

static int n, m, T;
static int mat[20][20];
static int tmp[20][20];
static int perm[20];
static bool marked[20];

bool check() {
    memcpy(tmp, mat, sizeof(tmp));

    for (int i = 1; i <= n; i++) {
        int j = 1;
        while (tmp[i][j] != perm[i])
            j++;
        for (; j <= m; j++)
            tmp[i][j] = perm[i];
    }

    for (int j = 1; j <= m; j++) {
        memset(marked, 0, sizeof(marked));
        
        for (int i = 1; i <= n; i++) {
            if (tmp[i][j] == 0)
                continue;
            
            if (marked[tmp[i][j]])
                return false;
            marked[tmp[i][j]] = true;
        }
    }

    return true;
}

int main() {
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d", &n, &m);

        for (int i = 1; i <= n; i++) {
            perm[i] = i;
            for (int j = 1; j <= m; j++) {
                scanf("%d", &mat[i][j]);
            }
        }

        bool ans = false;
        do {
            if (check()) {
                ans = true;
                break;
            }
        } while (next_permutation(perm + 1, perm + n + 1));

        if (ans) {
            for (int i = 1; i <= n; i++) {
                printf("%d ", perm[i]);
            }
            printf("\n");
        } else
            puts("fuck");
    }
}
