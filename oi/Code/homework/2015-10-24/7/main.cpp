// I don't know what the problem means.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;

    vector<unsigned long long> w(n);
    for (int i = 0; i < n; i++) { cin >> w[i]; }  // for

    std::sort(w.begin(), w.end());

    w[n - 2] = (w[n - 1] + w[n - 2]) / k;
    for (int i = n - 3; i >= 0; i--) { w[i] = (w[i] + w[i + 1]) / k; }  // for

    cout << w[0];

    return 0;
}  // function main
