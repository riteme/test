#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n;
static int seq[NMAX + 10];

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", seq + i);
    }  // for
}

int main() {
    initialize();

    int ans1 = 1;
    bool state = true;
    for (int i = 2; i <= n; i++) {
        if ((state && seq[i] < seq[i - 1]) || (!state && seq[i] > seq[i - 1])) {
            ans1++;
            state = !state;
        }
    }  // for

    int ans2 = 1;
    state = false;
    for (int i = 2; i <= n; i++) {
        if ((state && seq[i] < seq[i - 1]) || (!state && seq[i] > seq[i - 1])) {
            ans2++;
            state = !state;
        }
    }  // for

    printf("%d\n", max(ans1, ans2));

    return 0;
}  // function main
