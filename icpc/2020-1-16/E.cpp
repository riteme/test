#include <cstdio>
#include <cstring>

#include <list>
#include <algorithm>
#include <functional>

using namespace std;

#define NMAX 200000

int n, m, K;
struct item {
    int cnt, i;

    bool operator<(const item &z) const {
        return cnt > z.cnt;
    }
} c[NMAX + 10];
int a[NMAX + 10];
list<int> li;

template <typename T>
void nxt(T &it) {
    it++;
    if (it == li.end())
        it = li.begin();
}

int main() {
    scanf("%d%d%d", &n, &m, &K);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &c[i].cnt);
        c[i].i = i;
    }

    sort(c + 1, c + m + 1);
    int p = n - c[1].cnt + 1;
    int L = n / p;
    int L0 = c[1].cnt / p;
    int cnt = c[1].cnt % p;
    if (K < L)
        puts("-1");
    else {
        for (int i = 1; i <= n; i++)
            li.push_back(i);

        auto it = li.begin();
        for (int i = 1; i <= m; i++) {
            while (c[i].cnt) {
                if (a[*it - 1] == c[i].i) nxt(it);
                int R = L;
                if (i == 1) {
                    if (cnt) {
                        cnt--;
                        R = L;
                    } else R = L0;
                }
                for (int j = 0; j < R && c[i].cnt; j++, c[i].cnt--) {
                    a[*it] = c[i].i;
                    it = li.erase(it);
                    if (it == li.end()) it = li.begin();
                }
            }
        }

        for (int i = 1; i <= n; i++)
            printf("%d ", a[i]);
        puts("");
    }

    return 0;
}