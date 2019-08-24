#include <iomanip>
#include <iostream>

#include "geometry.hpp"

using std::cin;
using std::cout;
using std::endl;

int main() {
    Vector2 a, b, c;
    cin >> a >> b >> c;

    double p = turning(a, b, c);
    if (is_same(p, 0.0))
        cout << "Go straight." << endl;
    else if (p < 0)
        cout << "Turn right." << endl;
    else
        cout << "Turn left." << endl;

    return 0;
}  // function main
