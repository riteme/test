/**
 * 显然这个最小体积就是gcd
 * 但是我怎么没想到直接分解因子来算呢......
 */

#include <cstdio>

#include <map>
#include <algorithm>

using namespace std;

static int n, k;
static map<int, int> cnt;

int main() {
    scanf("%d%d", &n, &k);

    for (int i = 0; i < n; i++) {
        int u;
        scanf("%d", &u);

        for (int d = 1; d * d <= u; d++) {
            if (u % d == 0) {
                cnt[d]++;
                
                if (u / d != d)
                    cnt[u / d]++;
            }
        }
    }

    int answer = 1;
    for (map<int, int>::iterator beg = cnt.begin();
         beg != cnt.end(); beg++) {
        if (beg->second >= k)
            answer = max(answer, beg->first);
    }

    printf("%d\n", answer);

    return 0;
}
