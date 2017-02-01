#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

#define NMAX 100000
#define KMAX 200

#define LAST(stk) stk[stk.size() - 1]
#define SECOND(stk) stk[stk.size() - 2]

typedef long long int64;

struct Vector {
    Vector() : index(0), x(0.0L), y(0.0L) {}
    Vector(const int id, const int64 &_x, const int64 &_y)
        : index(id), x(_x), y(_y) {}

    int index;
    int64 x, y;

    Vector operator-(const Vector &b) const {
        return Vector(0, x - b.x, y - b.y);
    }
};  // struct Vector

inline int64 cross(const Vector &a, const Vector &b) {
    return a.x * b.y - a.y * b.x;
}

static int n, K;
static int64 seq[NMAX + 10];
static int64 pre[NMAX + 10];
static int64 f[NMAX + 10][KMAX + 10];
static int maxp[NMAX + 10][KMAX + 10];
static int op[KMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &K);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", seq + i);
        pre[i] = pre[i - 1] + seq[i];
    }  // for
}

int main() {
    initialize();

    vector<Vector> stk;
    stk.reserve(n);
    for (int k = 1; k <= K; k++) {
        // Build convex hull
        stk.clear();
        for (int i = 1; i <= n; i++) {
            // if (seq[i] == 0)
            //     continue;

            Vector u(i, pre[i], f[i][k - 1] - pre[i] * pre[i]);

            while (stk.size() >= 2 &&
                   cross(u - LAST(stk), u - SECOND(stk)) < 0) {
                stk.pop_back();
            }  // while

            stk.push_back(u);
        }  // for

        int j = 0;
        for (int i = k + 1; i <= n; i++) {
            while (stk[j + 1].index < i &&
                   stk[j + 1].y - stk[j].y >
                       -pre[i] * (stk[j + 1].x - stk[j].x)) {
                j++;
            }  // while

            int &p = stk[j].index;

            while (p + 1 < i && seq[p + 1] == 0) {
                p++;
            }  // while

            maxp[i][k] = p;
            f[i][k] = f[p][k - 1] + pre[p] * (pre[i] - pre[p]);
        }  // for
    }      // for

    printf("%lld\n", f[n][K]);

    int x = n;
    for (int i = K; i >= 1; i--) {
        op[i] = maxp[x][i];
        x = op[i];
    }  // for

    for (int i = 1; i <= K; i++) {
        printf("%d ", op[i]);
    }  // for
    printf("\n");

    return 0;
}  // function main
