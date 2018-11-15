#include <map>
#include <iostream>

int main() {
    std::map<int, int> a;
    a[1]=2;
    a[2]=3;
    for (int v : a) {
        std::cout << a[v] << std::endl;
    }
    return 0;
}
