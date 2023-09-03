#include <cstdio>
#include <cassert>
#include <cstring>

#include <bitset>
#include <algorithm>

using namespace std;

constexpr int NMAX = 1024;

using bits = bitset<NMAX>;

int n, K;
bits row[NMAX];
bool val[NMAX];

int main() {
    scanf("%d%d", &n, &K);
    for (int i = 0; i <= K; i++) {
        for (int j = 0; j < K; j++) {
            int p = (i + j) % (K + 1);
            row[i][p] = 1;
        }
    }
    for (int i = K + 1; i < n; i++) {
        row[i][i] = 1;
        for (int j = 0; j < K - 1; j++) {
            row[i][j] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        printf("?");
        for (int j = 0; j < n; j++) {
            if (row[i][j])
                printf(" %d", j + 1);
        }
        puts("");
        fflush(stdout);
        int v;
        scanf("%d", &v);
        val[i] = v;
    }

    for (int i = 0; i < n; i++) {
        if (!row[i][i]) {
            for (int j = i + 1; j < n; j++) {
                if (row[j][i]) {
                    swap(row[i], row[j]);
                    swap(val[i], val[j]);
                    break;
                }
            }
        }

        // printf("i=%d\n", i);
        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < n; j++) {
        //         printf("%d", (int)row[i][j]);
        //     }
        //     puts("");
        // }
        assert(row[i][i]);

        for (int j = i + 1; j < n; j++) {
            if (row[j][i]) {
                row[j] ^= row[i];
                val[j] ^= val[i];
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            if (row[j][i]) {
                row[j] ^= row[i];
                val[j] ^= val[i];
            }
        }
    }

    printf("!");
    for (int i = 0; i < n; i++) {
        printf(" %d", val[i]);
    }
    puts("");

    return 0;
}
