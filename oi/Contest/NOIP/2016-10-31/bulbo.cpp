#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long int64;

int main() {
    freopen("bulbo.in", "r", stdin);
    freopen("bulbo.out", "w", stdout);

    int n;
    int64 x;
    scanf("%d%lld", &n, &x);

    int64 answer = 0;
    int64 l = x, r = x;
    for (int i = 1; i <= n; i++) {
        int64 nl, nr;
        scanf("%lld%lld", &nl, &nr);

        if (max(l, nl) <= min(r, nr)) {
            l = max(l, nl);
            r = min(r, nr);
        } else if (nr < l) {
            answer += l - nr;
            r = l;
            l = nr;
        } else {
            answer += nl - r;
            l = r;
            r = nl;
        }
    }

    printf("%lld\n", answer);
    return 0;
}
