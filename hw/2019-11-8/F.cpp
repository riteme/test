#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    priority_queue<int, vector<int>, greater<int>> q;
    int n, K;
    scanf("%d%d", &n, &K);
    for (int i = 1; i <= n; i++) {
        int v;
        scanf("%d", &v);
        q.push(v);
    }
    int mi = 0;
    while (K--) {
        if (q.empty()) puts("0");
        else {
            int v = q.top();
            q.pop();
            if (v == mi) {
                K++;
                continue;
            }
            printf("%d\n", v - mi);
            mi = v;
        }
    }
    return 0;
}
