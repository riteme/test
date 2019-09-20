#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        int cnt = (a > 0) + (b > 0) + (c > 0) + (d > 0);
        if (cnt == 0) puts("Typically Otaku");
        if (cnt == 1) puts("Eye-opener");
        if (cnt == 2) puts("Young Traveller");
        if (cnt == 3) puts("Excellent Traveller");
        if (cnt == 4) puts("Contemporary Xu Xiake");
    }
    return 0;
}
