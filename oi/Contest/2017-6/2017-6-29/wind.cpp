#include <cstdio>
#include <cstring>
#include <climits>

#include <unordered_map>
#include <algorithm>

using namespace std;

#define NMAX 12

typedef unsigned long long u64;

struct State {
    State(u64 _s, u64 _t) : s(_s), t(_t) {}

    u64 s, t;
};

namespace std {
template <>
struct hash<State> {
    size_t operator()(const State &a) const {
        return (a.s << 7) ^ a.t;
    }
};
}

typedef unordered_map<State, int> DP;

static int n, m;
static int d[NMAX + 10][NMAX + 10];

inline u64 get(u64 s, int i) {
    return (s >> 3 * i) & 7;
}

inline u64 set(u64 s, int i, u64 v) {
    return (s & (~(7ULL << 3 * i))) | (v << 3 * i);
}

void show(u64 s, bool newline) {
    for (int i = 0; i <= m; s >>= 3, i++) {
        printf("%llu", s & 7);

        if (i < m)
            putchar(' ');
    }

    if (newline)
        putchar('\n');
}

template <typename T>

void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", d[i] + j);

            if (d[i][j] < 0 || d[i][j] > 4)
                d[i][j] = -1;
        }
    }
}

int main() {
    initialize();

    return 0;
}
