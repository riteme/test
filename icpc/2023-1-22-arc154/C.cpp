#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 5000;

int n;
int A[NMAX], B[NMAX];

bool greedy(int s) {
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j < n && B[(s + i) % n] != A[j]) {
            j++;
        }
        if (j >= n)
            return false;
    }
    return true;
}

bool solve() {
    if (equal(A, A + n, B))
        return true;

    bool any = false;
    for (int i = 0; i < n; i++) {
        if (B[i] == B[(i + 1) % n])
            any = true;
    }
    if (!any)
        return false;

    for (int i = 0; i < n; i++) {
        if (greedy(i))
            return true;
    }

    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", A + i);
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", B + i);
        }
        puts(solve() ? "Yes" : "No");
    }
    return 0;
}
