#include "int.h"

#include <iostream>
#include <algorithm>

#define TOKEN "623a4d20bdc597ce5e3fc485c22ab1e2"

uint64_t  int2048_t::fake1;
uint64_t  int2048_t::fake2;
uint64_t  int2048_t::fake3;
uint64_t* int2048_t::cost;
uint64_t  int2048_t::fake4;
uint64_t  int2048_t::fake5;

void _print_axvc(const int2048_t &a) {
    for (int i = 2047; i >= 0; i--)
        std::cout << a._num[i];
    std::cout << std::endl;
}

int main() {
    int2048_t::cost = new uint64_t(0);

    long double vmin, vmax;
    std::string target;
    std::cin >> vmin >> vmax >> target;

    int2048_t num(target);
    int user = evaluate(num);
    int std = 0;

    for (int i = 0; i < target.size(); i++)
        if (target[i] == '1')
            std++;

    std::cout << TOKEN << std::endl;
    if (user != std) {
        std::cout << "0" << std::endl;
        std::cout << "Wrong answer: expected " << std
                  << ", but got " << user << std::endl;
    } else {
        long long score = std::max(
            10.0L * std::min(1.0L, (vmax - *int2048_t::cost) / (vmax - vmin)),
            0.0L
        );
        std::cout << score << std::endl;
        std::cout << "Cost = " << *int2048_t::cost << std::endl;
    }

    delete int2048_t::cost;

    return 0;
}
