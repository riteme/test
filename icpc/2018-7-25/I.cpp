#include <cstdio>
#include <algorithm>
using namespace std;
#define FIRST "Yalalov"
#define LAST "Shin"
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, s = 0, m = 1e9, x;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &x);
            s += x;
            m = min(m, x);
        }

        if (n & 1)
            puts(s & 1 ? FIRST : LAST);
        else
            puts(!(s & 1) && !(m & 1) ? LAST : FIRST);
    }
    return 0;
}
