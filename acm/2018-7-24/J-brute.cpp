#include <cstdio>

#include <algorithm>

using namespace std;

static int l, r, v;

bool test(int s) {
    for (int i = l; i <= r - s + 1; i++) {
        int sum = 0;
        for (int j = i; j <= i + s - 1; j++) sum |= j;
        if (sum <= v) return true;
    }
    return false;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &l, &r, &v);
        int s;
        for (s = r - l  + 1; !test(s); s--);
        printf("%d\n", s);
    }

    return 0;
}
