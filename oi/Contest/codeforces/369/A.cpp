#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 2000

static int n;
static bool flag;
static char m[NMAX + 10][100];

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%s", &m[i][1]);
    }  // for

    for (int i = 1; i <= n; i++) {
        if (m[i][1] == 'O' && m[i][2] == 'O') {
            m[i][1] = '+';
            m[i][2] = '+';
            flag = true;
            break;
        }

        if (m[i][4] == 'O' && m[i][5] == 'O') {
            m[i][4] = '+';
            m[i][5] = '+';
            flag = true;
            break;
        }
    }  // for

    if (flag) {
        puts("YES");
        for (int i = 1; i <= n; i++) {
            printf("%s\n", &m[i][1]);
        }  // for
    } else {
        puts("NO");
    }

    return 0;
}  // function main
