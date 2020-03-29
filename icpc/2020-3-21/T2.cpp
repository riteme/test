// usage: ./a.out [n]
//   e.g. ./a.out 10000000
// compile it with "-std=c++11" and "-O3"

// #define VECTOR
// #define LIST

#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>

typedef long long i64;

struct Foo {
    i64 value;
    Foo *next;
    i64 junk[30];
};

std::vector<Foo*> vec;
Foo *list;

#define tick std::chrono::high_resolution_clock::now()
#define duration(a, b) \
    std::chrono::duration_cast<std::chrono::microseconds>(b - a).count()

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    i64 *mem = new i64[n];

    std::random_device rd;
    std::mt19937_64 gen(rd());

    for (int i = 0; i < n; i++) {
        mem[i] = gen();
        auto x = new Foo{mem[i], list};
        list = x;
        vec.push_back(x);
    }
    std::reverse(vec.begin(), vec.end());

    // auto t1 = tick;
    // i64 ans0 = 0;
    // for (int i = 0; i < n; i++)
    //     ans0 += mem[i];
    // auto t2 = tick;
    // auto tm0 = duration(t1, t2);

#ifdef VECTOR
    auto t5 = tick;

    i64 ans1 = 0;
    for (int i = 0; i < 1000; i++)
    for (auto e : vec)
        ans1 += e->value;

    auto t6 = tick;
    auto tm1 = duration(t5, t6);
#endif

#ifdef LIST
    auto t3 = tick;

    i64 ans2 = 0;
    for (int i = 0; i < 1000; i++)
    for (auto e = list; e; e = e->next)
        ans2 += e->value;

    auto t4 = tick;
    auto tm2 = duration(t3, t4);
#endif

    // std::cout << "scan:   " << ans0 << " " << tm0 << "μs" << std::endl;

#ifdef VECTOR
    std::cout << "vector: " << ans1 << " " << tm1 << "μs" << std::endl;
#endif

#ifdef LIST
    std::cout << "list:   " << ans2 << " " << tm2 << "μs" << std::endl;
#endif

    delete[] mem;
    return 0;
}