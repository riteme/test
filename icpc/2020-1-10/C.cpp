#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

bool query(int a, int b, int c) {
    printf("? %d %d %d\n", a, b, c);
    fflush(stdout);
    int ret;
    scanf("%d", &ret);
    return ret;
}

int main() {
    int n;
    scanf("%d", &n);
    int x = 2;
    for (int v = 3; v <= n; v++) {
        if (query(1, x, v))
            x = v;
    }
    printf("! %d\n", x);
    fflush(stdout);

    return 0;
}