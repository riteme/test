#include <cstdio>

static int n;
static int seq[100];

static int dfs(int x) {
    if (x == 0) {
        for (int i = 2; i <= n - 1; i++) {
            if (seq[i - 1] == 0 && seq[i] == 1 && seq[i + 1] == 0)
                return 0;
        }  // for

        return 1;
    }

    int answer = 0;
    seq[x] = 1;
    answer += dfs(x - 1);
    seq[x] = 0;
    answer += dfs(x - 1);

    return answer;
}

int main() {
    scanf("%d", &n);

    printf("%d", dfs(n));

    return 0;
}  // function main
