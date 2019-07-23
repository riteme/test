#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

int main() {
    cout << (double) std::chrono::high_resolution_clock::period::num
             / std::chrono::high_resolution_clock::period::den << endl;
    return 0;
}
