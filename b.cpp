#include <cstdio>
struct A {
    int a, b, c;
    A();
    void fuck();
};
static struct B {
    B() {
        puts("B");
    }
    A* ptr;
} dat __attribute__((init_priority(101)));
A::A() {
    puts("A");
    dat.ptr = this;
}
void A::fuck() {
    a =1;b=2;c=3;
}
