#include <iomanip>
#include <vector>
#include <iostream>

#include "geometry.hpp"

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<Vector2> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i];
    }  // for

    polar_sort(vec.begin(), vec.end());

    for (auto &e : vec) {
        cout << e << endl;
    }  // foreach in vec

    return 0;
}  // function main
