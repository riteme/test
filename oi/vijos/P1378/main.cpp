#include <climits>
#include <cmath>
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

        return *this;
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

    Integer &operator*=(const int b) {
        for (int i = 0; i < size; i++)
            number[i] *= b;

        correct();

        return *this;
    }
};  // struct Integer

#define NMAX 80
#define VMAX 1000

static int n, m;
static int mat[NMAX + 10][NMAX + 10];
static Integer f[NMAX + 10][NMAX + 10];
static Integer tpow[NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &mat[i][j]);
        }  // for
    }      // for
}

int main() {
    initialize();

    tpow[0].store(1);
    for (int i = 1; i <= m; i++) {
        tpow[i] = tpow[i - 1];
        tpow[i] *= 2;
    }  // for

    Integer answer;

    for (int p = 1; p <= n; p++) {
        for (int i = 1; i <= m; i++) {
            f[i][i] = tpow[m];
            f[i][i] *= mat[p][i];
        }  // for

        for (int l = 1; l < m; l++) {
            for (int i = 1; i <= m; i++) {
                int j = i + l;
                int selected = i - 1 + m - j + 1;
                Integer t1 = tpow[selected];
                Integer t2 = tpow[selected];
                t1 *= mat[p][i];
                t1 += f[i + 1][j];
                t2 *= mat[p][j];
                t2 += f[i][j - 1];

                if (t1 < t2)
                    f[i][j] = t2;
                else
                    f[i][j] = t1;
            }  // for
        }      // for

        answer += f[1][m];
    }  // for

    answer.print();

    return 0;
}  // function main
