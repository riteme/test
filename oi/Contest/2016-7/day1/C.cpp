#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

#define BLOCKSIZE 300

class Case1 {
 public:
    Case1() {}
    ~Case1() {}

    void main() {}
};  // class Case1

int main() {
    // Case1 *instance = new Case1;
    // instance->main();

    long double a =
        1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.0L;
    printf("%.0Lf\n", a);

    return 0;
}  // function main
