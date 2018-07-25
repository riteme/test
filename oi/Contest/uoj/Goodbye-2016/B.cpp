#include <cmath>
#include <cstdio>

#include <algorithm>

using namespace std;

int gen(int n, int k) {
    static int id = 0;
    if (n < 1)
        return 0;

    int u = ++id;
    n--;
    int normal = n / k;
    int last = n - normal * (k - 1);
    for (int i = 0; i < k - 1; i++) {
        int v = gen(normal, k);

        if (v)
            printf("%d %d\n", u, v);
    }  // for

    int v = gen(last, k);
    if (v)
        printf("%d %d\n", u, v);

    return u;
}

int main() {
    int n;
    scanf("%d", &n);

    if (n <= 3)
        gen(n, n);
    else
        gen(n, 3);

    return 0;
}  // function main
