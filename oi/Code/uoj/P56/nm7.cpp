#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

#define N 20

typedef long long int64;

static int G[30][30];
static int pos[30];
static int maxd;
static bool marked[30];

bool val() {
    FILE *io = fopen("/tmp/nm7.dat", "r");
    int64 a, b, c, d;
    fscanf(io, "%lld%lld%lld%lld", &a, &b, &c, &d);
    fclose(io);
    return d == 2432898351216220492L;
}

void check() {
    // for (int d = 1; d <= maxd; d++) {
    //     for (int i = 1; i <= pos[d]; i++) {
    //         printf("%d ", G[d][i]);
    //     }  // for
    //     printf("\n");
    // }  // for
    // printf("=====\n");

    FILE *io = fopen("/tmp/nm7.out", "w");
    fputs("20 20 22\n", io);
    for (int d = 1; d <= maxd; d++) {
        for (int i = 2; i <= pos[d]; i++) {
            fprintf(io, "%d %d 0\n", G[d][i - 1], G[d][i]);
        }  // for
        fprintf(io, "%d %d 0\n", G[d][pos[d]], G[d][1]);
    }  // for
    fclose(io);
    system("./prog.out /tmp/nm7.out > /tmp/nm7.dat");

    if (val()) {
        puts("OK!");
        exit(0);
    }
}

void dfs(int x, int depth, int cnt, bool first) {
    if (cnt == N) {
        maxd = depth;
        check();
    } else if (x > N) {
        pos[depth + 1] = 0;
        dfs(1, depth + 1, cnt, true);
    } else {
        if (!marked[x]) {
            marked[x] = true;
            G[depth][++pos[depth]] = x;
            dfs(x + 1, depth, cnt + 1, false);
            pos[depth]--;
            marked[x] = false;
        }

        if (marked[x] || !first)
            dfs(x + 1, depth, cnt, first);
    }
}

int main() {
    dfs(1, 1, 0, true);

    return 0;
}  // function main
