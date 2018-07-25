#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 1000000

typedef long long int64;

static int n;
static char str[NMAX + 10];
static int fail[NMAX + 10];
static int64 size[NMAX + 10];

int main() {
    scanf("%s", str + 1);
    n = strlen(str + 1);

    int j = 0;
    for (int i = 2; i <= n; i++) {
        while (j && str[j + 1] != str[i])
            j = fail[j];

        if (str[i] == str[j + 1])
            j++;

        fail[i] = j;
    }  // for

    int64 answer = 0;
    for (int i = n; i >= 1; i--) {
        size[i]++;
        answer = max(answer, i * size[i]);

        if (fail[i])
            size[fail[i]] += size[i];
    }  // for

    printf("%lld\n", answer);

    return 0;
}  // function main
x
