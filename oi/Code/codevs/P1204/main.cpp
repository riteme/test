#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    string a, b;
    cin >> a >> b;
    cout << std::distance(a.begin(),
                          std::search(a.begin(), a.end(), b.begin(), b.end())) +
                1 << endl;

    return 0;
}  // function main
