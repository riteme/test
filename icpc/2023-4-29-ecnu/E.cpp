#include <cctype>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <set>

using namespace std;

char buf[65536];
size_t pos = 65536;

char _getchar() {
    if (pos >= 65536) {
        pos = 0;
        fread(buf, 1, 65536, stdin);
    }
    return buf[pos++];
}

int readi() {
    int x = 0;
    char c;
    do {
        c = _getchar();
    } while (!isdigit(c));
    do {
        x = x * 10 + (c - '0');
        c = _getchar();
    } while (isdigit(c));
    return x;
}

constexpr int NMAX = 1000000;

struct ran {
    mutable int l, r, c;

    bool operator<(const ran &z) const {
        return l < z.l;
    }
};

int n, q;
int cnt[NMAX + 10];

int main() {
    // scanf("%d%d", &n, &q);
    n = readi();
    q = readi();
    cnt[1] = n;
    set<ran> S;
    S.insert({0, 0, 0});
    S.insert({1, n, 1});
    S.insert({n + 1, n + 1, 0});
    int ans = 1;
    while (q--) {
        int l, r, c;
        // scanf("%d%d%d", &l, &r, &c);
        l = readi();
        r = readi();
        c = readi();

        auto it = S.upper_bound({l, l, 0});
        it--;

        while (true) {
            auto &w = *it;
            if (l <= w.l && w.r <= r) {
                cnt[w.c] -= w.r - w.l + 1;
                if (cnt[w.c] == 0)
                    ans--;
                it = S.erase(it);
            } else if (w.l < l && l <= w.r && w.r <= r) {
                cnt[w.c] -= w.r - l + 1;
                if (cnt[w.c] == 0)
                    ans--;
                w.r = l - 1;
                it++;
            } else if (l <= w.l && w.l <= r && r < w.r) {
                cnt[w.c] -= r - w.l + 1;
                if (cnt[w.c] == 0)
                    ans--;
                w.l = r + 1;
                it++;
            } else if (w.l < l && r < w.r) {
                cnt[w.c] -= r - l + 1;
                if (cnt[w.c] == 0)
                    ans--;
                int old_r = w.r;
                w.r = l - 1;
                S.insert({r + 1, old_r, w.c});
                break;
            } else {
                break;
            }
        }

        if (cnt[c] == 0)
            ans++;
        cnt[c] += r - l + 1;
        S.insert({l, r, c});

        // printf("%d %d %d\n", l, r, c);
        // for (auto &w : S) {
        //     printf("[%d,%d,%d]", w.l, w.r, w.c);
        // }
        // puts("");

        printf("%d\n", ans);
    }
    return 0;
}
