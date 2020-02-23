#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 10000

int main() {
    char op[16], s[10000];
    int p;
    scanf("%s%d%s", op, &p, s);
    for (int i = 0; s[i]; i++) {
        if (op[0] == 'E')
            s[i] = ((s[i] - 'a' + p) % 26 + 26) % 26 + 'a';
        else
            s[i] = ((s[i] - 'a' - p) % 26 + 26) % 26 + 'a';
    }
    puts(s);
    return 0;
}
