#include <cstdio>
#include <cstring>

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

using i64 = long long;
constexpr int MAXA = 1000;

vector<i64> bs[MAXA + 1];

void solve(int n) {
    if (n == 1) {
        puts("Yes\n1");
        return;
    }
    if (n == 2) {
        puts("No");
        return;
    }

    set<i64> S = {2, 3, 6};
    while ((int)S.size() < n) {
        // for (i64 a : S) {
        //     printf("%lld ", a);
        // }
        // puts("");
        for (auto it = S.begin(); it != S.end(); it++) {
            i64 a = *it;
            if (a > MAXA)
                break;
            // printf("a=%lld\n", a);
            bool done = false;
            for (i64 b : bs[a]) {
                //     printf("a=%lld, b=%lld\n", a, b);
                i64 x = b;
                i64 y = a * b / (b - a);
                if (x != y && !S.count(x) && !S.count(y)) {
                    // printf("%lld -> %lld %lld\n", a, x, y);
                    S.erase(it);
                    S.insert(x);
                    S.insert(y);
                    done = true;
                    break;
                }
            }
            // printf("done=%d\n", done);
            if (done)
                break;
        }
    }

    puts("Yes");
    for (i64 a : S) {
        printf("%lld ", a);
    }
    puts("");
}

int main() {
    for (i64 a = 2; a <= MAXA; a++) {
        for (i64 b = a + 1; b < 1000; b++) {
            if (b * a % (b - a) == 0) {
                bs[a].push_back(b);
            }
        }
    }

    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        solve(n);
    }
    return 0;
}
