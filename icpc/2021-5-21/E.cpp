#include <cstdio>
#include <climits>
#include <cassert>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 2000000;

int n, q;
int c[NMAX + 10];
bool used[NMAX + 10];
vector<int> pos[NMAX + 10];
int buc[NMAX + 10];
int w[NMAX + 10];
vector<int> ch[NMAX + 10];

void dfs(int x) {
    if (ch[x].empty()) {
        assert(w[x] != 0);
        assert(pos[x].size() == 1);
        int p = pos[x][0];
        if (w[x] == +1)
            c[p] = 1;
        else
            c[p] = 0;
        return;
    }

    int s = +1;
    if (w[x] == -1)
        s = -1;

    int sum = 0;
    for (int v : ch[x]) {
        if (w[v] != 0) {
            w[v] *= s;
            s = -s;
        }
        dfs(v);
        sum += pos[v].size();
    }

    assert(sum == pos[x].size());
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= q; i++) {
        int k;
        scanf("%d", &k);
        pos[i].reserve(k);
        for (int j = 0; j < k; j++) {
            int x;
            scanf("%d", &x);
            pos[i].push_back(x);
        }
    }

    for (int i = q + 1; i <= q + n; i++) {
        pos[i].push_back(i - q);
    }
    int m = q + n + 1;
    pos[m].reserve(n);
    for (int i = 1; i <= n; i++) {
        pos[m].push_back(i);
    }

    sort(pos + 1, pos + m + 1, [](const vector<int> &a, const vector<int> &b) {
        return a.size() < b.size();
    });

    for (int i = 1; i <= m; i++) {
        int sum = 0;
        for (int j : pos[i]) {
            int &p = buc[j];
            if (p && used[p])
                p = 0;
            if (p) {
                used[p] = true;
                ch[i].push_back(p);
                w[i] ^= w[p];
                sum += pos[p].size();
            }
            p = i;
        }

        w[i] ^= (pos[i].size() - sum) & 1;
    }

    // for (int i = 1; i <= m; i++) {
    //     for (int j : pos[i]) {
    //         printf("%d ", j);
    //     }
    //     printf(": %d\n", w[i]);
    // }

    dfs(m);

    // for (int i = 1; i <= m; i++) {
    //     for (int j : pos[i]) {
    //         printf("%d ", j);
    //     }
    //     printf(": %d\n", w[i]);
    // }

    for (int i = 1; i <= n; i++) {
        printf("%d ", c[i]);
    }
    puts("");

    return 0;
}