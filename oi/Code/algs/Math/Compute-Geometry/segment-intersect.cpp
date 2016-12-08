#include <iomanip>
#include <iostream>

#include "geometry.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::boolalpha;

int main() {
    Vector2 a, b, c, d;
    cin >> a >> b >> c >> d;

    cout << boolalpha << is_intersect(a, b, c, d) << endl;

    return 0;
}  // function main
