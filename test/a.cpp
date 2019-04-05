#include <cstdio>
int main() {
    char buf[] ="1 2";
    int a, b;
    sscanf_s(buf, "%d%d", &a, &b);
    printf("%d\n", a + b);
    return 0;
}
