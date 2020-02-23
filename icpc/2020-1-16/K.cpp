#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100

int main() {
    int n;
    scanf("%d", &n);

    printf("%d\n", 3 * n * n / 4);
    for (int i = 1; 2 * i <= n; i++) {
        int j = 2 * i - 1;
        for (int k = 1; k <= n; k += 2) {
            printf("1 %d %d 2\n", j + 1, k);
            printf("1 %d %d 2\n", j, k + 1);
            printf("2 %d %d 1\n", j, k);
        }
    }

    return 0;
}