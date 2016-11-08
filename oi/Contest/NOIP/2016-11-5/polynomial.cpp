#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NUMLENGTH 500
#define POLYLENGTH 300

struct Integer {
    Integer() {
        size = 1;
        memset(num, 0, sizeof(num));
    }

    int size;
    int num[NUMLENGTH];

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
        int c[NUMLENGTH];
        memset(c, 0, sizeof(c));

        for (int i = 0; i < size; i++)
            for (int j = 0; j < b.size; j++)
                c[i + j] += num[i] * b.num[j];

        size = size + b.size - 1;
        memcpy(num, c, sizeof(num));
        correct();
        return *this;
    }
    
    Integer &operator+=(const Integer &b) {
        for (int i = 0; i < b.size; i++)
            num[i] += b.num[i];
        size = max(size, b.size);
        correct();

        return *this;
    }
};

struct Polynomial {
    int size;
    Integer num[POLYLENGTH];

    Polynomial &operator*=(const Polynomial &b) {
        Integer c[POLYLENGTH];
        Integer tmp;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < b.size; j++) {
                tmp = num[i];
                tmp *= b.num[j];
                c[i + j] += tmp;
            }
        }

        size = size + b.size - 1;
        memcpy(num, c, sizeof(num));
        return *this;
    }
    
    Integer sum() {
        Integer r;

        for (int i = 0; i < size; i++)
            r += num[i];

        return r;
    }
};

static Polynomial A;
static Polynomial B;
static Integer r;

int main() {
    freopen("polynomial.in", "r", stdin);
    freopen("polynomial.out", "w", stdout);
    int a, b, c, k;
    scanf("%d%d%d%d", &a, &b, &c, &k);

    if (k == 0) {
        puts("1");
        return 0;
    }

    A.size = 3;
    A.num[0].num[0] = c;
    A.num[1].num[0] = b;
    A.num[2].num[0] = a;
    B = A;
    
    for (int i = 0; i < k - 1; i++) 
        A *= B;

    r = A.sum();

    for (int i = r.size - 1; i >= 0; i--)
        putchar(r.num[i] + '0');
    putchar('\n');

    return 0;
}
