#include <iostream>
#include <algorithm>

using namespace std;

#define TMAX 1000
#define MMAX 100

static int t, m;
static int w[MMAX + 10];
static int c[MMAX + 10];
static int f[TMAX + 10];

void initialize();
void output();

int main() {
    ios::sync_with_stdio(false);
    initialize();

    for (int i = 1; i <= m; i++) {
        for (int j = t; j >= c[i]; j--) {
            f[j] = max(f[j], f[j - c[i]] + w[i]);
        }  // for
    }      // for

    output();
    return 0;
}  // function main

void initialize() {
    cin >> t >> m;

    for (int i = 1; i <= m; i++) { cin >> c[i] >> w[i]; }  // for

    fill(&f[0], &f[t + 1], 0);
}

void output() { cout << f[t]; }
