// P1051 选课
// AC

#include <climits>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define NMAX 300
#define MMAX 300

static int n, m;
static int w[NMAX + 10];
static vector<int> t[NMAX + 10];
static vector<vector<int>> f;
static int h[NMAX + 10];
static int result;

void initialize();
void output();
void solve(int x);
void recursive(int x);
void _print_f();

int main() {
    ios::sync_with_stdio(false);
    initialize();

    recursive(0);
    result = f.back().back();

    output();

    // _print_f();

    return 0;
}  // function main

void _print_f() {
    for (int i = 0; i <= n; i++) {
        cout << i << ": ";

        if (h[i] == -1)
            cout << "Nothing.";
        else
            for (auto &e : f[h[i]]) cout << e << " ";

        cout << endl;
    }  // for
}

void initialize() {
    fill(begin(h), end(h), -1);
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p >> w[i];
        t[p].push_back(i);
    }

    result = INT_MIN;
}

void output() { cout << result << endl; }

void recursive(int x) {
    if (!t[x].empty()) {
        for (auto c : t[x]) { recursive(c); }  // foreach in t[x]
    }

    solve(x);
}

void solve(int x) {
    if (t[x].empty()) return;

    h[x] = f.size();
    f.resize(f.size() + 1);
    f.back().resize(m + 1, 0);

    auto &dp = f.back();
    for (auto c : t[x]) {
        vector<int> *child = nullptr;

        if (h[c] != -1) child = &f[h[c]];

        if (child == nullptr) {
            // cout << c << ": 0-1 Dping..." << endl;
            for (int i = m; i >= 1; i--) {
                dp[i] = max(dp[i], dp[i - 1] + w[c]);
            }  // for
        } else {
            // cout << c << ": Strange Dping..." << endl;

            for (int i = m; i >= 1; i--) {
                int tmp = INT_MIN;

                for (int k = 1; k <= i; k++) {
                    tmp = max(tmp, (*child)[i - k] + dp[k - 1] + w[c]);
                }  // for

                dp[i] = max(dp[i], tmp);
            }  // for
        }

        // for (auto &e : dp) { cout << e << " "; }  // foreach in dp
        // cout << endl;
    }  // foreach in t[x]
}
