#include <climits>
#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 100
#define BMAX 22500
#define INVAILD false

static int n;
static int s;
static int b;
static int w[NMAX + 10];
static bool f[BMAX + 10];

void initialize();
void output();

int main() {
    ios::sync_with_stdio(false);
    initialize();

    for (int i = 1; i <= n; i++) {
        for (int j = b; j >= w[i]; j--) { f[j] = f[j - w[i]]; }  // for
    }                                                            // for

    output();
    return 0;
}  // function main

void initialize() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        s += w[i];
    }  // for
    b = s / 2;

    fill(&f[0], &f[b + 1], INVAILD);
    f[0] = true;
}

void output() {
    for (int i = b; i; /* process */) { /* your code */ }  // for
}
