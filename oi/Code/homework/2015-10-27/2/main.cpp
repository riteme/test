#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> data(n);
    for (int i = 0; i < n; i++) { cin >> data[i]; }  // for

    int m;
    cin >> m;

    vector<int>::iterator pos = std::lower_bound(data.begin(), data.end(), m);

    if (pos == data.end()) { cout << -1; } else {
        cout << std::distance(data.begin(), pos) + 1;
    }

    return 0;
}  // function main
