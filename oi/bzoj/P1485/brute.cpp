#include <cstdio>
#include <algorithm>

using namespace std;

#define NMAX 1000

static int n;
static int seq[NMAX + 10];

inline bool check() {
    for (int i = 1; i <= n * 2 - 2; i += 2) {
        if (seq[i] > seq[i + 2])
            return false;
    }  // for

    for (int i = 2; i <= n * 2 - 2; i += 2) {
        if (seq[i] > seq[i + 2])
            return false;
    }  // for

    for (int i = 1; i < n * 2; i += 2) {
        if (seq[i] > seq[i + 1])
            return false;
    }  // for

    return true;
}

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n * 2; i++) {
        seq[i] = i;
    }  // for

    int answer = 1;
    while (next_permutation(seq + 1, seq + n * 2 + 1)) {
        if (check())
            answer++;
    }  // while

    printf("%d\n", answer);

    return 0;
}  // function main
