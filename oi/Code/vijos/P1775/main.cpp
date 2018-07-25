#include <cstdio>
#include <cstring>

#include <algorithm>
#include <map>
#include <vector>

using namespace std;

#define NMAX 350
#define MMAX 40
#define MOD 10000007

typedef pair<int, int> IntPair;

static int n, m;
static int score[NMAX + 10];
static int cnt[10];
// static int f[NMAX + 10][MMAX + 1][MMAX + 1][MMAX + 1][MMAX + 1];
static map<int, int> f;
static vector<IntPair> table[MOD];

inline void insert(int id, int v) {
    int index = id % MOD;

    for (size_t i = 0; i < table[index].size(); i++) {
        if (table[index][i].first == id) {
            table[index][i].second = v;

            return;
        }
    }  // for

    table[index].push_back(IntPair(id, v));
}

inline int query(int id) {
    int index = id % MOD;

    for (size_t i = 0; i < table[index].size(); i++) {
        if (table[index][i].first == id)
            return table[index][i].second;
    }  // for

    return -1;
}

inline int hashing(int x, int a, int b, int c, int d) {
    return x * 100000000 + a * 1000000 + b * 10000 + c * 100 + d;
}

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%d", score + i);
    }  // for

    for (int i = 0; i < m; i++) {
        int id;
        scanf("%d", &id);

        cnt[id]++;
    }  // for
}

static int dfs(int x, int a, int b, int c, int d) {
    if (x < 1)
        return 0;
    if (x == 1)
        return score[1];
    if (a > cnt[1] || b > cnt[2] || c > cnt[3] || d > cnt[4])
        return 0;

    int id = hashing(x, a, b, c, d);
    int result = query(id);
    if (result >= 0)
        return result;
    else {
        int answer =
            max(max(dfs(x - 1, a + 1, b, c, d), dfs(x - 2, a, b + 1, c, d)),
                max(dfs(x - 3, a, b, c + 1, d), dfs(x - 4, a, b, c, d + 1)));

        insert(id, answer + score[x]);
        return answer + score[x];
    }
}

int main() {
    freopen("tortoise.in", "r", stdin);
    freopen("tortoise.out", "w", stdout);
    initialize();

    printf("%d\n", dfs(n, 0, 0, 0, 0));

    return 0;
}  // function main
