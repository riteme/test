#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string Combine(const string &a, const string &b);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<string> data(n);
    for (auto &e : data) { cin >> e; }  // foreach in data

    std::sort(data.begin(), data.end());

    for (int i = 0; i < n - 1; i++) {
        data[i + 1] = Combine(data[i], data[i + 1]);
    }  // for

    cout << data.back() << endl;

    return 0;
}  // function main

string Combine(const string &a, const string &b) {
    return std::max(a + b, b + a);
}
