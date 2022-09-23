#include <cstdio>
#include <cstring>

#include <bitset>
#include <algorithm>

using namespace std;

using i64 = long long;

int main() {
    for (int m = 1; m <= 10000; m++) {
        printf("[%8d] ", m);
        for (int n = 0; n <= min(m, 21); n++) {
            bool ok = true;
            for (i64 S = 0; ok && S < (1ll << n); S++) {
                int cnt = 0;
                bitset<64> b;
                for (int i = 1; i <= n; i++) {
                    if ((S >> (i - 1)) & 1) {
                        cnt++;
                        for (int j = 0; j < n; j++) {
                            int a = m - j;
                            if (a % i == 0)
                                b[j] = 1;
                        }
                    }
                }

                // printf("%d %zu\n", cnt, b.count());
                if (b.count() < cnt)
                    ok = false;
            }

            putchar(ok ? '1' : '0');
            fflush(stdout);
        }
        puts("");
    }
    return 0;
}