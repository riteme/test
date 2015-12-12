// 借教室

#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 1000000
#define MMAX 1000000

typedef long long ntype;

struct Reservation {
    Reservation() : start(0), end(0), need(0) {}
    Reservation(ntype s, ntype t, ntype d) : start(s), end(t), need(d) {}

    ntype start;
    ntype end;
    ntype need;
};  // struct Reservation

static ntype n, m;
static ntype r[NMAX + 10];
static Reservation q[MMAX + 10];

void initialize();
void quit();

int main() {
    ios::sync_with_stdio(false);
    initialize();

    quit();
    return 0;
}  // function main

void initialize() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) cin >> r[i];
    for (int i = 1; i <= m; i++) cin >> q[i].need >> q[i].start >> q[i].end;
}

void quit();
