// 编辑距离问题
// WA

#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_LENGTH 4000

template <typename T>
T abs(const T &v) {
    return v >= 0 ? v : -v;
}

static string a, b;
static int maxlen, minlen;
static int dlen;
static int f[MAX_LENGTH + 10][MAX_LENGTH + 10];

void initialize();
void output();

int main() {
    ios::sync_with_stdio(false);
    initialize();

    string &m = a.size() < b.size() ? b : a;
    string &n = a.size() >= b.size() ? b : a;

    for (int j = 1; j <= minlen; j++) {
        if (m[j - 1] == n[j - 1])
            f[0][j] = f[0][j - 1];
        else
            f[0][j] = f[0][j - 1] + 1;
    }  // for

    for (int i = 1; i <= dlen; i++) {
        for (int j = i + 1; j <= minlen + i; j++) {
            int v = 0;

            if (m[j - 1] != n[j - i - 1]) v = 1;

            f[i][j] = min(f[i][j - 1] + v, f[i - 1][j - 1] + 1);
        }  // for
    }      // for

    output();
    return 0;
}  // function main

void initialize() {
    cin >> a >> b;

    dlen = abs(int(a.size()) - int(b.size()));
    maxlen = max(a.size(), b.size());
    minlen = min(a.size(), b.size());

    for (int i = 0; i <= dlen; i++) { f[i][i] = i; }  // for
}

void output() {
    // for (int i = 0; i <= dlen; i++) {
    //     for (int j = 1; j <= maxlen; j++) { cout << f[i][j] << " "; }  // for
    //     cout << endl;
    // }  // for

    cout << f[dlen][maxlen];
}
