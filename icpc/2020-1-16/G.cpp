#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200000

int n, m;
char s[NMAX + 10], t[NMAX + 10];
struct record {
    int i, j;
} rec[NMAX + 10];

void swap(int i, int j) {
    swap(s[i], t[j]);
    rec[m++] = {i, j};
}

int main() {
    scanf("%d%s%s", &n, s + 1, t + 1);

    int j = 0, k = 0;
    for (int i = 1; i <= n; i++) if (s[i] != t[i]) {
        if (s[i] == 'a' && j) {
            swap(j, i);
            j = 0;
        } else if (s[i] == 'b' && k) {
            swap(k, i);
            k = 0;
        } else if (s[i] == 'a' && !j)
            j = i;
        else if (s[i] == 'b' && !k)
            k = i;
    }
    if (j && k) {
        swap(j, j);
        swap(j, k);
        j = k = 0;
    }

    if (j || k) puts("-1");
    else {
        printf("%d\n", m);
        for (int i = 0; i < m; i++)
            printf("%d %d\n", rec[i].i,rec[i].j);
    }
    return 0;
}