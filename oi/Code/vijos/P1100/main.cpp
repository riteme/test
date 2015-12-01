/**
 * 树形动态规划
 * g(i, x, j): f(i, x - i) * f(x + 1, j - x)
 *
 * 状态：
 * f(i, j): 第i号到第i + j - 1号节点组成的最大加分树的值
 * f(i, i): w(i)
 * f(i, j): max{g(1) + w(1), g(2) + w(2), ..., g(i + j - 1) + w(i + j - 1)}
 */

#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define NDEBUG

#define NMAX 30

typedef unsigned ntype;

static int n;
static ntype w[NMAX + 10];
static ntype f[NMAX + 10][NMAX + 10];
static int tree[NMAX + 10][NMAX + 10];

void initialize();
void output();
void print_tree(int i, int j);
void _print_f();

inline ntype g(int s, int x, int j) {
    return f[s][x - s] * f[x + 1][j - x + s - 1];
}

int main() {
    ios::sync_with_stdio(false);
    initialize();

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= n - i + 1; j++) {
            for (int k = j; k <= j + i - 1; k++) {
                ntype m = g(j, k, i) + w[k];

                if (f[j][i] < m) {
                    f[j][i] = m;
                    tree[j][i] = k;
                }
            }  // for
        }      // for
    }          // for

    output();
    return 0;
}  // function main

void initialize() {
    for (int x = 0; x < NMAX + 10; x++)
        for (int y = 0; y < NMAX + 10; y++) f[x][y] = 1;

    for (int x = 0; x < NMAX + 10; x++)
        for (int y = 0; y < NMAX + 10; y++) tree[x][y] = 0;

    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        f[i][1] = w[i];
        tree[i][1] = i;
    }
}

void output() {
    cout << f[1][n] << '\n';

    print_tree(1, n);
    cout << '\n';

    _print_f();
}

void print_tree(int i, int j) {
    int x = tree[i][j];
    if (x == 0) return;

    cout << x << " ";

    print_tree(i, x - i);
    print_tree(x + 1, j - x + i - 1);
}

void _print_f() {
#ifndef NDEBUG
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) cout << f[x][y] << " ";
        cout << endl;
    }
#endif  // IFNDEF NDEBUG
}
