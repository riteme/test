#include <cstdio>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n, k;
static int num[NMAX + 10];
static priority_queue<int> q;
static unordered_map<int, int> m;

static void initialize() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", num + i);
    }  // for
}

inline void update(int i, int offest) {
    auto iter = m.find(i);

    if (iter == m.end())
        m[i] = offest;
    else
        iter->second += offest;
}

int main() {
    initialize();

    num[0] = -1;
    for (int i = 1; i <= n; i++) {
        update(num[i - 1], -1);

        int max_group = -1;
        for (int j = i; j <= n; j++) {
            update(num[j], 1);

            if (m[num[j]] > m[max_group]) {
                max_group = num[j];
            }
        }  // for
    }      // for

    return 0;
}  // function main
