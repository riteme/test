#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

typedef long long i64;

constexpr i64 ctm(i64 h, i64 m, i64 s) {
    return h * 60 * 60 + m * 60 + s;
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        if (n == 0) break;

        int cnt = 0;
        while (n--) {
            char S;
            do {
                S = getchar();
            } while (S != 'D' && S != 'E');
            i64 h1, m1, s1, h2, m2, s2;
            scanf(":%lld:%lld:%lld:%lld:%lld:%lld",
                &h1, &m1, &s1, &h2, &m2, &s2);
            i64 t1 = ctm(h1, m1, s1);
            i64 t2 = ctm(h2, m2, s2);
            if (S == 'D') {
                if (t1 > ctm(9, 30, 0))
                    cnt++;
                else {
                    t1 = max(t1, ctm(8, 30, 0));
                    i64 span = max(0LL, t2 - t1 + 1);
                    if (span < 8 * 60 * 60)
                        cnt++;
                }
            } else {
                if (t1 > ctm(12, 30, 0))
                    cnt++;
                else {
                    t1 = max(t1, ctm(8, 30, 0));
                    i64 span = max(0LL, t2 - t1 + 1);
                    if (span < 9 * 60 * 60)
                        cnt++;
                }
            }
        }

        switch (cnt) {
            case 0: puts("All OK"); break;
            case 1: puts("1 Point(s) Deducted"); break;
            case 2: puts("2 Point(s) Deducted"); break;
            case 3: puts("3 Point(s) Deducted"); break;
            default: puts("Issue Show Cause Letter"); break;
        }
    }

    return 0;
}