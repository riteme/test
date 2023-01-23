#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 200000;

int n;
char A[NMAX + 10], B[NMAX + 10];

int main() {
    scanf("%d%s%s", &n, A + 1, B + 1);
    int i = n, j = n;
    while (j >= 1) {
        while (j >= 1 && A[i] != B[j]) {
            j--;
        }
        if (j < 1)
            break;
        i--;
        j--;
    }
    sort(A + 1, A + n + 1);
    sort(B + 1, B + n + 1);
    if (strcmp(A + 1, B + 1) == 0)
        printf("%d\n", i);
    else
        puts("-1");
    return 0;
}
