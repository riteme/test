#include <iostream>

using namespace std;

struct A {
    A() : a(0) {}
    A(int v) : a(v) {}

    int a;

    A &operator+(const A &b) const {
        A ret;
        ret.a = a + b.a;
        return ret;
    }
};

int main() {
    A a = {1}, b = {2};
    A c = a + b;
    printf("%d, %d\n", c.a, (a + b).a);
    return 0;
}
