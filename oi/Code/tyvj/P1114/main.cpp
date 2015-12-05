// 修建双塔

#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 100
#define MMAX 2000
#define IMPOSSIBLE "Impossible"
#define INVAILD_VALUE -1

static int n;
static int sum;
static int h[NMAX + 10];
static bool f[MMAX / 2 + 10];
static int r;

void initialize();
void output();
int dp(int m);

int main() {
    ios::sync_with_stdio(false);
    initialize();

    for (int i = sum / 2; r == INVAILD_VALUE and i >= 0; i -= 2) {
        if (dp(i) == i) r = i;
    }  // for

    output();
    return 0;
}  // function main

void initialize() {
    cin >> n;

    sum = 0;
    int x;
    generate_n(&h[1], n, [&x]() {
        cin >> x;
        sum += x;
        return x;
    });

    fill(begin(f), end(f), 0);
    r = INVAILD_VALUE;
}

int dp(int m) {
    if (m == 0) return 0;

    int dp[m + 10];
    fill(&dp[0], &dp[m + 1], 0);
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= h[j]; j--) {
            dp[j] = max(dp[j], dp[j - h[i]]);
        }  // for
    }      // for

    return dp[m];
}

void output() {
    if (r == INVAILD_VALUE)
        cout << IMPOSSIBLE;
    else
        cout << r;
}
