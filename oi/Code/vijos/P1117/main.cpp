#include <iostream>

using namespace std;

static int n, k;

int dfs(int p, int m, int d);

int dfs(int p, int m, int d) {
    if (d == 1) return 1;

    int cnt = 0;
    int l = m / d;
    for (int i = p; i <= l; i++) { cnt += dfs(i, m - i, d - 1); }  // for

    return cnt;
}

int main() {
    ios::sync_with_stdio(false);

    cin >> n >> k;
    cout << dfs(1, n, k);

    return 0;
}  // function main
