#include <cstdio>
#include <cassert>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 100000;

struct op {
    int i, a, j, b;
};

int n;
vector<int> h[3][3];
// vector<int> q[3];
int cnt[NMAX][3];
vector<op> o;

int chr(char c) {
    switch (c) {
        case 'w': return 0;
        case 'i': return 1;
    }
    return 2;
}

int inv(int c) {
    switch (c) {
        case 0: return 'w';
        case 1: return 'i';
    }
    return 'n';
}

bool check() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            if (cnt[i][j] != 1)
                return false;
        }
    }
    return true;
}

bool test(int a, int i, int j) {
    if (cnt[a][i] < 2 || cnt[a][j] > 0) {
        h[i][j].pop_back();
        return false;
    }
    return true;
}

bool twin() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) if (j != i && h[i][j].size() && h[j][i].size()) {
            int a = h[i][j].back();
            int b = h[j][i].back();
            assert(a != b);
            if (!test(a, i, j) || !test(b, j, i))
                return false;

            h[i][j].pop_back();
            h[j][i].pop_back();
            o.push_back({a, i, b, j});
            cnt[a][i]--;
            cnt[a][j]++;
            cnt[b][i]++;
            cnt[b][j]--;
            return true;
        }
    }
    return false;
}

bool cycle() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) if (j != i && h[i][j].size()) {
            for (int k = 0; k < 3; k++) if (k != i && k != j && h[j][k].size() && h[k][i].size()) {
                int a = h[i][j].back();
                int b = h[j][k].back();
                int c = h[k][i].back();
                assert(a != b && b != c && a != c);
                if (!test(a, i, j) || !test(b, j, k) || !test(c, k, i))
                    return false;

                h[i][j].pop_back();
                h[j][k].pop_back();
                h[k][i].pop_back();
                o.push_back({a, i, b, j});
                o.push_back({b, i, c, k});
                cnt[a][i]--;
                cnt[a][j]++;
                cnt[b][j]--;
                cnt[b][k]++;
                cnt[c][k]--;
                cnt[c][i]++;
                return true;
            }
        }
    }

    return false;
}

void solve() {
    o.clear();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            h[i][j].clear();
        }
    }
    memset(cnt, 0, sizeof(int) * n * 3);

    char s[4];
    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        for (int j = 0; j < 3; j++) {
            cnt[i][chr(s[j])]++;
        }

        for (int j = 0; j < 3; j++) {
            if (cnt[i][j] > 1) {
                for (int l = 0; l < 3; l++) {
                    if (j != l && cnt[i][l] == 0)
                        h[j][l].push_back(i);
                }
            }
        }
    }

    while (twin()) {}
    while (cycle()) {}

    printf("%zu\n", o.size());
    for (auto &e : o) {
        printf("%d %c %d %c\n", e.i + 1, inv(e.a), e.j + 1, inv(e.b));
    }

    assert(check());
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        solve();
    }
    return 0;
}
