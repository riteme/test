#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 2000

typedef long long ntype;

static ntype a[NMAX + 10][NMAX + 10];

static void modify(int x1, int x2, int y1, int y2, ntype delta) {
    for (int x = x1; x <= x2; x++) {
        for (int y = y1; y <= y2; y++) {
            a[x][y] += delta;
        }  // for
    }      // for
}

static ntype query(int x1, int x2, int y1, int y2) {
    ntype answer = 0;

    for (int x = x1; x <= x2; x++) {
        for (int y = y1; y <= y2; y++) {
            answer += a[x][y];
        }  // for
    }      // for

    return answer;
}

int main() {
    int _;
    scanf("%d%d", &_, &_);

    int command;
    while (true) {
        scanf("%d", &command);

        if (command == 3)
            break;

        if (command == 1) {
            int x1, y1, x2, y2;
            ntype v;
            scanf("%d%d%d%d%lld", &x1, &y1, &x2, &y2, &v);

            modify(x1, x2, y1, y2, v);
        } else {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

            printf("%lld\n", query(x1, x2, y1, y2));
        }
    }  // while

    return 0;
}  // function main
