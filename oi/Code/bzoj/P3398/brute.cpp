#include <cstdio>

#include <algorithm>

using namespace std;

static int n, k;

bool check(int s) {
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (c && ((s >> i) & 1))
            return false;
        if (c)
            c--;
        if ((s >> i) & 1)
            c = k;
    }

    return true;
}

int main() {
    scanf("%d%d", &n, &k);

    int answer = 0;
    for (int s = 0; s < (1 << n); s++) {
        answer += check(s) ? 1 : 0;
    }

    printf("%d\n", answer);

    return 0;
}
