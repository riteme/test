// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <stack>
#include <algorithm>

using namespace std;

#define NMAX 100000

static stack<char> stk, cur;
static int n;
static char s[NMAX + 10];
static bool tmp[NMAX + 10];
static bool right[NMAX + 10];

void build(int l) {
    for (int i = l; i <= n; i++) {
        if (!stk.empty() && s[i] == stk.top()) {
            stk.pop();
            tmp[i] = true;
        } else {
            stk.push(s[i]);
            tmp[i] = false;
        }
    }
}

void initialize() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
}

int main() {
#ifdef USE_FILE_IO
    freopen("match.in", "r", stdin);
    freopen("match.out", "w", stdout);
#endif
    initialize();
    build(1);
    if (!stk.empty())
        puts("-1");
    else {
        memcpy(right, tmp, sizeof(right));

        for (int i = 1; i <= n; i++) {
            if (right[i]) {
                stk = cur;
                stk.push(s[i]);
                memcpy(tmp, right, sizeof(tmp));
                build(i + 1);

                if (stk.empty()) {
                    cur.push(s[i]);
                    right[i] = false;
                    memcpy(right + i + 1, tmp + i + 1, sizeof(bool) * (n - i));
                } else {
                    assert(!cur.empty());
                    assert(cur.top() == s[i]);
                    cur.pop();
                }
            } else
                cur.push(s[i]);
        }

        for (int i = 1; i <= n; i++) {
            putchar(right[i] ? ')' : '(');
        }
        putchar('\n');
    }

    return 0;
}
