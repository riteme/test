#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>

using namespace std;

#define LMAX 1000000
#define MOD 1000000007L

typedef long long ntype;

static ntype n;
static char s[LMAX + 10];
static ntype prefix[LMAX + 10];
static ntype next[LMAX + 10];
static ntype cnt[LMAX + 10];

int main() {
    scanf("%lld", &n);

    for (ntype c = 0; c < n; c++) {
        scanf("%s", s + 1);

        ntype answer = 1;
        prefix[0] = prefix[1] = 0;
        cnt[0] = -1;
        cnt[1] = 0;
        for (int i = 2; s[i] != '\0'; i++) {
            ntype k = prefix[i - 1];
            while (k != 0 && s[i] != s[k + 1]) {
                k = prefix[k];
            }  // while

            if (s[k + 1] == s[i]) {
                k++;
            }

            prefix[i] = k;
            cnt[i] = cnt[k] + 1;
        }  // for

        next[0] = next[1] = 0;
        for (int i = 2; s[i] != '\0'; i++) {
            ntype k = next[i - 1];
            if (k + 1 > i / 2) {
                k = prefix[k];
            }

            while (k != 0 && s[k + 1] != s[i]) {
                k = prefix[k];
            }  // while

            if (s[k + 1] == s[i]) {
                k++;
            }

            next[i] = k;
            answer *= cnt[next[i]] + 2;
            answer %= MOD;
        }  // for

        printf("%lld\n", answer);
    }  // for

    return 0;
}  // function main
