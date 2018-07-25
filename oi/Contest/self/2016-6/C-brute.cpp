#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n;

struct Point {
    int x, y, z, t;
    int answer;
};  // struct Point

static Point points[NMAX + 10];
static Point *sorted[NMAX + 10];

static bool cmp(const Point *a, const Point *b) {
    return a->t < b->t;
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &points[i].x, &points[i].y, &points[i].z,
              &points[i].t);
        sorted[i] = &points[i];
    }  // for

    sort(sorted + 1, sorted + n + 1, cmp);
}

int main() {
    initialize();

    int i = 1, j = 1;
    while (i <= n) {
        while (j <= n && j + 1 <= n && sorted[j]->t == sorted[j + 1]->t) {
            j++;
        }  // while

        for (int k = i; k <= j; k++) {
            for (int x = 1; x <= j; x++) {
                if (sorted[x]->x <= sorted[k]->x &&
                    sorted[x]->y <= sorted[k]->y &&
                    sorted[x]->z <= sorted[k]->z) {
                    sorted[k]->answer++;
                }
            }  // for

            sorted[k]->answer--;
        }  // for

        i = j = j + 1;
    }  // while

    for (int pos = 1; pos <= n; pos++) {
        printf("%d\n", points[pos].answer);
    }  // for

    return 0;
}  // function main
