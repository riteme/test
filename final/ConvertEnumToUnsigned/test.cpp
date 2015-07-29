#include <bitset>
#include <iostream>
using namespace std;

enum class ENUM {
    A, B, C, D
};  // enum class A

int main(int argc, char *argv[]) {
    bitset<4> b;
    b.flip(static_cast<unsigned>(ENUM::A));
    cout << b << endl;
    return 0;
}  // function main

