#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

char s[64][64];

int main() {
    for (int i = 1; i <= 10; i++) {
        scanf("%s", s[i] + 1);
    }
    int a = 100, b = 0, c = 100, d = 0;
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            if (s[i][j] == '#') {
                a = min(a, i);
                b = max(b, i);
                c = min(c, j);
                d = max(d, j);
            }
        }
    }
    printf("%d %d\n%d %d\n", a, b, c, d);
    return 0;
}
