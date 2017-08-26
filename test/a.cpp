#include <cstring>
#include <cstdio>

int main() {
    int n, ans = -1;
    char str[100];
    scanf("%s", str + 1);
    n = strlen(str + 1);
    for (int i = 1; i <= n; i++)
        str[i] -= '0';
    for (int i = 1; i < n; i++) {
        if ((str[i] ^ str[i - 1]) && (str[i] ^ str[i + 1]))
            str[i] ^= 1, ans += 2;
    }
    if (str[n] && !str[n - 1]) {
        ans += 2, str[n] = 0;
    }
    for (int i = 1; i <= n; i++)
        if (str[i] != str[i - 1]) {
            ans += 2;
        }
    ans += str[n] ? 2 : 0;
    printf("%d\n", ans);
    return 0;
}
