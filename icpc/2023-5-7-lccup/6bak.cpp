#pragma optimize(3)
#pragma optimize("O3")
#pragma optimize("-O3")
#pragma optimize("Ofast")
#pragma optimize("-Ofast")
#pragma optimize("march=native")
#pragma optimize("-march=native")

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    auto search(int l, int r) -> vector<string> {
        if (l == r) {
            return {"1_9"};
        }

        vector<string> res;
        for (int m = l; m < r; m++) {
            auto A = search(l, m);
            auto B = search(m + 1, r);
            for (auto &a : A) {
                for (auto &b : B) {
                    auto s = "1" + a + b + "9";
                    res.push_back(s);
                }
            }
        }

        return res;
    }

    int n, MOD;

    using i64 = long long;

    struct val {
        i64 v = 0;
        int len = 0;
    };

    using tree = vector<val>;

    int cnt1, cnt2;
    i64 arr1[1000];
    i64 arr2[1000];
    i64 pow10[10000];

    static constexpr int nbuc = 128;
    vector<i64> buc[nbuc];

    void clear() {
        for (int i = 0; i < nbuc; i++) {
            buc[i].clear();
        }
    }

    void insert(i64 v) {
        int i = v % nbuc;
        buc[i].push_back(v);
    }

    i64 count_v(i64 v) {
        int i = v % nbuc;
        i64 ret = 0;
        for (i64 x : buc[i]) {
            if (v == x)
                ret++;
        }
        return ret;
    }

    i64 count(i64 Q) {
        i64 ret = 0;
        for (int i = 0; i < cnt2; i++) {
            if (arr2[i] <= Q)
                ret += count_v(Q - arr2[i]);
        }
        // int j = cnt2 - 1;
        // for (int i = 0; i < cnt1; i++) {
        //     while (j >= 0 && arr1[i] + arr2[j] > Q) {
        //         j--;
        //     }
        //     for (int k = 0;; k++) {
        //         int p = j - k;
        //         if (p < 0)
        //             break;
        //         if (arr1[i] + arr2[p] == Q)
        //             ret++;
        //         else
        //             break;
        //     }
        // }
        return ret;
    }

    i64 solve0(const tree &T, i64 *a, int n, int *lena, i64 *b, int m, int *lenb, i64 Q) {
        int rlen = 0;
        for (int i = 0; i < m; i++) {
            rlen += T[n + m - i].len + lenb[i];
        }

        int perm[20];
        for (int i = 0; i < n; i++) {
            perm[i] = i;
        }

        clear();
        cnt1 = 0;
        // sort(a, a + n);
        do {
            i64 v = T[0].v;
            for (int _i = 0; _i < n; _i++) {
                int i = perm[_i];
                auto &tv = T[_i + 1];
                v = ((v * pow10[lena[i]] + a[i]) % MOD * pow10[tv.len] + tv.v) % MOD;
            }
            v = v * pow10[rlen] % MOD;
            // arr1[cnt1++] = v;
            insert(v);
        } while (next_permutation(perm, perm + n));

        for (int i = 0; i < m; i++) {
            perm[i] = i;
        }

        // clear();
        cnt2 = 0;
        // sort(b, b + m);
        do {
            i64 v = 0;
            for (int _i = 0; _i < m; _i++) {
                int i = perm[_i];
                auto &tv = T[n + 1 + _i];
                v = ((v * pow10[lenb[i]] + b[i]) % MOD * pow10[tv.len] + tv.v) % MOD;
            }
            arr2[cnt2++] = v;
            // insert(v);
        } while (next_permutation(perm, perm + m));

        // sort(arr1, arr1 + cnt1);
        // sort(arr2, arr2 + cnt2);
        i64 ret = count(Q);
        ret += count(Q + MOD);
        return ret;
    }

    i64 solve(const tree &T, const vector<i64> &a, i64 Q) {
        int ts = (n + 1) / 2;
        int ret = 0;
        i64 tmp[20] = {0};
        int tmp_len[20] = {0};
        int len[20] = {0};
        for (int i = 0; i < n; i++) {
            i64 v = a[i];
            if (v == 0)
                len[i] = 1;
            while (v) {
                len[i]++;
                v /= 10;
            }
        }
        for (int S = 0; S < (1 << n); S++) {
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if ((S >> i) & 1)
                    cnt++;
            }
            if (cnt != ts)
                continue;
            int j = 0;
            for (int i = 0; i < n; i++) {
                if ((S >> i) & 1) {
                    tmp_len[j] = len[i];
                    tmp[j++] = a[i];
                }
            }
            for (int i = 0; i < n; i++) {
                if (!((S >> i) & 1)) {
                    tmp_len[j] = len[i];
                    tmp[j++] = a[i];
                }
            }
            ret += solve0(T, tmp, cnt, tmp_len, tmp + cnt, n - cnt, tmp_len + cnt, Q);
        }
        return ret;
    }

    auto parse(const string &T) {
        tree t;
        val v;
        for (char c : T) {
            if (c == '_') {
                t.push_back(v);
                v = {0, 0};
            } else {
                v.v = (v.v * 10 + (c - '0')) % MOD;
                v.len++;
            }
        }
        t.push_back(v);
        return t;
    }

    int treeOfInfiniteSouls(vector<int> &gem, int p, int target) {
        n = gem.size();
        MOD = p;
        i64 ans = 0;
        vector<i64> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = gem[i];
        }
        pow10[0] = 1;
        for (int i = 1; i < 10000; i++) {
            pow10[i] = pow10[i - 1] * 10 % MOD;
        }
        auto all_trees = search(0, n - 1);
        for (auto &T : all_trees) {
            ans += solve(parse(T), a, target);
        }
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> a = {67, 34, 92};
    int p = 474443;
    int target = 101472;
    printf("%d\n", sol.treeOfInfiniteSouls(a, p, target));
    // auto v = sol.search(0, 8);
    // printf("%zu\n", v.size());
    return 0;
}
