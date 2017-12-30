#include <cstdio>
#include <cstring>

int main() {
    int k;
    scanf("%d", &k);
    printf("%d\n", k + 1);
    for (int i = 0; i <= k; i++) {
        printf("%d ", i + 1);
    }
    return 0;
}
