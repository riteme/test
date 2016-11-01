#include <cstdio>
#include <algorithm>

using namespace std;

#define NMAX 500000

typedef long long int64;

static int n;
static int seq[NMAX + 10];

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%d", seq + i);
}

static int stackpos;
static int stack[NMAX + 10];
static int cnt[NMAX + 10];

int main() {
    freopen("def.in", "r", stdin);
    freopen("def.out", "w", stdout);
    initialize();

    int64 answer = 0;
    stackpos = 1;
    stack[1] = seq[1];
    cnt[1] = 1;
    for (int i = 2; i <= n; i++) {
        while (stackpos > 0 && seq[i] > stack[stackpos]) {
            answer += cnt[stackpos];
            stackpos--;
        }

        if (seq[i] == stack[stackpos]) {
            answer += cnt[stackpos];

            if (stackpos > 1)
                answer++;

            cnt[stackpos]++;
        } else {
            if (stackpos > 0)
                answer++;

            stack[++stackpos] = seq[i];
            cnt[stackpos] = 1;
        }
    }

    printf("%lld\n", answer);

    fclose(stdin);
    fclose(stdout);
    return 0;
}
