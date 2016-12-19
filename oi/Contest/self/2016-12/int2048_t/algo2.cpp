#include "int2048_t.hpp"

int evaluate(const int2048_t &num) {
    int answer = 0;
    int2048_t n = num;

    while (n) {
        answer++;
        n = n ^ (n & (-n));
    }

    return answer;
}
