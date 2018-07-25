#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 10

static int n;
static int perm[NMAX + 10];
static bool L[NMAX + 10];

void print() {
    // for (int i = 1; i <= n; i++) {
    //     putchar(L[i] ? 'L' : 'R');
    // }
    // putchar('\n');

    for (int i = 1; i <= n; i++) {
        printf("%d ", perm[i]);
    }
    putchar('\n');
}

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        perm[i] = i;
        L[i] = true;
    }

    print();
    while (true) {
        int p = 0;
        for (int i = 1; i <= n; i++) {
            if ((L[i] && i > 1 && perm[i] > perm[i - 1]) ||
                (!L[i] && i < n && perm[i] > perm[i + 1]))
            if (perm[p] < perm[i])
                p = i;
        }

        if (!p)
            break;

        for (int i = 1; i <= n; i++) {
            if (perm[i] > perm[p])
                L[i] ^= 1;
        }

        if (L[p]) {
            swap(perm[p], perm[p - 1]);
            swap(L[p], L[p - 1]);
        } else {
            swap(perm[p], perm[p + 1]);
            swap(L[p], L[p + 1]);
        }

        print();
    }

    return 0;
}
