#include <iomanip>
#include <vector>
#include <iostream>

#include "geometry.hpp"

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<Segment> seg(n);
    for (int i = 0; i < n; i++) {
        cin >> seg[i];
    }  // for

    cout << boolalpha << brute_any_segment_intersect(seg.begin(), seg.end())
         << endl;

    return 0;
}  // function main
