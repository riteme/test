#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

struct Vector2 {
    Vector2() : x(0), y(0) {}
    Vector2(int _x, int _y) : x(_x), y(_y) {}

    int x, y;
};

inline Vector2 subtract(const Vector2 &a, const Vector2 &b) {
    return Vector2(a.x - b.x, a.y - b.y);
}

inline int square(const Vector2 &a) {
    return abs(a.x * a.x + a.y * a.y);
}

#define NMAX 50000

static int n;
static Vector2 p[NMAX + 10];

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &p[i].x, &p[i].y);
    }
}

int main() {
    initialize();

    int maxdist = 0;
    int x, y;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            Vector2 &a = p[i];
            Vector2 &b = p[j];

            int dist = square(subtract(a, b));
            if (dist > maxdist) {
                maxdist = dist;
                x = i;
                y = j;
            }
        }
    }

    printf("%d\n", maxdist);
    // printf("(%d, %d) - (%d, %d)\n", p[x].x, p[x].y, p[y].x, p[y].y);

    return 0;
}
