#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000

vector<int> buc[NMAX + 10];

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        int v, c;
        scanf("%d%d", &v, &c);
        buc[c].push_back(v);
    }

    bool ok = true;
    for (int i = 1; ok && i <= NMAX; i++)
        ok &= is_sorted(buc[i].begin(), buc[i].end());

    puts(ok ? "YES" : "NO");
    return 0;
}