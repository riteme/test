#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    struct ran {
        mutable int l, r;

        bool contain(int i) const {
            return l <= i && i <= r;
        }

        bool operator<(const ran &z) const {
            return l < z.l;
        }
    };

    using seq = set<ran>;

    void setbit(seq &S, int i, int v) {
        auto it = S.upper_bound({i, i});
        it--;
        auto &z = *it;

        if (z.contain(i)) {
            if (v == 0) {
                int r = z.r;
                z.r = i - 1;
                if (z.l > z.r)
                    S.erase(it);
                if (i < r)
                    S.insert({i + 1, r});
            }
        } else if (v == 1) {
            if (z.r + 1 == i) {
                z.r++;
                it++;
                auto &y = *it;
                if (z.r + 1 == y.l) {
                    z.r = y.r;
                    S.erase(it);
                }
            } else {
                it++;
                auto &y = *it;
                if (i + 1 == y.l) {
                    y.l--;
                } else {
                    S.insert({i, i});
                }
            }
        }
    }

    int n;

    int tail(seq &S) {
        auto it = S.rbegin();
        it++;
        if (it->r == n - 1)
            return it->r - it->l + 1;
        return 0;
    }

    int getNandResult(int k, vector<int> &arr, vector<vector<int>> &operations) {
        n = arr.size();
        seq S[30];
        for (int j = 0; j < k; j++) {
            S[j].insert({-10, -10});
            S[j].insert({n + 10, n + 10});
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k; j++) {
                int v = (arr[i] >> j) & 1;
                // printf("%d", v);
                setbit(S[j], i, v);
            }
            // puts("");
        }

        // for (int j = 0; j < k; j++) {
        //     printf("%d\n", tail(S[j]));
        // }

        int ret = 0;
        for (auto &q : operations) {
            int op = q[0];
            int x = q[1];
            int y = q[2];

            if (op == 0) {
                for (int j = 0; j < k; j++) {
                    int v = (y >> j) & 1;
                    setbit(S[j], x, v);
                }
            } else {
                int ans = 0;
                for (int j = 0; j < k; j++) {
                    int v = (y >> j) & 1;
                    int c = tail(S[j]);
                    if (c < n) {
                        v = (c + 1) % 2;
                    } else {
                        v = (x % 2 * c + v) % 2;
                    }
                    ans |= v << j;
                }
                ret ^= ans;
            }
        }

        return ret;
    }
};

int main() {
    Solution sol;
    vector<int> a = {4, 6, 4, 7, 10, 9, 11};
    vector<vector<int>> b = {{1, 5, 7}, {1, 7, 14}, {0, 6, 7}, {1, 6, 5}};
    int ret = sol.getNandResult(4, a, b);
    printf("%d\n", ret);
    return 0;
}
