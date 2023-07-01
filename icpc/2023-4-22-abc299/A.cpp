#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

int n;
char s[1000];

int main() {
    scanf("%d%s", &n, s);
    int l = -1, m, r;
    for (int i = 0; s[i]; i++) {
        if (s[i] == '|') {
            if (l < 0)
                l = i;
            else
                r = i;
        }
        if (s[i] == '*')
            m = i;
    }
    if (l < m && m < r)
        puts("in");
    else
        puts("out");
    return 0;
}
