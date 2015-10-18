#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef vector<int> Team;

Team DP(int n, int size, const vector<int> &W);
void DP(int n, int size, const vector<int> &W, vector<vector<int>> &d);
Team ReverseDP(int n, int size, const vector<int> &W, vector<vector<int>> &d);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n;
    vector<int> data;

    cin >> n;

    int sum = 0;
    data.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> data[i];
        sum += data[i];
    }  // for
    int average = sum / 2;

    cout << "sum: " << sum << endl;
    cout << "average: " << average << endl;

    Team a = DP(n, average, data);
    Team b;

    std::sort(a.begin(), a.end(), std::greater<int>());
    for (auto e : data) {
        if (!std::binary_search(a.begin(), a.end(), e, std::greater<int>())) {
            b.push_back(e);
        }
    }  // foreach in data
    std::sort(b.begin(), b.end(), std::greater<int>());

    cout << "A origin team: ";
    for (auto e : a) { cout << e << ' '; }  // foreach in a
    cout << endl;

    cout << "B origin team: ";
    for (auto e : b) { cout << e << ' '; }  // foreach in a
    cout << endl;

    // TODO
    while (fabs(int(a.size()) - int(b.size())) > 1) {
        if (a.size() > b.size()) {
            b.push_back(a.back());
            a.pop_back();
        } else {
            a.push_back(b.back());
            b.pop_back();
        }
    }  // while

    int aCount = 0, bCount = 0;

    cout << "A team: ";
    for (auto e : a) {
        cout << e << ' ';
        aCount += e;
    }  // foreach in a
    cout << endl;

    cout << "B team: ";
    for (auto e : b) {
        cout << e << ' ';
        bCount += e;
    }  // foreach in a
    cout << endl;

    cout << std::min(aCount, bCount) << ' ' << std::max(aCount, bCount) << endl;

    return 0;
}  // function main

Team DP(int n, int size, const vector<int> &W) {
    vector<vector<int>> d;

    d.resize(n);
    for (auto &e : d) { e.resize(size + 1); }  // foreach in d

    DP(n - 1, size, W, d);

    // for (auto &line : d) {
    //     for (auto &e : line) { cout << e << ' '; }  // foreach in line
    //     cout << endl;
    // }  // foreach in d

    return ReverseDP(n - 1, size, W, d);
}

void DP(int n, int size, const vector<int> &W, vector<vector<int>> &d) {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= size; j++) {
            if (i > 0) {
                d[i][j] = W[i] <= j
                              ? std::max(d[i - 1][j], d[i - 1][j - W[i]] + W[i])
                              : d[i - 1][j];
            } else { d[i][j] = W[i] <= j ? W[i] : 0; }
        }  // for
    }      // for
}

// TODO
Team ReverseDP(int n, int size, const vector<int> &W, vector<vector<int>> &d) {
    Team result;
    int j = size;
    for (int i = n; i >= 0; i--) {
        if (W[i] > j) { continue; }

        if (i > 0) {
            if (d[i - 1][j] < d[i - 1][j - W[i]] + W[i]) {
                j -= W[i];
                result.push_back(W[i]);
            }
        } else {
            if (d[i][j] > 0) { result.push_back(W[i]); }
        }
    }  // for

    return result;
}
