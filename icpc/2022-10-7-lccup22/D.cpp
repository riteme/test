#include <bits/stdc++.h>

using namespace std;

constexpr int INF = 0x3f3f3f3f;

class Solution {
public:
    // helloleetcode
    // h1 e4 l3 o2 t1 c1 d1
    int h[9][1 << 8];

    void chkmin(int &a, int b) {
        if (a > b)
            a = b;
    }

    static int bit(int S, int i) {
        return (S >> i) & 1;
    }

    static int mask(int n, int b) {
        return ((1 << n) - 1) << b;
    }

    struct id {
        int h, e, l, o, t, c, d;

        id() {}
        id(int S) {
            h = bit(S, 0);
            e = bit(S, 1) + bit(S, 2) + bit(S, 3) + bit(S, 4);
            l = bit(S, 5) + bit(S, 6) + bit(S, 7);
            o = bit(S, 8) + bit(S, 9);
            t = bit(S, 10);
            c = bit(S, 11);
            d = bit(S, 12);
        }

        bool check() const {
            return
                // h <= 1 &&
                // e <= 4 &&
                // l <= 3 &&
                // o <= 2 &&
                // t <= 1 &&
                // c <= 1 &&
                // d <= 1;
                h >= 0 &&
                e >= 0 &&
                l >= 0 &&
                o >= 0 &&
                t >= 0 &&
                c >= 0 &&
                d >= 0;
        }

        explicit operator int() const {
            return
                mask(h, 0) |
                mask(e, 1) |
                mask(l, 5) |
                mask(o, 8) |
                mask(t, 10) |
                mask(c, 11) |
                mask(d, 12);
        }
    };

    vector<string> words;

    int f[1 << 13];
    int g[1 << 13];

    // int dp(int n, int S) {
    //     if (n <= 0)
    //         return f[0][S];
    //     if (f[n][S] < INF)
    //         return f[n][S];

    //     int ans = INF;
    //     int m = words[n - 1].size();
    //     id q(S);
    //     for (int T = 0; T < (1 << m); T++) {
    //         id p = q;
    //         bool extra = false;
    //         for (int i = 0; i < m; i++) {
    //             if ((T >> i) & 1) {
    //                 char c = words[n - 1][i];
    //                 switch (c) {
    //                     case 'h': p.h++; break;
    //                     case 'e': p.e++; break;
    //                     case 'l': p.l++; break;
    //                     case 'o': p.o++; break;
    //                     case 't': p.t++; break;
    //                     case 'c': p.c++; break;
    //                     case 'd': p.d++; break;
    //                     default: extra = true; goto out;
    //                 }
    //             }
    //         }
    //         out:
    //         if (!extra && p.check())
    //             chkmin(ans, dp(n - 1, int(p)) + h[m][T]);
    //     }
    //     f[n][S] = ans;
    //     return ans;
    // }

    int Leetcode(vector<string>& words) {
        this->words = words;
        memset(h, 0x3f, sizeof(h));
        for (int n = 1; n <= 8; n++) {
            h[n][0] = 0;
            for (int S = 0; S < (1 << n); S++) {
                for (int i = 0; i < n; i++) {
                    if ((S >> i) & 1)
                        continue;
                    int l = 0, r = 0;
                    for (int j = 0; j < i; j++) {
                        if (!((S >> j) & 1))
                            l++;
                    }
                    for (int j = i + 1; j < n; j++) {
                        if (!((S >> j) & 1))
                            r++;
                    }
                    chkmin(h[n][S | (1 << i)], h[n][S] + l * r);
                }
            }
        }

        memset(f, 0x3f, sizeof(f));
        id all;
        all.h = 1;
        all.e = 4;
        all.l = 3;
        all.o = 2;
        all.t = 1;
        all.c = 1;
        all.d = 1;
        f[int(all)] = 0;

        for (int n = 0; n < (int)words.size(); n++) {
        memset(g, 0x3f, sizeof(g));
        for (int S = 0; S < (1 << 13); S++) {
            if (f[S] >= INF)
                continue;
            int m = words[n].size();
            id q(S);
            for (int T = 0; T < (1 << m); T++) {
                id p = q;
                bool extra = false;
                for (int i = 0; i < m; i++) {
                    if ((T >> i) & 1) {
                        char c = words[n][i];
                        switch (c) {
                            case 'h': p.h--; break;
                            case 'e': p.e--; break;
                            case 'l': p.l--; break;
                            case 'o': p.o--; break;
                            case 't': p.t--; break;
                            case 'c': p.c--; break;
                            case 'd': p.d--; break;
                            default: extra = true; goto out;
                        }
                    }
                }
                out:
                if (!extra && p.check())
                    chkmin(g[int(p)], f[S] + h[m][T]);
            }
        }
        memcpy(f, g, sizeof(f));
        }

        int ans = f[0];
        return ans < INF ? ans : -1;
    }
};

int main() {
    vector<string> words =
    // {"hold","engineer","cost","level"};
    {"hellolll","leetcode","leetcode","leetcode",
    "leetcode","leetcode","leetcode","leetcode","leetcode",
    "leetcode","leetcode","leetcode","leetcode","leetcode",
    "leetcode","leetcode","leetcode","leetcode","leetcode",
    "leetcode","leetcode","leetcode","leetcode","leetcode"};
    printf("%d\n", Solution().Leetcode(words));
};
