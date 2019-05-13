#include <cstdio>
static int arr[2][100];
static auto p = arr[1];
int main() {
    for (int i = -50; i <= 50; i++) p[i] = i;
    int x = p[-25] + p[26];
    printf("%d\n", x);
    return 0;
}
