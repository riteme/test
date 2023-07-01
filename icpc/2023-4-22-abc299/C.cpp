#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

int n;
char s[1000000];

int main() {
    scanf("%d%s", &n, s);
    int mc = 0, ol = 0, maxol = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'o') {
            ol++;
            maxol = max(maxol, ol);
        }
        if (s[i] == '-') {
            mc++;
            ol = 0;
        }
    }
    if (mc == 0 || maxol == 0)
        puts("-1");
    else
        printf("%d\n", maxol);
    return 0;
}
