#include <cstdio>
int main() {
    int c, d = 1;
    c = ++d,--d,d++,d--;
    printf("%d\n", c);
    return 0;
}
