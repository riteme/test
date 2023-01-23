#include <cstdio>
#include <cstring>

#include <vector>

using namespace std;

using op = pair<int, int>;

auto solve(int n) -> vector<op> {
    if (n == 2)
        return {};

    if (n == 3 || n == 4) {
        return {
            {1, 3},
        };
    }

    if (n == 5 || n == 6) {
        return {
            {1, 5},
            {2, 3},
            {1, 5},
        };
    }

    int m = n + n % 2;
    int no = m / 2;

    vector<op> A;
    if (no % 2 == 1) {
        m += 2;
        A.push_back({1, n - 1 + n % 2});
        for (int a = 5, b = n - 3 + n % 2; a < b; a += 2, b -= 2) {
            A.push_back({a, b});
        }
        A.push_back({3, 6});
        A.push_back({3, 9});
    } else {
        for (int a = 1, b = n - 1 + n % 2; a < b; a += 2, b -= 2) {
            A.push_back({a, b});
        }
    }

    for (auto &p : solve(m / 2)) {
        A.push_back({p.first * 2, p.second * 2});
    }
    return A;
}

int main() {
    int n;
    scanf("%d", &n);
    auto S = solve(n);
    printf("%zu\n", S.size());
    for (auto &p : S) {
        printf("%d %d\n", p.first, p.second);
    }
    return 0;
}
