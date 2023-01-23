#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 100000;
constexpr int CMAX = 26;

int n;
char s[NMAX + 10];
int cnt[CMAX];
int a[CMAX];
vector<int> pos[CMAX];

void solve() {
    int best = n + 1;
    int best_k = 0;
    for (int k = 1; k <= CMAX; k++) {
        if (n % k != 0)
            continue;
        int f = n / k;
        int cost = 0;
        for (int i = 1; i <= k; i++) {
            cost += max(0, cnt[CMAX - i] - f);
        }
        for (int i = 0; i < CMAX - k; i++) {
            cost += cnt[i];
        }
        if (cost < best) {
            best = cost;
            best_k = k;
        }
    }

    int k = best_k;
    int f = n / k;

    auto donate = [&](int i) {
        int j = CMAX - k;
        while (cnt[j] >= f) {
            j++;
        }

        int ci = a[i];
        int cj = a[j];

        int p = pos[ci].back();
        pos[ci].pop_back();
        s[p] = 'a' + cj;

        cnt[i]--;
        cnt[j]++;
    };

    for (int i = 0; i < CMAX - k; i++) {
        while (cnt[i] > 0) {
            donate(i);
        }
    }
    for (int i = 1; i <= k; i++) {
        while (cnt[CMAX - i] > f) {
            donate(CMAX - i);
        }
    }

    printf("%d\n%s\n", best, s + 1);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%s", &n, s + 1);
        for (int c = 0; c < CMAX; c++) {
            pos[c].clear();
            a[c] = c;
            cnt[c] = 0;
        }
        for (int i = 1; i <= n; i++) {
            int c = s[i] - 'a';
            cnt[c]++;
            pos[c].push_back(i);
        }
        sort(a, a + CMAX, [](int x, int y) {
            return cnt[x] < cnt[y];
        });
        sort(cnt, cnt + CMAX);
        solve();
    }
    return 0;
}
