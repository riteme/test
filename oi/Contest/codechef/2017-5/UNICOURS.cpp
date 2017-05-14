#include <cstdio>

#include <algorithm>

using namespace std;

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n;
        scanf("%d", &n);

        int maxa = 0;
        for (int i = 1; i <= n; i++) {
            int v;
            scanf("%d", &v);
            maxa = max(maxa, v);
        }  // for

        printf("%d\n", n - maxa);
    }  // while

    return 0;
}  // function main
