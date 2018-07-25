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

// Wrong
int DP(const vector<int> &W, const vector<int> &V, const vector<int> &C,
       const int size) {
    int n = W.size();
    vector<int> d(size + 1);

    for (int i = 0; i < n; i++) {
        for (int j = W[i]; j <= size; j++) {
            for (int k = 1; k <= C[i] && k * W[i] <= j; k++) {
                d[j] = std::max(d[j], d[j - k * W[i]] + k * V[i]);
            }                                   // for
        }                                       // for
        for (auto e : d) { cout << e << ' '; }  // foreach in d
        cout << endl;
    }  // for

    return d[size];
}
