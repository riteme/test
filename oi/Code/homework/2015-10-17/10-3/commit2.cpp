#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n;
    vector<int> data;

    cin >> n;

    data.resize(n);
    for (int i = 0; i < n; i++) { cin >> data[i]; }  // for

    std::sort(data.begin(), data.end(), std::greater<int>());

    if (n < 2) { return -1; }

    int a, b;
    a = std::max(data[0], data[1]);
    b = std::min(data[0], data[1]);
    cout << "a += " << a << endl;
    cout << "b += " << b << endl;

    int upBound = n % 2 == 0 ? n : n - 1;
    for (int i = 2; i < upBound; i += 2) {
        a += data[i + 1];
        b += data[i];

        cout << "a += " << data[i + 1] << endl;
        cout << "b += " << data[i] << endl;
    }  // for

    if (n % 2 == 1) {
        if (a < b) {
            a += data.back();
            cout << "a += " << data.back() << endl;
        } else {
            b += data.back();
            cout << "b += " << data.back() << endl;
        }
    }

    cout << std::min(a, b) << ' ' << std::max(a, b) << endl;

    return 0;
}  // function main
