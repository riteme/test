#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define ll long long
ll n, m, ans;
inline ll GetAns(ll x, ll y) {
    if (x > y)
        return false;
    if (y == 0)
        return false;
    if (y == 1)
        return false;
    if (y == 2)
        return true;
    if (y == x)
        return 2;
    if (y - x == 1)
        return 2;
    if (x == 1)
        return (y + 1) / 2;
    if (x == 0)
        return (y + 1) / 2;
    int k = x <= 1 ? 1 : 2;
    if (x & 1)
        return k + (y - x) / 2 - 1;
    else
        return k + (y - x - 2) / 2;
}
inline ll max(ll x, ll y) {
    return x < y ? y : x;
}
int main() {
    while (scanf("%lld%lld", &n, &m) != EOF)
        printf("%lld\n", max(GetAns(n, m), GetAns(n, m - 1)));
    return 0;
}
