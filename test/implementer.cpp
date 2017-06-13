#include "int.h"

#include <iostream>

uint64_t int2048_t::cost;

int main() {
    std::string target;
    std::cin >> target;

    int2048_t num(target);
    int user = evaluate(num);
    int std = 0;

    for (int i = 0; i < target.size(); i++)
        if (target[i] == '1')
            std++;

    if (user != std)
        std::cout << "Wrong answer: expected " << std
                  << ", but got " << user << std::endl;
    else
        std::cout << "Cost = " << int2048_t::cost << std::endl;

    return 0;
}
