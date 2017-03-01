#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

typedef long long i64;

static i64 A, B, C;
static unordered_set<i64> database;
static vector<pair<i64, i64>> command;

void ensure(i64 x) {
    assert(database.count(x));
}

bool has(i64 x) {
    return database.count(x);
}

void require(i64 i, i64 j) {
    if (i == j)
        return;

    assert(i > j);
    ensure(i);
    ensure(j);
    if (has(i - j))
        return;

    database.insert(i - j);
    command.push_back(make_pair(i, j));
}

void require_2kb(int k, i64 x) {
    assert((x << k) <= A);

    if (has(x << k))
        return;

    if (k == 0)
        ensure(x);
    else {
        require_2kb(k - 1, x);

        i64 tpow = x << (k - 1);
        require(A, tpow);
        require(A - tpow, tpow);
        require(A, A - (tpow << 1));
    }
}

void require_kb(i64 k, i64 b) {
    assert(k * b <= A);

    if (has(k * b))
        return;

    int pos = 0;
    i64 save = A;
    while (k) {
        if (k & 1) {
            require_2kb(pos, b);
            require(save, b << pos);
            save -= b << pos;
        }

        k >>= 1;
        pos++;
    }

    require(A, save);
}

void require_akb(i64 a, i64 k, i64 b) {
    assert(k * b <= a);

    if (has(a - k * b))
        return;

    require_kb(k, b);
    require(a, k * b);
}

i64 require_gcd(i64 a, i64 b) {
    if (b == 0)
        return a;
    if (a < b)
        return require_gcd(b, a);

    require_akb(a, a / b, b);
    return require_gcd(b, a % b);
}

int main() {
    scanf("%lld%lld%lld", &A, &B, &C);
    if (A < B)
        swap(A, B);
    database.insert(A);
    database.insert(B);

    if (A == C || B == C)
        printf("0\n");
    else if (C > max(A, B))
        printf("-1\n");
    else {
        i64 r = require_gcd(A, B);
        if (C % r > 0)
            printf("-1\n");
        else {
            require_kb(C / r, r);

            printf("%zu\n", command.size());
            for (size_t i = 0; i < command.size(); i++) {
                printf("%lld %lld\n",
                       command[i].first, command[i].second);
            }
        }
    }

    return 0;
}
