#include "int2048_t.hpp"

int evaluate(const int2048_t &num) {
    int answer = 0;

    int2048_t tester(std::string("1"));
    for (int i = 0; i < 2047; i++) {
        if (num & tester)
            answer++;

        if (i < 2046)
            tester = tester << 1;
    }

    return answer;
}
