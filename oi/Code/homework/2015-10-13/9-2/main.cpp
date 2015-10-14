#include <cmath>
#include <iostream>

using namespace std;

typedef unsigned long long Number;

// out of range...

int main() {
    ios::sync_with_stdio(false);

    Number target = 1ULL;
    Number n;
    unsigned count = 1;
    cin >> n;

    while (target % n != 0) {
        target = target * 10ULL + 1ULL;
        count++;
    }  // while

    cout << count << endl;

    return 0;
}
