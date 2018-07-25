#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

#define NMAX 2500

static int n;
static bool marked[NMAX * NMAX + 10];
static vector<int> s;
static vector<int> ret;

bool check() {
    memset(marked, 0, sizeof(marked));
    s.push_back(n * (n + 1) / 2);

    for (size_t i = 1; i < s.size(); i++) {
        for (size_t j = 0; j < i; j++) {
            int delta = s[i] - s[j];

            if (marked[delta]) {
                s.pop_back();
                return false;
            }

            marked[delta] = true;
        }  // for
    }      // for

    ret = s;
    s.pop_back();
    return true;
}

bool dfs(int x, int cnt) {
    if (x >= n * (n + 1) / 2) {
        return cnt == n + 1 && check();
    } else {
        if (cnt < n + 1) {
            s.push_back(x);
            if (dfs(x + 1, cnt + 1))
                return true;
            s.pop_back();
        }

        return dfs(x + 1, cnt);
    }
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);

        s = {0};
        if (dfs(1, 2)) {
            for (auto v : ret) {
                printf("%d ", v);
            }  // foreach in s
            printf("\n");
        } else
            puts("-1");
    }  // while

    return 0;
}  // function main
