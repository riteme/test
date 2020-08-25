#include <cstdio>
#include <cstring>

#include <map>
#include <algorithm>

using namespace std;

struct loc {
    loc() : x(0), y(0) {}
    loc(int _x, int _y) : x(_x), y(_y) {}

    int x, y;

    bool operator<(const loc &z) const {
        return x < z.x || (x == z.x && y < z.y);
    }
};

int w, h, n, q;
map<loc, int> ans;
map<int, int> row, col;


void _main() {
    scanf("%d%d%d", &w, &h, &n);
    ans.clear();
    for (int i = 0; i < n; i++) {
        int x, y, c;
        scanf("%d%d%d", &x, &y, &c);
        ans[loc(x, y)] = c;
    }

    scanf("%d", &q);
    row.clear();
    col.clear();
    for (int i = 0; i < q; i++) {
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1) {
            if (!row.count(x))
                row[x] = x;
            if (!row.count(y))
                row[y] = y;
            swap(row[x], row[y]);
        } else if (op == 2) {
            if (!col.count(x))
                col[x] = x;
            if (!col.count(y))
                col[y] = y;
            swap(col[x], col[y]);
        } else {
            if (!row.count(x))
                row[x] = x;
            if (!col.count(y))
                col[y] = y;
            x = row[x];
            y = col[y];
            printf("%d\n", ans[loc(x, y)]);
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        printf("Case #%d:\n", i);
        _main();
    }
    return 0;
}
