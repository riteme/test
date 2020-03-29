// usage: ./a.out [n]
//   e.g. ./a.out 10000000
// compile it with "-std=c++11" and "-O3"

//#define VECTOR
//#define LIST
// #define LIST2

#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>

typedef long long i64;

struct Foo {
    i64 value;
    Foo *next[32];
    // i64 junk[15];
};

std::vector<Foo*> vec;
Foo *head;

#define tick std::chrono::high_resolution_clock::now()
#define duration(a, b) \
    std::chrono::duration_cast<std::chrono::microseconds>(b - a).count()

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);

    std::random_device rd;
    std::mt19937_64 gen(rd());

    for (int i = 0; i < n; i++) {
        auto x = new Foo{(i64) gen(), NULL};
        // x->junk[0] = gen();
        vec.push_back(x);
    }

    std::shuffle(vec.begin(), vec.end(), gen);
    for (int i = 0; i + 1 < n; i++) {
        for (int j = 0; j < 32; j++)
        if (i + j + 1 < n)
            vec[i]->next[j] = vec[i + j + 1];
        else vec[i]->next[j] = NULL;
    }
    head = vec[0];

#ifdef VECTOR
    auto t7 = tick;

    i64 ans1 = 0;
    for (auto e : vec)
        ans1 += e->value;

    auto t8 = tick;
    auto tm1 = duration(t7, t8);
#endif

#ifdef LIST
    auto t3 = tick;

    i64 ans2 = 0;
    for (auto e = head; e; e = e->next[0])
        ans2 += e->value;

    auto t4 = tick;
    auto tm2 = duration(t3, t4);
#endif

#define LIST2
#ifdef LIST2
    auto t3 = tick;

    i64 ans3 = 0;
    for (auto e = head; e; e = e->next[31]) {
        ans3 += e->value;
        ans3 += e->next[0]->value;
        ans3 += e->next[1]->value;
        ans3 += e->next[2]->value;
        ans3 += e->next[3]->value;
        ans3 += e->next[4]->value;
        ans3 += e->next[5]->value;
        ans3 += e->next[6]->value;
        ans3 += e->next[7]->value;
        ans3 += e->next[8]->value;
        ans3 += e->next[9]->value;
        ans3 += e->next[10]->value;
        ans3 += e->next[11]->value;
        ans3 += e->next[12]->value;
        ans3 += e->next[13]->value;
        ans3 += e->next[14]->value;
        ans3 += e->next[15]->value;
        ans3 += e->next[16]->value;
        ans3 += e->next[17]->value;
        ans3 += e->next[18]->value;
        ans3 += e->next[19]->value;
        ans3 += e->next[20]->value;
        ans3 += e->next[21]->value;
        ans3 += e->next[22]->value;
        ans3 += e->next[23]->value;
        ans3 += e->next[24]->value;
        ans3 += e->next[25]->value;
        ans3 += e->next[26]->value;
        ans3 += e->next[27]->value;
        ans3 += e->next[28]->value;
        ans3 += e->next[29]->value;
        ans3 += e->next[30]->value;
    }

    auto t4 = tick;
    auto tm3 = duration(t3, t4);
#endif

#ifdef LIST3
    auto t10 = tick;

    i64 ans4 = 0;
    for (auto e = head; e; e = e->next)
        ans4 += e->value + e->junk[0];

    auto t11 = tick;
    auto tm4 = duration(t10, t11);
#endif

#ifdef VECTOR
    std::cout << "vector: " << ans1 << " " << tm1 << "μs" << std::endl;
#endif

#ifdef LIST
    std::cout << "list:   " << ans2 << " " << tm2 << "μs" << std::endl;
#endif

#ifdef LIST2
    std::cout << "list2:  " << ans3 << " " << tm3 << "μs" << std::endl;
#endif

#ifdef LIST3
    std::cout << "list3:  " << ans4 << " " << tm4 << "μs" << std::endl;
#endif

    return 0;
}