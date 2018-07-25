//
// Copyright 2015 riteme
// DP - 01 Bag Problem
// Solved
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// static ifstream cin("data.in");
// static ofstream cout("data.out");

int DP(const vector<int> &W, const vector<int> &V, const vector<int> &C,
       const int size);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n;
    int size;
    vector<int> weight;
    vector<int> values;
    vector<int> counts;

    cin >> size;
    cin >> n;

    weight.resize(n);
    values.resize(n);
    counts.resize(n);
    for (int i = 0; i < n; i++) { cin >> weight[i] >> values[i] >> counts[i]; }

    int result = DP(weight, values, counts, size);

    cout << result << endl;

    return 0;
}  // function main

int DP(const vector<int> &W, const vector<int> &V, const vector<int> &C,
       const int size) {
    int n = W.size();
    vector<vector<int>> d(n);
    for (auto &e : d) { e.resize(size + 1); }  // foreach in d

    for (int i = 0; i < n; i++) {
        for (int j = W[i]; j <= size; j++) {
            for (int k = 0; k <= C[i] && k * W[i] <= j; k++) {
                if (i > 0) {
                    d[i][j] = std::max(d[i - 1][j],
                                       d[i - 1][j - k * W[i]] + k * V[i]);
                } else { d[i][j] = k * V[i]; }
            }  // for
        }      // for
    }          // for

    return d[n - 1][size];
}
