//
// Copyright 2015 riteme
// Accepted
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> ArrayType;

int DP(int size, const ArrayType &V);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    ArrayType v;
    int n, size;
    cin >> size >> n;

    v.resize(n);
    for (int i = 0; i < n; i++) { cin >> v[i]; }  // for

    cout << DP(size, v) << endl;

    return 0;
}  // function main

int DP(int size, const ArrayType &V) {
    vector<ArrayType> d;

    d.resize(V.size());
    for (vector<ArrayType>::iterator beg = d.begin(); beg != d.end(); beg++) {
        beg->resize(size + 1);
    }  // for

    for (int i = 0; i < V.size(); i++) {
        for (int j = 0; j <= size; j++) {
            if (i > 0) { d[i][j] = d[i - 1][j]; }

            if (V[i] <= j) {
                if (i == 0) { d[i][j] = V[i]; } else {
                    d[i][j] = std::max(d[i - 1][j], d[i - 1][j - V[i]] + V[i]);
                }
            }
        }  // for
    }      // for

    return size - d[V.size() - 1][size];
}
