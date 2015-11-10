#include <iostream>
#include <algorithm>

using namespace std;

#define NMAX 50000

static int l, n, m;
static int stone[NMAX + 10];

int solve(int left, int right) {
    // O(NlogN)
    // Imagine k is the correct answer.

    if (right <= left) return left;  // Search ended.

    int k =
        (left + right + 1) / 2;  // Avoid death loop. For example, (4+5)/2=4.
    int last, count;
    last = count = 0;

    // O(N)
    for (int i = 1; i <= n; i++) {
        if (stone[i] - last >= k)
            last = stone[i];  // Keep this stone.
        else
            count++;  // Throw this stone and increase the count.
    }                 // for

    if (l - last < k) count++;  // Specially, we can't remove the last stone.

    // O(logN)
    if (count <= m)
        return solve(k, right);  // final answer must >= k.
    else
        return solve(left, k - 1);  // Removed too many stones.
}

int main() {
    ios::sync_with_stdio(false);

    cin >> l >> n >> m;
    for (int i = 1; i <= n; i++) { cin >> stone[i]; }  // for

    cout << solve(1, l);

    return 0;
}  // function main
