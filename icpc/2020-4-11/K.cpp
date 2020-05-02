#include <cstdio>

#include <algorithm>

using namespace std;

int main() {
    int a[4];
    scanf("%d%d%d%d", a+0, a+1, a+2, a+3);
    sort(a, a + 4);
    if (a[1] - a[0] == a[3] - a[2])
        puts("YES");
    else
        puts("NO");
    return 0;
}