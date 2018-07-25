#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define BUFFERSIZE 40

struct Integer {
    Integer() : size(1) {
        memset(number, 0, sizeof(number));
    }

    Integer &operator=(const Integer &b) {
        size = b.size;
        memcpy(number, b.number, sizeof(number));
    }

    int size;
    int number[BUFFERSIZE];

    void store(int x) {
        size = 0;
        while (x) {
            int digit = x % 10;
            x /= 10;
            number[size++] = digit;
        }  // while
    }

    void print() const {
        for (int i = size - 1; i >= 0; i--)
            putchar(number[i] + '0');
        putchar('\n');
    }

    void correct() {
        for (int i = 0; i < size; i++) {
            if (number[i] > 9) {
                number[i + 1] += number[i] / 10;
                number[i] %= 10;
            }
        }  // for

        while (number[size]) {
            if (number[size] > 9) {
                number[size + 1] += number[size] / 10;
                number[size] %= 10;
            }

            size++;
        }
    }

    Integer &operator+=(const Integer &b) {
        for (int i = 0; i < b.size; i++)
            number[i] += b.number[i];

        size = max(size, b.size);
        correct();

        return *this;
    }

    Integer &operator*=(const Integer &b) {
        Integer c;

        for (int i = 0; i < size; i++)
            for (int j = 0; j < b.size; j++)
                c.number[i + j] += number[i] * b.number[j];

        c.size = size + b.size - 1;
        c.correct();

        size = c.size;
        memcpy(number, c.number, sizeof(number));

        return *this;
    }

    Integer &operator*=(const int b) {
        for (int i = 0; i < size; i++)
            number[i] *= b;

        correct();

        return *this;
    }
};  // struct Integer

int main() {
    int a, b;
    scanf("%d%d", &a, &b);

    Integer ai;
    ai.store(a);
    ai *= b;
    ai.print();

    return 0;
}  // function main
