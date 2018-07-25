#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define NMAX 10000

typedef long long int64;

static size_t pos;
static int64 target[NMAX + 10];

int main() {
    int64 a = 1;
    do {
        int64 b = 1;
        do {
            int64 c = 1;
            do {
                int64 d = 1;
                do {
                    target[pos++] = a * b * c * d;

                    if (a * b * c * d > 1000000000)
                        break;
                } while (d *= 7);  // do ... while
                if (a * b * c > 1000000000)
                    break;
            } while (c *= 5);  // do ... while
            if (a * b > 1000000000)
                break;
        } while (b *= 3);  // do ... while
        if (a > 1000000000)
            break;
    } while (a <<= 1);  // do ... while

    sort(target, target + pos);

    int t;
    scanf("%d", &t);
    while (t--) {
        int x;
        scanf("%d", &x);

        int64 *iter = lower_bound(target, target + pos, x);
        printf("%lld\n", *iter);
    }  // while

    return 0;
}  // function main
