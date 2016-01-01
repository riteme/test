#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

static char os[1000010];
static char s[2000010];
static int f[2000010];
static int n;
static bool flag = true;

inline void read_string() {
    scanf("%s", os);

    if (strcmp(os, "END") == 0) {
        flag = false;
        return;
    }

    n = 1;
    int len = strlen(os);
    s[0] = '#';
    for (int i = 0; i < len; i++) {
        s[n++] = os[i];
        s[n++] = '#';
    }
    s[n] = '\0';

    // printf("%s\n",s);
    // printf("%d\n",n);
}

int solve() {
    int answer = 1;
    int id = 0;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        if (mx > i) { f[i] = min(f[id * 2 - i], mx - i); } else
            f[i] = 1;

        while (i - f[i] >= 0 and i + f[i] < n and s[i - f[i]] == s[i + f[i]]) {
            f[i]++;
        }

        if (i + f[i] > mx) {
            mx = i + f[i];
            id = i;
        }

        if (f[i] - 1 > answer) answer = f[i] - 1;
    }

    return answer;
}

int main() {
    int cnt = 1;

    while (true) {
        read_string();

        if (!flag) break;

        printf("Case %d: %d\n", cnt++, solve());
    }

    return 0;
}
