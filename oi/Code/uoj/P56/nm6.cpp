#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

#define N 8

static int G[10][10];
static int pos[10];
static int maxd;
static bool marked[10];

bool val() {
    FILE *io = fopen("nm6.dat", "r");
    int a, b, c, d;
    fscanf(io, "%d%d%d%d", &a, &b, &c, &d);
    fclose(io);
    return d == 232615585;
}

void check() {
    // for (int d = 1; d <= maxd; d++) {
    //     for (int i = 1; i <= pos[d]; i++) {
    //         printf("%d ", G[d][i]);
    //     }  // for
    //     printf("\n");
    // }  // for
    // printf("=====\n");

    FILE *io = fopen("nm6.out", "w");
    fputs("8 8 21\n", io);
    for (int d = 1; d <= maxd; d++) {
        for (int i = 2; i <= pos[d]; i++) {
            fprintf(io, "%d %d 0\n", G[d][i - 1], G[d][i]);
        }  // for
        fprintf(io, "%d %d 0\n", G[d][pos[d]], G[d][1]);
    }  // for
    fclose(io);
    system("./prog.out nm6.out > nm6.dat");

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
