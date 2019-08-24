#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 7700000

struct Rational {
    Rational() : x(0), y(1) {}
    Rational(int _x, int _y) : x(_x), y(_y) {}
    Rational(const Rational &b) : x(b.x), y(b.y) {}

    int x, y;

    void print() {
        printf("%d/%d\n", x, y);
    }

    Rational operator+(const Rational &b) const {
        return Rational(x + b.x, y + b.y);
    }
};

static int n, q;
static vector<Rational> farey;

void dfs(Rational l, Rational r) {
    Rational x = l + r;
    if (x.y > n)
        return;

    dfs(l, x);
    farey.push_back(x);
    dfs(x, r);
}

int main() {
    scanf("%d%d", &n, &q);

    farey.reserve(NMAX);
    farey.push_back(Rational(0, 1));
    dfs(Rational(0, 1), Rational(1, 1));
    farey.push_back(Rational(1, 1));

    while (q--) {
        int k;
        scanf("%d", &k);

        if (k > farey.size())
            puts("No Solution");
        else
            farey[k - 1].print();
    }

    return 0;
}
