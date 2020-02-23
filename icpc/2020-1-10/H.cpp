#include <cstdio>
#include <cstring>

#include <unordered_map>
#include <algorithm>

using namespace std;

typedef unsigned long long u64;

int main() {
    u64 C;
    scanf("%llu", &C);
    unordered_map<u64, int> mp;
    for (u64 i = 2; i <= (1ULL << 23); i++) {
        while (C % i == 0) {
            C /= i;
            mp[i] ^= 1;
        }
    }

    if (C > 1) {
        u64 l = 1, r = (1ULL << 32) - 1;
        while (l < r) {
            u64 m = (l + r) / 2;
            u64 m2 = m * m;
            if (m2 < C) l = m + 1;
            else if (m2 > C) r = m - 1;
            else l = r = m;
        }
        if (l * l != C)
            mp[C] = 1;
    }

    u64 D = 1;
    for (auto &e : mp) if (e.second)
        D *= e.first;
    printf("%llu\n", D);
    return 0;
}