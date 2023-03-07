#include <cstdio>

int main() {
    char s[200];
    scanf("%s", s + 1);
    for (int i = 1; s[i]; i++) {
        if ('A' <= s[i] && s[i] <= 'Z')
            printf("%d\n", i);
    }
    return 0;
}
