#include <cstdio>

char s[1000];

char scan() {
    scanf("%s", s);
    char c = 0;
    for (int i = 0; s[i]; i++) {
        if (s[i] == '=')
            c = '=';
        else if (c == '=' && s[i] != '.')
            return s[i];
    }
    return 0;
}

int main() {
    char c;
    c = scan();
    if (c) return putchar(c), 0;
    c = scan();
    if (c) return putchar(c), 0;
    c = scan();
    if (c) return putchar(c), 0;
    puts("You shall pass!!!");
    return 0;
}