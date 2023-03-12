#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

using f128 = long double;

constexpr int C = 100;

int n;
vector<int> p1, p2;
vector<int> n1, n2;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        if (a > 0)
            p1.push_back(a);
        else
            n1.push_back(a);
    }
    sort(p1.begin(), p1.end());
    p2 = p1;
    sort(p2.begin(), p2.end(), greater<int>());
    sort(n1.begin(), n1.end());
    n2 = n1;
    sort(n2.begin(), n2.end(), greater<int>());
    if (p1.size() <= 2 * C) {
        p2.clear();
    } else {
        p1.resize(C);
        p2.resize(C);
    }
    if (n1.size() <= 2 * C) {
        n2.clear();
    } else {
        n1.resize(C);
        n2.resize(C);
    }
    auto a = p1;
    a.insert(a.end(), p2.begin(), p2.end());
    a.insert(a.end(), n1.begin(), n1.end());
    a.insert(a.end(), n2.begin(), n2.end());
    n = a.size();
    f128 mi = 1e99, mx = -1e99;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                f128 v = (a[i] + a[j] + a[k]) / (1.0L * a[i] * a[j] * a[k]);
                mi = min(mi, v);
                mx = max(mx, v);
            }
        }
    }
    printf("%.16Lf\n%.16Lf\n", mi, mx);
    return 0;
}
