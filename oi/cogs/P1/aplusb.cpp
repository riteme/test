#include <cstdio>

int main() {
    freopen("aplusb.in", "r", stdin);
    freopen("aplusb.out", "w", stdout);

    float a, b;
    scanf("%f%f", &a, &b);
    printf("%d\n", int(a + b));

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
