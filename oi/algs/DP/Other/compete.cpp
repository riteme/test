// What the fuck

#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 50
#define FMAX 300000

typedef long long ntype;

static ntype n;
static ntype s[NMAX + 10];
static ntype f[FMAX + 10];

int main() {
    ios::sync_with_stdio(false);

    cin >> n;

    ntype tmp = 0;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        tmp += s[i];
    }

    ntype sum = 0;
    ntype bound = tmp / 2;

    memset(f, 0, sizeof(f));
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        if (sum < bound) sum += s[i];

        for (ntype j = std::min(sum, bound); j >= s[i]; j--) {
            f[j] += f[j - s[i]];
        }  // for
    }      // for

    cout << f[bound] / 2;

    return 0;
}  // function main
