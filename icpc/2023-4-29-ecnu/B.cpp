#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 1000000;
constexpr int MOD = 1000000007;

int n;
char s[NMAX + 10];
int f[NMAX + 10][2];

void add(int &a, int b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}

const char *t[] = {
    "0110", "111", "10", "0001", "0101", "001", "0", "0100", "011",  "0000", "00",   "1110", "101",
    "0010", "11",  "01", "1011", "010",  "000", "1", "100",  "1000", "110",  "1001", "1101", "0011",
};

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 26; k++) {
                if (j == 0 && k == 1)
                    continue;
                if (j == 1 && k != 1)
                    continue;
                int p = 0;
                while (t[k][p] && i - p > 0 && t[k][p] == s[i - p]) {
                    p++;
                }
                if (t[k][p] == 0) {
                    add(f[i][j], f[i - p][0]);
                    if (k != 0)
                        add(f[i][j], f[i - p][1]);
                }
            }
        }
    }
    int ans = 0;
    add(ans, f[n][0]);
    add(ans, f[n][1]);
    printf("%d\n", ans);
    return 0;
}
