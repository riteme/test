#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

char s[10000000], t[10000000];

int lcs() {
    int i = 0;
    for ( ; s[i] && t[i] && s[i] == t[i]; i++) {
    }
    return i;
}

int main() {
    int n;
    scanf("%d", &n);
    scanf("%s", s);
    int ans = INT_MAX;
    for (int i = 1; i < n; i++) {
        scanf("%s", t);
        ans = min(ans, lcs());
        memcpy(s, t, ans);
        s[ans] = 0;
    }
    t[ans] = 0;
    puts(t);
    return 0;
}
