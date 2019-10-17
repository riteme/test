#include <cstdio>

template <typename T>
void show_signature(T x) {
    puts(__PRETTY_FUNCTION__);
}

int main() {
    show_signature(2147483647);
    show_signature(2147483648);
    show_signature(-2147483647);
    show_signature(-2147483648);
    show_signature(-2147483647 - 1);
    show_signature(0x80000000);
    return 0;
}
