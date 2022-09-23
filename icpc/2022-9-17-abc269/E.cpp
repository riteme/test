#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

int query(int xmin, int xmax, int ymin, int ymax) {
    printf("? %d %d %d %d\n", xmin, xmax, ymin, ymax);
    fflush(stdout);
    int v;
    scanf("%d", &v);
    return v;
}

int main() {
    int n;
    scanf("%d", &n);
    int l = 1, r = n;
    while (l < r) {
        int m = (l + r) / 2;
        if (query(l, m, 1, n) < (m - l + 1))
            r = m;
        else
            l = m + 1;
    }
    int x = l;
    l = 1;
    r = n;
    while (l < r) {
        int m = (l + r) / 2;
        if (query(1, n, l, m) < (m - l + 1))
            r = m;
        else
            l = m + 1;
    }
    printf("! %d %d\n", x, l);
    return 0;
}
