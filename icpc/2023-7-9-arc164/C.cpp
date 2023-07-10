#include <cstdio>
#include <cstring>

#include <algorithm>
#include <set>

using namespace std;

using i64 = long long;

int main() {
    int n;
    scanf("%d", &n);
    multiset<i64> Q;
    i64 S = 0;
    for (int i = 0; i < n; i++) {
        i64 A, B;
        scanf("%lld%lld", &A, &B);
        S += A;
        Q.insert(B - A);
    }
    while (Q.size()) {
        i64 v = *Q.begin();
        S += v;
        Q.erase(Q.begin());
        Q.insert(-v);

        Q.erase(Q.begin());
    }

    printf("%lld\n", S);
    return 0;
}
