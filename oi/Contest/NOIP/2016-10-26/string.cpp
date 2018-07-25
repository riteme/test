#pragma GCC optimize(3)

#define NDEBUG

#include <cassert>
#include <cstring>
#include <cstdio>

#include <vector>
#include <algorithm>

using namespace std;

typedef long long int64;

#define NMAX 5000

static int n, k;
static char str[NMAX + 10];
static int nxt[NMAX + 10];
static int num[NMAX + 10];

static void initialize() {
    scanf("%s", str + 1);
    scanf("%d", &k);
    n = strlen(str + 1);
}

static int evaluate(int s) {
    nxt[0] = nxt[1] = 0;
    int j = 0;
    for (int i = 2; i <= n - s + 1; i++) {
        while (str[s + j] != str[s + i - 1]) {
            j = nxt[j];
            
            if (j == 0)
                break;
        }

        if (str[s + j] == str[s + i - 1])
            j++;

        nxt[i] = j;
    }

    int answer = 0;
    num[0] = num[1] = 0;
    j = 0;
    for (int i = 2; i <= n - s + 1; i++) {
        while (str[s + j] != str[s + i - 1]) {
            j = nxt[j];
            
            if (j == 0)
                break;
        }

        if (str[s + j] == str[s + i - 1])
            j++;

        int limit;
        
        if (i & 1)
            limit = i / 2;
        else
            limit = i / 2 - 1;

        while (j > limit)
            j = nxt[j];

        if (j >= k)
            answer++;
        num[i] = j;
    }

    return answer;
}

int main() {
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    initialize();

    int answer = 0;

    for (int i = 1; i <= n; i++)
        answer += evaluate(i);

    printf("%d\n", answer);

    fclose(stdin);
    fclose(stdout);
    return 0;
}
