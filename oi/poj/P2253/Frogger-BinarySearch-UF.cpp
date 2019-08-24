/**
 * Frogger
 * tags: 二分 并查集
 * time: O(n^3)
 */

#include <cmath>
#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

#define NMAX 200
#define SCENARIO "Scenario #%d"
#define DISTANCE "Frog Distance = %.3lf"

struct Point {
    double x;
    double y;
};  // struct Point

typedef set<double>::iterator iterator_t;

static int n;
static Point stone[NMAX + 10];
static set<double> edges;
static int edgeCount;
static double len[400000];
static double G[NMAX + 10][NMAX + 10];
static int data[NMAX + 10];

inline void make_set() {
    for (int i = 1; i <= n; i++) {
        data[i] = i;
    }  // for
}

inline int find_set(int x) {
    return x == data[x] ? x : data[x] = find_set(data[x]);
}

inline void union_set(int x, int y) {
    data[find_set(x)] = find_set(y);
}

inline double length(int a, int b) {
    return sqrt((stone[a].x - stone[b].x) * (stone[a].x - stone[b].x) +
                (stone[a].y - stone[b].y) * (stone[a].y - stone[b].y));
}

void initialize() {
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", &stone[i].x, &stone[i].y);
    }  // for

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            G[i][j] = G[j][i] = length(i, j);
            edges.insert(G[i][j]);
        }  // for
    }      // for

    edges.insert(0.0);
    for (int i = 1; i <= n; i++) {
        G[i][i] = 0.0;
    }  // for

    edgeCount = 1;
    for (iterator_t beg = edges.begin(); beg != edges.end(); beg++) {
        len[edgeCount++] = *beg;
    }  // for
}

// O(E) = O(n^2)
bool validate(double limit) {
    make_set();

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (G[i][j] <= limit) {
                union_set(i, j);
            }  // if  not exceeded limit
        }      // for j
    }          // for i

    return find_set(1) == find_set(2);
}

int main() {
    int id = 0;
    while (scanf("%d", &n) != EOF) {
        if (n == 0) {
            break;
        }

        id++;
        initialize();

        int left = 1;
        int right = edgeCount - 1;

        // O(logE) = O(n)
        while (right - left > 1) {
            int mid = (left + right) >> 1;

            if (validate(len[mid])) {
                right = mid;
            } else {
                left = mid;
            }
        }  // while

        if (left != right and !validate(len[left])) {
            left = right;
        }

        printf(SCENARIO "\n", id);
        printf(DISTANCE "\n\n", len[left]);
    }  // while

    return 0;
}  // function main
