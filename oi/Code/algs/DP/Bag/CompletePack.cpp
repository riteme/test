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
    int n = W.size();
    vector<int> d(size + 1);

    for (int i = 0; i < n; i++) {
        for (int j = W[i]; j <= size; j++) {
            d[j] = std::max(d[j], d[j - W[i]] + V[i]);
        }  // for
    }      // for

    return d[size];
}
