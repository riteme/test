#include <cstring>
#include <cstdio>

using namespace std;

typedef long long ntype;

int main() {
    int n;
    scanf("%d", &n);

    ntype d[n + 10];
    for (int i = 1; i <= n; i++) { scanf("%lld", d + i); }  // for

    ntype f[n + 10];
    memset(f, 0, sizeof(ntype) * (n + 10));

    ntype max = 0;
    f[1] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++)
            if (d[j] <= d[i] and f[i] < f[j]) f[i] = f[j];

        f[i]++;

        if (max < f[i]) max = f[i];
    }  // for

    printf("%lld", max);

    return 0;
}  // function main
