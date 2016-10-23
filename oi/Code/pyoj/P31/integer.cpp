#include <cstdio>
#include <cstring>

#include <algorithm>
#include <string>

using namespace std;

#define NMAX 30000

struct Integer {
    Integer() : size(1) {
        memset(number, 0, sizeof(number));
    }

    Integer(const Integer &b) : size(b.size) {
        memcpy(number, b.number, sizeof(number));
    }

    Integer(Integer &&b) : size(b.size) {
        memcpy(number, b.number, sizeof(number));
    }

    Integer &operator=(const Integer &b) {
        size = b.size;
        memcpy(number, b.number, sizeof(number));

        return *this;
    }

    Integer &operator=(Integer &&b) {
        size = b.size;
        memcpy(number, b.number, sizeof(number));

        return *this;
    }

    bool operator==(const Integer &b) const {
        if (size != b.size)
            return false;

        for (int i = 0; i < size; i++)
            if (number[i] != b.number[i])
                return false;
        return true;
    }

    bool operator!=(const Integer &b) const {
        return !(*this == b);
    }

    bool operator<(const Integer &b) const {
        if (size < b.size)
            return true;
        if (size > b.size)
            return false;

        for (int i = size - 1; i >= 0; i--) {
            if (number[i] < b.number[i])
                return true;
            else if (number[i] > b.number[i])
                return false;
        }  // for

        return false;
    }

    bool operator<=(const Integer &b) const {
        if (size < b.size)
            return true;
        if (size > b.size)
            return false;

        for (int i = size - 1; i >= 0; i--) {
            if (number[i] < b.number[i])
                return true;
            else if (number[i] > b.number[i])
                return false;
        }  // for

        return true;
    }

    bool operator>(const Integer &b) const {
        return !(*this <= b);
    }

    bool operator>=(const Integer &b) const {
        return !(*this < b);
    }

    Integer operator+(const Integer &b) const {
        const Integer *m = size >= b.size ? this : &b;
        const Integer *n = size >= b.size ? &b : this;
        Integer c = *m;

        for (int i = 0; i < n->size; i++)
            c.number[i] += n->number[i];

        c.correct();
        return c;
    }

    Integer &operator+=(const Integer &b) {
        *this = *this + b;

        return *this;
    }

    Integer operator-(const Integer &b) const {
        Integer c = *this;

        for (int i = 0; i < b.size; i++) {
            if (c.number[i] >= b.number[i])
                c.number[i] -= b.number[i];
            else {
                c.number[i] = c.number[i] + 10 - b.number[i];
                c.number[i + 1]--;
            }
        }  // for

        for (int i = 0; i < c.size; i++)
            if (c.number[i] < 0) {
                c.number[i] = 9;
                c.number[i + 1]--;
            }

        while (c.size > 1 && c.number[c.size - 1] == 0)
            c.size--;

        return c;
    }

    Integer &operator-=(const Integer &b) {
        *this = *this - b;

        return *this;
    }

    Integer operator*(const Integer &b) const {
        Integer c;

        for (int i = 0; i < size; i++)
            for (int j = 0; j < b.size; j++)
                c.number[i + j] += number[i] * b.number[j];

        c.size = size + b.size - 1;
        c.correct();

        return c;
    }

    Integer &operator*=(const Integer &b) {
        *this = *this * b;

        return *this;
    }

    Integer operator/(const Integer &b) const {
        Integer c;
        Integer target = *this;
        Integer bitrecoder;
        Integer tester = b;
        bitrecoder.store("1");

        while (tester < target) {
            tester.mul2();
            bitrecoder.mul2();
        }

        while (bitrecoder.size > 1 || bitrecoder.number[0] > 0) {
            while (tester > target) {
                tester.div2();
                bitrecoder.div2();
            }

            target -= tester;
            c += bitrecoder;
        }

        return c;
    }

    Integer &operator/=(const Integer &b) {
        *this = *this / b;

        return *this;
    }

    Integer operator%(const Integer &b) const {
        Integer c = *this;
        Integer tester = b;

        while (tester < c)
            tester.mul2();

        while (c >= b) {
            while (tester > c)
                tester.div2();

            c -= tester;
        }

        return c;
    }

    Integer &operator%=(const Integer &b) {
        *this = *this % b;

        return *this;
    }

    int size;
    int number[NMAX];

    void store(const char *src) {
        size = strlen(src);
        for (int i = 0; i < size; i++)
            number[size - i - 1] = src[i] - '0';
    }

    void get(char *dest) const {
        for (int i = 0; i < size; i++)
            dest[size - i - 1] = number[i] + '0';
        dest[size] = '\0';
    }

    void print() const {
        char buffer[NMAX];
        get(buffer);

        printf("%s\n", buffer);
    }

 private:
    void correct() {
        int remain = 0;

        for (int i = 0; i < size; i++) {
            number[i] += remain;
            remain = number[i] / 10;
            number[i] %= 10;
        }

        while (remain) {
            number[size] = remain % 10;
            remain /= 10;
            size++;
        }
    }

    void mul2() {
        int remain = 0;
        for (int i = 0; i < size; i++) {
            number[i] = (number[i] << 1) + remain;
            remain = number[i] / 10;
            number[i] %= 10;
        }

        while (remain) {
            number[size] = remain % 10;
            remain /= 10;
            size++;
        }
    }

    void div2() {
        int remain = 0;

        for (int i = size - 1; i >= 0; i--) {
            remain = remain * 10 + number[i];
            number[i] = remain >> 1;
            remain &= 1;
        }

        while (size > 1 && number[size - 1] == 0)
            size--;
    }
};  // struct Integer

int main() {
    freopen("integer99.in", "r", stdin);

    char symbol;
    char a[20000], b[20000];
    char buffer[20000];
    symbol = getchar();
    scanf("%s%s", a, b);

    bool flag = false;
    Integer ai, bi;
    ai.store(a);
    bi.store(b);

    switch (symbol) {
        case '+': {
            ai += bi;
        } break;

        case '-': {
            if (ai < bi) {
                flag = true;
                ai = bi - ai;
            } else
                ai -= bi;
        } break;

        case '*': {
            ai *= bi;
        } break;

        case '/': {
            ai /= bi;
        } break;

        case '%': {
            ai %= bi;
        } break;

        default: puts("orz HJWJBSR!"); break;
    }  // switch to symbol

    ai.get(buffer);

    if (flag)
        putchar('-');
    printf("%s\n", buffer);

    return 0;
}  // function main
