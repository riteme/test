#include <cstdio>
#include <cstring>

#include <deque>
#include <algorithm>
#include <functional>

using namespace std;

typedef long long i64;

#define NMAX 200000

static int n;
static deque<i64> p, q;

i64 take() {
    i64 ret;
    if (p.empty() || (!q.empty() && p[0] > q[0])) {
        ret = q[0];
        q.pop_front();
    } else {
        ret = p[0];
        p.pop_front();
    }
    //printf("ret = %lld\n", ret);
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        i64 w;
        scanf("%lld", &w);
        p.push_back(w);
    }
    if (n % 2 == 0) {
        n++;
        p.push_back(0);
    }
    sort(p.begin(), p.end());

    i64 ans = 0;
    for ( ; n > 1; n -= 2) {
        i64 v = take() + take() + take();
        ans += v;
        q.push_back(v);
    }

    printf("%lld\n", ans);
    return 0;
}
