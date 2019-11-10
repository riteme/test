#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

int main() {
    priority_queue<i64> q;
    int n, K;
    scanf("%d%d", &n, &K);
    while (n--) {
        i64 v;
        scanf("%lld", &v);
        q.push(v);
    }
    while (K--) {
        i64 v = q.top();
        q.pop();
        q.push(v / 2);
    }
    i64 ans = 0;
    while (!q.empty()) {
        ans += q.top();
        q.pop();
    }
    printf("%lld\n", ans);
    return 0;
}
