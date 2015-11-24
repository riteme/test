#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 50
#define SMAX 5000

static int n;
static int s[NMAX + 10];
static int f[SMAX + 10];

int main() {
    ios::sync_with_stdio(false);

    cin >> n;

    int sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        sum += s[i];
    }

    int bound = sum / 2;

    std::sort(&s[1], &s[n + 1]);

    memset(f, 0, sizeof(f));

    f[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= s[i]; j++) { f[j] = f[j] + 1; }  // for
    }                                                         // for

    cout << f[bound] + 1;

    return 0;
}  // function main
