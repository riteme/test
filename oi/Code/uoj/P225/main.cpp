// #define NDEBUG
#pragma GCC optimize(3)

#include <bits/stdc++.h>

using namespace std;

#define NMAX 500

struct Point {
    int x, y;
};  // struct Point

static int n, m, k;
static bool ch[NMAX + 10][NMAX + 10];
static vector<Point> black;
static vector<Point> white;

static void construct1() {
    int offest = 0;
    for (int i = 1; i <= n; i += k - 1) {
        for (int j = 1; j <= m; j += 2) {
            int x = i;
            while (x <= n && x <= i + k - 2) {
                ch[x][j + offest] = true;
                x++;
            }
        }  // for
        offest = (offest + 1) % 2;
    }  // for
}

static void construct2() {
    int offest = 0;
    for (int j = 1; j <= m; j += k - 1) {
        for (int i = 1; i <= m; i += 2) {
            int y = j;
            while (y <= m && y <= j + k - 2) {
                ch[i + offest][y] = true;
                y++;
            }
        }  // for
        offest = (offest + 1) % 2;
    }  // for
}

static bool construct() {
    if (k < 2)
        return false;
    if (k == 2) {
        if (n > 1 && m > 1)
            return false;

        if (n == 1) {
            for (int i = 1; i <= m; i += 2)
                ch[1][i] = true;
        } else {
            for (int i = 1; i <= n; i += 2)
                ch[i][1] = true;
        }

        return true;
    }

    // k > 2
    if (n % 2 == 1) {
        construct1();
    } else {
        construct2();
    }

    return true;
}

int main() {
    scanf("%d%d%d", &n, &m, &k);

    // if (!construct()) {
    //     puts("-1");
    //     return 0;
    // }

    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= m; j++) {
    //         printf("%d ", ch[i][j]);
    //     }  // for
    //     putchar('\n');
    // }  // for

    construct1();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (ch[i][j])
                black.push_back({ i, j });
            else
                white.push_back({ i, j });
        }  // for
    }      // for

    printf("black = %d, white = %d\n", black.size(), white.size());
    // int i = 0, j = 0;
    // while (i < black.size() || j < white.size()) {
    //     if (i < black.size())
    //         printf("%d %d\n", black[i].x, black[i].y);
    //     if (j < white.size())
    //         printf("%d %d\n", white[j].x, white[j].y);

    //     i++;
    //     j++;
    // }

    black.clear();
    white.clear();
    memset(ch, 0, sizeof(ch));
    construct2();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (ch[i][j])
                black.push_back({ i, j });
            else
                white.push_back({ i, j });
        }  // for
    }      // for

    printf("black = %d, white = %d\n", black.size(), white.size());

    return 0;
}  // function main
