// ART OF FATUOUS CODING

#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000000

static char s[NMAX + 10];

bool v1[8];
bool v2[8][8];
bool v3[8][8][8];
bool v4[8][8][8][8];
bool v5[8][8][8][8][8];
bool v6[8][8][8][8][8][8];

static int t, n;
static char sp[128];

bool dfs(int p, int l) {
    if (!p) {
        switch (l) {
            case 1: return !v1[sp[0]];
            case 2: return !v2[sp[0]][sp[1]];
            case 3: return !v3[sp[0]][sp[1]][sp[2]];
            case 4: return !v4[sp[0]][sp[1]][sp[2]][sp[3]];
            case 5: return !v5[sp[0]][sp[1]][sp[2]][sp[3]][sp[4]];
            case 6: return !v6[sp[0]][sp[1]][sp[2]][sp[3]][sp[4]][sp[5]];
        }
        return false;
    }
    for (char c = 'A'; c <= 'H'; c++) {
        sp[t++] = c - 'A';
        if (dfs(p - 1, l))
            return true;
        t--;
    }
    return false;
}

void clear(int l) {
    switch (l) {
        case 1: memset(v1, 0, sizeof(v1)); break;
        case 2: memset(v2, 0, sizeof(v2)); break;
        case 3: memset(v3, 0, sizeof(v3)); break;
        case 4: memset(v4, 0, sizeof(v4)); break;
        case 5: memset(v5, 0, sizeof(v5)); break;
        case 6: memset(v6, 0, sizeof(v6)); break;
    }
}

void reg(char *p, int l) {
    switch (l) {
        case 1: v1[p[0]] = true; break;
        case 2: v2[p[0]][p[1]] = true; break;
        case 3: v3[p[0]][p[1]][p[2]] = true; break;
        case 4: v4[p[0]][p[1]][p[2]][p[3]] = true; break;
        case 5: v5[p[0]][p[1]][p[2]][p[3]][p[4]] = true; break;
        case 6: v6[p[0]][p[1]][p[2]][p[3]][p[4]][p[5]] = true; break;
    }
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%s", s + 1);
        n = strlen(s + 1);
        for (int i = 1; i <= n; i++)
            s[i] -= 'A';
        for (int l = 1; l <= 6; l++) {
            clear(l);
            for (int i = 1; i <= n; i++)
                if (i + l - 1 <= n) reg(s + i, l);
            t = 0;
            if (dfs(l, l)) {
                for (int i = 0; i < l; i++) sp[i] += 'A';
                sp[l] = 0;
                printf("%s\n", sp);
                break;
            }
        }
    }

    return 0;
}
