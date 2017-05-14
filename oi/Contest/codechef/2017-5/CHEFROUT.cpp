#include <cstdio>

#define NMAX 100000

static char str[NMAX + 10];

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%s", str);

        char last = 'A';
        bool ans = true;
        for (size_t i = 0; str[i]; i++) {
            if (str[i] < last)
                ans = false;
            last = str[i];
        }  // for

        puts(ans ? "yes" : "no");
    }  // while

    return 0;
}  // function main
