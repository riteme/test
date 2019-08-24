#include <iostream>
#include <set>

using namespace std;

set<int> Count(int n);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    for (auto i : Count(n)) { cout << i << ' '; }  // foreach in Count(n)
    cout << endl;

    return 0;
}  // function main

set<int> Count(int n) {
    if (n < 2) { return { 0 }; }
    if (n == 2) { return { 0, 1 }; }

    set<int> result;
    for (int p = n; p > 0; p--) {
        for (auto i : Count(n - p)) {
            result.insert(p * (n - p) + i);
        }  // foreach in Count(n-p)
    }      // for

    return result;
}
