/******************************************************************/
/* ACM ICPC 2017-2018                                             */
/* NEERC - Northern Eurasia Finals                                */
/* St Petersburg - Barnaul - Tbilisi - Almaty, December 3, 2017   */
/******************************************************************/
/* Problem G. The Great Wall                                      */
/*                                                                */
/* Original idea         Vitaliy Aksenov                          */
/* Problem statement     Vitaliy Aksenov                          */
/* Test set              Vitaliy Aksenov                          */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Niyaz Nigmatullin                        */
/******************************************************************/

#include <bits/stdc++.h>

using namespace std;

void calcSumLen(vector<long long> &s, vector<int> &a, int len) {
    int n = (int) a.size();
    long long cur = 0;
    for (int i = n - 1; i >= 0; i--) {
        cur += a[i];
        if (i + len < n) cur -= a[i + len];
        s[i] = cur;
    }
    s.resize(n - len + 1);
}

struct Fenwick {
    vector<long long> const &a;
    vector<int> f;
    int n;

    Fenwick(vector<long long> const &a) : a(a), f(a.size()), n((int) a.size()) {}

    void set(int x, int y) {
        for (int i = x; i < n; i |= i + 1) {
            f[i] += y;
        }
    }

    int getCount(long long y) {
        int ans = 0;
        int start = (int) (lower_bound(a.begin(), a.end(), y) - a.begin());
        for (int i = start - 1; i >= 0; i = (i & (i + 1)) - 1) {
            ans += f[i];
        }
        return ans;
    }

};


int main() {
    ios_base::sync_with_stdio(false);
    int n, L;
    long long k;
    cin >> n >> L >> k;
    n = n - L + 1;
    vector<int> a(n + L - 1);
    long long sum = 0;
    for (int i = 0; i < n + L - 1; i++) {
        cin >> a[i];
        sum += a[i];
    }
    vector<int> b(n + L - 1);
    for (int i = 0; i < n + L - 1; i++) {
        cin >> b[i];
        b[i] -= a[i];
    }
    vector<int> c(n + L - 1);
    long long MAX = 0;
    for (int i = 0; i < n + L - 1; i++) {
        cin >> c[i];
        c[i] -= a[i];
        MAX += c[i];
    }
    vector<int> cb(n + L - 1);
    for (int i = 0; i < n + L - 1; i++) {
        cb[i] = c[i] - b[i];
    }
    vector<long long> sb(n + L - 1);
    calcSumLen(sb, b, L);
    vector<long long> cover(n + L - 1);
    calcSumLen(cover, cb, L);
    vector<long long> delta(n);
    for (int i = 0; i < n; i++) delta[i] = 2 * b[i] - c[i];
    for (int i = 1; i < n; i++) {
        delta[i] += delta[i - 1];
        cover[i] -= delta[i - 1];
    }
    long long left = -1;
    long long right = MAX + 1;
    vector<long long> coverSorted(cover.begin(), cover.end());
    sort(coverSorted.begin(), coverSorted.end());
    coverSorted.erase(unique(coverSorted.begin(), coverSorted.end()), coverSorted.end());
    vector<long long> sbSorted(sb.begin(), sb.end());
    sort(sbSorted.begin(), sbSorted.end());
    sbSorted.erase(unique(sbSorted.begin(), sbSorted.end()), sbSorted.end());
    vector<int> where(n), whereB(n);
    for (int i = 0; i < n; i++) {
        where[i] = (int) (lower_bound(coverSorted.begin(), coverSorted.end(), cover[i]) - coverSorted.begin());
        whereB[i] = (int) (lower_bound(sbSorted.begin(), sbSorted.end(), sb[i]) - sbSorted.begin());
    }
    while (left < right - 1) {
        long long mid = (left + right) >> 1;
        long long count = 0;
        Fenwick tree(coverSorted);
        Fenwick treePrev(sbSorted);
        for (int i = 0; i < n; i++) {
            long long current = sb[i] + (i == 0 ? 0 : delta[i - 1]);
            count += tree.getCount(mid - current);
            count += treePrev.getCount(mid - sb[i]);
            if (count >= k) break;
            tree.set(where[i], 1);
            if (i >= L) {
                tree.set(where[i - L], -1);
                treePrev.set(whereB[i - L], 1);
            }
        }
        if (count >= k) {
            right = mid;
        } else {
            left = mid;
        }
    }
    cout << left + sum << endl;
}

