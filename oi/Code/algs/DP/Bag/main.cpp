//
// Copyright 2015 riteme
// DP - 01 Bag Problem
// Solved
//

// #include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

static ifstream cin("data.in");
static ofstream cout("data.out");

int DP(const vector<int> &W, const vector<int> &V, const int size);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n;
    int size;
    vector<int> weight;
    vector<int> values;

    cin >> size;
    cin >> n;

    weight.resize(n);
    values.resize(n);
    for (int i = 0; i < n; i++) { cin >> weight[i] >> values[i]; }

    int result = DP(weight, values, size);
    cout << result << endl;

    return 0;
}  // function main

int DP(const vector<int> &W, const vector<int> &V, const int size) {
    int n = W.size() - 1;
    vector<vector<int>> d;

    d.resize(n + 1);
    for (auto &e : d) { e.resize(size + 1); }  // foreach in d

    for (int i = 0; i <= n; i++) {
        for (int j = 1; j <= size; j++) {
            if (i > 0) { d[i][j] = d[i - 1][j]; }

            if (W[i] <= j) {
                d[i][j] = i == 0 ? V[0] : std::max(d[i - 1][j],
                                                   d[i - 1][j - W[i]] + V[i]);
            }
        }
    }

    return d[n][size];
}
