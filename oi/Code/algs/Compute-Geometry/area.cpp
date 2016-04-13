#include <vector>
#include <iomanip>
#include <iostream>

#include "geometry.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::setprecision;
using std::fixed;

int main() {
    int n;
    cin >> n;

    vector<Vector2> vec;
    while (n > 0) {
        double x, y;
        cin >> x >> y;

        vec.push_back(Vector2(x, y));

        n--;
    }
    vec.push_back(vec.front());

    double sum = 0.0;
    for (int i = 0; i < vec.size() - 1; i++) {
        sum += vec[i] * vec[i + 1];
    }

    cout << setprecision(6) << fixed;
    cout << sum / 2.0 << endl;

    return 0;
}  // function main
