#include <cstdio>

typedef long long i64;

#define CHECK(statement) if (statement) return true;

bool dfs(int n, int cnt, i64 F, i64 L, i64 T) {
    if (T <= n)
        return true;
    if (n == 0)
        return false;

    if (cnt) {
        CHECK(dfs(n - 1, cnt, F, L + 1, T));
        if (L > 1)
            CHECK(dfs(n - 1, cnt, F * L, L, T));
        if (F <= T)
            CHECK(dfs(n - 1, cnt - 1, 1, 0, T - F));
    }

    return false;
}

int main() {
    int n;
    i64 t;
    while (scanf("%d%lld", &n, &t) != EOF) {
        puts(dfs(n, 2, 1, 0, t) ? "YES" : "NO");
    }

    return 0;
}
