#include <cstdio>
#include <cstring>

#include <set>
#include <stack>
#include <algorithm>

using namespace std;

#define NMAX 300000

static int n;

int main() {
    scanf("%d", &n);
    char buf[16];
    int p = 1, ans = 0;
    set<int> q;
    stack<int> s;
    for (int i = 0; i < 2 * n; i++) {
        scanf("%s", buf);
        if (buf[0] == 'a') {
            int x;
            scanf("%d", &x);
            s.push(x);
        } else {
            if (!s.empty() && s.top() != p) {
                ans++;
                for ( ; !s.empty(); s.pop())
                    q.insert(s.top());
            }
            if (s.empty()) q.erase(p);
            else s.pop();
            p++;
        }
    }
    printf("%d\n", ans);
    return 0;
}
