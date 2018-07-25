#include <cstdio>
#include <cstring>

#define LENGTH 7000

struct Integer {
    Integer() {
        size = 1;
        memset(num, 0, sizeof(num));
    }

    int size;
    int num[LENGTH];

    void correct() {
        for (int i = 0; i < size; i++) {
            num[i + 1] += num[i] / 10;
            num[i] %= 10;
        }

        while (num[size]) {
            num[size + 1] += num[size] / 10;
            num[size] %= 10;
            size++;
        }
    }

    Integer &operator*=(const Integer &b) {
        int c[LENGTH];
        memset(c, 0, sizeof(c));

        for (int i = 0; i < size; i++)
            for (int j = 0; j < b.size; j++)
                c[i + j] += num[i] * b.num[j];

        size = size + b.size - 1;
        memcpy(num, c, sizeof(num));
        correct();
        return *this;
    }

    Integer &operator-=(const int b) {
        if (num[0] >= b)
            num[0] -= b;
        else {
            num[0] = num[0] + 10 * num[1] - b;
            num[1]--;
        }

        if (num[size - 1] == 0)
            size--;

        return *this;
    }

    Integer &operator-=(const Integer &b) {
        for (int i = b.size - 1; i >= 0; i--) {
            num[i] -= b.num[i];

            int j = i;
            while (j < size && num[j] < 0) {
                num[j] += 10;
                num[j + 1]--;
                j++;
            }
        }

        while (num[size - 1] == 0)
            size--;

        return *this;
    }
};

static Integer r;
static Integer a;
inline Integer pow2(int b) {
    memset(r.num, 0, sizeof(r.num));
    memset(a.num, 0, sizeof(a.num));
    r.size = 1;
    r.num[0] = 1;
    a.size = 1;
    a.num[0] = 2;

    while (b) {
        if (b & 1)
            r *= a;
        a *= a;
        b >>= 1;
    }

    return r;
}

int main() {
    freopen("chess.in", "r", stdin);
    freopen("chess.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);

    Integer twonm1 = pow2(n + m - 1);
    Integer twom1 = pow2(m - 1);
    Integer twon = pow2(n);
    twom1 -= 1;
    twon -= 2;
    twom1 *= twon;
    twonm1 -= twom1;

    for (int i = twonm1.size - 1; i >= 0; i--) {
        putchar(twonm1.num[i] + '0');
    }
    putchar('\n');

    return 0;
}
