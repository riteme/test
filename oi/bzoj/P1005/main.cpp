#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000

#define INTLENMAX 4000

struct Integer {
    Integer() : size(1) {
        memset(number, 0, sizeof(number));
    }

    Integer(const Integer &b) : size(b.size) {
        memcpy(number, b.number, sizeof(number));
    }

    // Integer(Integer &&b) : size(b.size) {
    //     memcpy(number, b.number, sizeof(number));
    // }

    Integer &operator=(const Integer &b) {
        size = b.size;
        memcpy(number, b.number, sizeof(number));

        return *this;
    }

    // Integer &operator=(Integer &&b) {
    //     size = b.size;
    //     memcpy(number, b.number, sizeof(number));

    //     return *this;
    // }

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
    int number[INTLENMAX];

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
        char buffer[INTLENMAX];
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

static Integer one;
static Integer n;
static int ni;
static char nbuf[32];
static int D[NMAX + 10];
static Integer fac[NMAX + 10];

static void initialize() {
    one.store("1");

    fac[0] = one;
    Integer i = one;
    for (int p = 1; p <= 1000; p++) {
        fac[p] = fac[p - 1] * i;
        i += one;
    }

    scanf("%s", nbuf);
    n.store(nbuf);
    ni = atoi(nbuf);
}

int main() {
    initialize();

    if (ni == 1) {
        int d;
        scanf("%d", &d);

        if (d == 0 || d == -1)
            puts("1");
        else
            puts("0");
    } else if (ni == 2) {
        int d1, d2;
        scanf("%d%d", &d1, &d2);

        if ((d1 == -1 && d2 == -1) ||
            (d1 == 1 && d2 == -1) ||
            (d1 == -1 && d2 == 1) ||
            (d1 == 1 && d2 == 1))
            puts("1");
        else
            puts("0");
    } else {
        int remain = ni - 2;
        int available = ni;
        for (int i = 1; i <= ni; i++) {
            int d;
            scanf("%d", &d);

            if (d > 0) {
                D[i] = d;
                remain -= d - 1;
                available--;
            } else if (d == 0) {
                remain = -1;
            }
        }

        if (available == 0 && remain != 0) {
            puts("0");
            return 0;
        }

        if (remain > 0 || (remain == 0 && available == 0)) {
            Integer answer = fac[ni - remain - 2];
            for (int i = 1; i <= ni; i++) {
                if (D[i])
                    answer /= fac[D[i] - 1];
            }

            if (remain) {
                Integer base = one;
                for (int i = 1; i < available; i++) {
                    base += one;
                }

                for (int i = 0; i < remain; i++) {
                    answer *= base;
                }
            }

            answer *= fac[ni - 2];
            answer /= fac[remain];
            answer /= fac[ni - 2 - remain];
            
            answer.print();
        } else
            puts("0");
    }

    return 0;
}
