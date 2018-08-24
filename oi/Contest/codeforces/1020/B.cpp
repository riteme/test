#include <cstdio>
#include <cstring>

#define NMAX 1000

static int n;
static bool marked[NMAX + 10];
static int ptr[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", ptr + i);
    for (int i = 1; i <= n; i++) {
        int x = i;
        memset(marked, 0, sizeof(marked));
        while (!marked[x]) {
            marked[x] = true;
            x = ptr[x];
        }
        printf("%d ", x);
    }
    return 0;
}
