#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long int64;

#define INTERGER_LENGTH 100000

struct Integer {
    Integer() : size(1) {
        memset(number, 0, sizeof(number));
    }

    Integer(const char *str) : size(strlen(str)) {
        memset(number, 0, sizeof(number));

        for (int i = size - 1; i >= 0; i--) {
            number[size - i - 1] = str[i] - '0';
        }  // for
    }

    Integer(const Integer &b) : size(b.size) {
        memcpy(number, b.number, sizeof(number));
    }

    int size;
    int64 number[INTERGER_LENGTH];

    void print() const {
        for (int i = size - 1; i >= 0; i--) {
            putchar(number[i] + '0');
        }  // for
    }

    void correct() {
        int64 remain = 0;
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

    bool operator==(const Integer &b) const {
        if (size != b.size)
            return false;

        for (int i = 0; i < size; i++) {
            if (number[i] != b.number[i])
                return false;
        }  // for

        return true;
    }

    bool operator!=(const Integer &b) const {
        return !(*this == b);
    }

    bool operator<(const Integer &b) const {
        if (size < b.size)
            return true;
        else if (size > b.size)
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
        else if (size > b.size)
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

    Integer &operator*=(const int64 b) {
        for (int i = 0; i < size; i++)
            number[i] *= b;

        correct();

        return *this;
    }

    Integer &operator/=(const int64 b) {
        int64 tmp = 0;
        for (int i = size - 1; i >= 0; i--) {
            tmp = tmp * 10 + number[i];

            if (tmp >= b) {
                number[i] = tmp / b;
                tmp %= b;
            } else
                number[i] = 0;
        }  // for

        while (size > 1 && number[size - 1] == 0)
            size--;

        correct();

        return *this;
    }
};  // struct Integer

#define NMAX 100000

static int n;
static int64 l, r;
static int64 a[NMAX + 10];
static int64 b[NMAX + 10];
static int sorted[NMAX + 10];

static bool cmp(const int i, const int j) {
    return a[i] * b[i] < a[j] * b[j];
}

int main() {
    scanf("%d", &n);

    scanf("%lld%lld", &l, &r);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", a + i, b + i);
        sorted[i] = i;
    }  // for

    sort(sorted + 1, sorted + n + 1, cmp);

    Integer pre;
    Integer answer;
    pre.number[0] = 1;
    pre *= l;

    for (int i = 1; i <= n; i++) {
        int p = sorted[i];
        Integer result = pre;
        result /= b[p];

        if (result > answer)
            answer = result;

        pre *= a[p];
    }  // for

    answer.print();

    return 0;
}  // function main
