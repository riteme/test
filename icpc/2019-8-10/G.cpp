#include <cstdio>
#include <cstring>

#include <deque>
#include <algorithm>

using namespace std;

#define NMAX 100000

static char s[NMAX + 10];

int main() {
    scanf("%s", s);
    deque<char> stk;
    int ans = 0;
    for (int i = 0; s[i]; i++) {
        stk.push_front(s[i]);
        if (stk.size() >= 3 && stk[0] == stk[1] && stk[1] == stk[2]) {
            ans++;
            stk.pop_front();
            stk.pop_front();
            stk.pop_front();
        }
    }
    printf("%d\n", ans);
    return 0;
}
