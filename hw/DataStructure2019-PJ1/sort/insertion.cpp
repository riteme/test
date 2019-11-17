#include "protocol.h"

#include <cstring>

#include <algorithm>

using namespace std;

int insert(Pack *s, int &n, Pack u, int L = 0, int R = 0) {
    int l = L ? L : 1, r = R ? R : n + 1;
    while (l < r) {
        int mi = (l + r) / 2;
        if (s[mi] < u) l = mi + 1;
        else r = mi;
    }
    if (l <= n)
        memmove(s + l + 1, s + l, sizeof(Pack) * (n - l + 1));
    s[l] = u;
    n++;
    return l;
}

void bubble(Pack *s, int n) {
    for (int i = 2; i <= n; i++)
    if (s[i] < s[i - 1]) swap(s[i], s[i - 1]);
}

void insertion_sort(Pack *s, int n) {
    bubble(s, n);
    int lp = 0, n0 = 0;
    for (int i = 1; i <= n; i++) {
        int L = 1, R = n0 + 1;
        if (lp) {
            if (s[lp] < s[i]) L = max(L, lp + 1);
            else R = min(R, lp);
        }
        lp = insert(s, n0, s[i], L, R);
    }
}

extern int n;
extern Pack s[500];

void sort() {
    insertion_sort(s, n);
}
