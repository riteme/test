#include <cstdio>

#include <algorithm>
#include <bitset>

using namespace std;

int n, D;
char S[200];
bitset<128> u;

int main() {
    scanf("%d%d", &n, &D);
    for (int i = 0; i < n; i++) {
        scanf("%s", S);
        bitset<128> v;
        for (int j = 0; j < D; j++) {
            if (S[j] == 'x')
                v[j] = 1;
        }
        u |= v;
    }

    int ans = 0;
    int cnt = 0;
    for (int i = 0; i < D; i++) {
        if (!u[i])
            cnt++;
        else
            cnt = 0;
        ans = max(ans, cnt);
    }

    printf("%d\n", ans);

    return 0;
}
