#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

static char str[NMAX + 10];
static int fail[NMAX + 10];
static int cnt[NMAX + 10];

int main() {
    freopen("passward.in", "r", stdin);
    freopen("passward.out", "w", stdout);
    scanf("%s", str + 1);
    int n = strlen(str + 1);

    fail[1] = 0;
    cnt[0] = 1;
    int j = 0;
    for (int i = 2; i <= n; i++) {
        while (j > 0 && str[j + 1] != str[i])
            j = fail[j];

        if (str[j + 1] == str[i])
            j++;

        fail[i] = j;
        cnt[j]++;
    }

    int answer;
    if (cnt[fail[n]] > 1)
        answer = fail[n];
    else
        answer = fail[fail[n]];

    if (answer == 0)
        puts("Just a legend");
    else {
        str[answer + 1] = '\0';
        puts(str + 1);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}
