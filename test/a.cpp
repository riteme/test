#include <cstdio>
#include <cstring>

template <typename T>
T show(T x) {
    return x;
}

int main() {
    auto a = 1*1u;
    show(static_cast<const int>(a));
    return 0;
}
