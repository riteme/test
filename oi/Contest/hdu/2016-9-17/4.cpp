// Fuck

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long int64;

int main() {
    int64 a, b;

    while (scanf("%lld%lld", &a, &b) != EOF) {
        if (b <= 1)
            printf("0\n");
        else if (a == b && a <= 2)
            printf("1\n");
        else if (a == b)
            printf("2\n");
        else if (a == 0 && b == 2)
            printf("1\n");
        else if (a == 1 && b == 2)
            printf("1\n");
        else {
            int64 s;
            if (a > 1)
                s = (a - 1) + 2;
            else
                s = 2;

            // printf("%lld\n", s);

            // if (b - s <= 1.0)
            //     printf("1\n");
            /*else*/ if (b - s - 1 <= 1.0)
                printf("2\n");
            else {
                int64 remain = b - s - 1;
                int64 t = 2 + remain / 2 + (remain % 2 > 1 ? 1 : 0);

                printf("%lld\n", t);
            }
        }
    }  // while

    return 0;
}  // function main
