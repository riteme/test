#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

int c[1000000];

int main() {
    int n, t;
    scanf("%d%d", &n, &t);
    for (int i = 1; i <= n; i++) {
        scanf("%d", c + i);
    }

    int b1 = 0, bt = 0;
    int r1 = 0, rt = 0;
    for (int i = 1; i <= n; i++) {
        int r;
        scanf("%d", &r);
        if (c[i] == c[1] && r > r1) {
            b1 = i;
            r1 = r;
        }
        if (c[i] == t && r > rt) {
            bt = i;
            rt = r;
        }
    }

    printf("%d\n", bt ? bt : b1);
    return 0;
}
