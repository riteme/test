#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Complex {
    int top;
    int bottom;

    bool operator<(const Complex &lhs) const {
        double a = double(top) / bottom;
        double b = double(lhs.top) / lhs.bottom;

        return a < b;
    }
};  // struct Complex

int GCD(int p, int q);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<Complex> fn;
    fn.push_back({ 0, 1 });
    // fn.push_back({ 1, 1 });

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (GCD(j, i) == 1) { fn.push_back({ j, i }); }
        }  // for
    }      // for

    std::sort(fn.begin(), fn.end());

    for (auto &e : fn) {
        cout << e.top << '/' << e.bottom << ", ";
    }  // foreach in fn
    cout << "1/1" << endl;

    return 0;
}  // function main

int GCD(int p, int q) {
    if (q == 0) { return p; }
    int r = p % q;
    return GCD(q, r);
}
