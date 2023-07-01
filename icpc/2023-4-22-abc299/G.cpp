#include <cstdio>
#include <cstring>

#include <algorithm>
#include <map>

using namespace std;

constexpr int NMAX = 200000;

int n, m;
int a[NMAX + 10];
int cnt[NMAX + 10];
int p[NMAX + 10];
bool has[NMAX + 10];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        cnt[a[i]]++;
    }

    int l = 0, r = 1;
    map<int, int> b;
    b[a[1]]++;
    for (int i = 1; i <= m; i++) {
        while (r < n) {
            int v = a[r];
            if (has[v] || cnt[v] > 1) {
                cnt[v]--;
                r++;
                if (!has[a[r]])
                    b[a[r]]++;
            } else {
                break;
            }
        }

        int v = b.begin()->first;
        p[i] = v;
        has[v] = true;
        b.erase(b.begin());

        while (a[l] != v) {
            if (l > 0 && !has[a[l]]) {
                b[a[l]]--;
                if (b[a[l]] <= 0)
                    b.erase(a[l]);
            }
            l++;
        }
    }

    for (int i = 1; i <= m; i++) {
        printf("%d ", p[i]);
    }
    puts("");

    return 0;
}
