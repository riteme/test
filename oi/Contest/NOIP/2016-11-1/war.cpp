#include <cstdio>

#include <algorithm>

using namespace std;

#define NMAX 2000

typedef long long int64;

static int n, m;
static int64 linecost[NMAX + 10];
static int64 colcost[NMAX + 10];
static int64 linemax[NMAX + 10][NMAX + 10];
static int64 colmax[NMAX + 10][NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i < n; i++)
        scanf("%lld", linecost + i);
    for (int i = 1; i < m; i++)
        scanf("%lld", colcost + i);

    for (int i = 1; i < n; i++) {
        linemax[i][i] = i;
        for (int j = i + 1; j < n; j++) {
            if (linecost[j] > linecost[linemax[i][j - 1]])
                linemax[i][j] = j;
            else
                linemax[i][j] = linemax[i][j - 1];
        }
    }

    for (int i = 1; i < m; i++) {
        colmax[i][i] = i;
        for (int j = i + 1; j < m; j++) {
            if (colcost[j] > colcost[colmax[i][j - 1]])
                colmax[i][j] = j;
            else
                colmax[i][j] = colmax[i][j - 1];
        }
    }
}

static int64 solve(int left, int right, int top, int bottom) {
    if (left == right && top == bottom)
        return 0;

    int pos, type;
    if (linecost[linemax[left][right - 1]] > colcost[colmax[top][bottom - 1]]) {
        pos = linemax[left][right - 1];
        type = 1;
    } else {
        pos = colmax[top][bottom - 1];
        type = 2;
    }

    if (type == 1)
        return linecost[pos] + solve(left, pos, top, bottom) + solve(pos + 1, right, top, bottom);
    else 
        return colcost[pos] + solve(left, right, top, pos) + solve(left, right, pos + 1, bottom);
}

int main() {
    freopen("war.in", "r", stdin);
    freopen("war.out", "w", stdout);
    initialize();

    printf("%lld\n", solve(1, n, 1, m));

    fclose(stdin);
    fclose(stdout);
    return 0;
}
