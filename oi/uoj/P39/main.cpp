#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <stack>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

typedef long long i64;

#define NMAX 1000
#define MMAX 6
#define SMAX 130
#define MOD 1000000007

inline int get(int s, int i) {
    return (s >> 2 * (i - 1)) & 3;
}

inline int set(int s, int i, int v) {
    return (s & (~(3 << 2 * (i - 1)))) | (v << 2 * (i - 1));
}

template <typename T1, typename T2>
inline void add(T1 &a, const T2 b) {
    a += b;
    if (a >= MOD)
        a -= MOD;
}

static int n, m, K, q, cnt;
static bool mat[NMAX + 10][MMAX + 10];
static int state[SMAX + 10];
static unordered_map<int, int> id;

inline void show(int s, bool newline = true) {
    constexpr char mask[] = {'.', '(', ')'};
    for (int i = 0; i <= m; i++, s >>= 2) {
        putchar(mask[s & 3]);
    }

    if (newline)
        putchar('\n');
}

struct DP {
    int arr[SMAX];

    void print() {
        for (int i = 1; i <= cnt; i++) {
            if (arr[i] == 0)
                continue;

            show(state[i], false);
            printf(": %d\n", arr[i]);
        }
    }

    int &operator[](const size_t i) {
        return arr[i];
    }
};

void dfs(int s, int p, int sum) {
    if (p > m + 1) {
        if (!sum) {
            state[++cnt] = s;
            // printf("%d: ", cnt);
            // show(s);
            id[s] = cnt;
        }
    } else {
        if (sum < 0)
            return;
        s <<= 2;
        dfs(s, p + 1, sum);
        dfs(s | 1, p + 1, sum - 1);
        dfs(s | 2, p + 1, sum + 1);
    }
}

void dp(vector<DP> &dest) {
    DP cur, nxt;

    memset(&nxt, 0, sizeof(nxt));
    nxt[id[0]] = 1;
    if (!mat[1][1])
        nxt[id[9]] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < m; j++) {
            memcpy(&cur, &nxt, sizeof(cur));
            memset(&nxt, 0, sizeof(nxt));

            for (int s = 1; s <= cnt; s++) {
                int u = state[s], v;
                int val = cur[s];

                if (!val)
                    continue;

                // 不放插头
                if (!get(u, j + 1) && !get(u, j + 2))
                    add(nxt[s], val);

                if (!mat[i][j + 1]) {
                    if (get(u, j + 1) && get(u, j + 2)) {
                        // () 即形成闭合回路，不允许
                        if (get(u, j + 1) == 1 && get(u, j + 2) == 2)
                            continue;

                        // 连接两个连通分量，如果没有后续操作就是)(这种
                        v = set(u, j + 1, 0);
                        v = set(v, j + 2, 0);

                        int p = 1, k;
                        constexpr int w[] = {0, 1, -1};
                        if (get(u, j + 1) == 1 && get(u, j + 2) == 1) {
                            // (( 需要修改一个对应的右括号
                            k = j + 3;
                            for (; k <= m + 1; k++) {
                                p += w[get(u, k)];

                                if (!p)
                                    break;
                            }

                            v = set(v, k, 1);
                        } else if (get(u, j + 1) == 2 && get(u, j + 2) == 2) {
                            // )) 需要修改一个对应的左括号
                            k = j;
                            for (; k >= 1; k--) {
                                p += -w[get(u, k)];

                                if (!p)
                                    break;
                            }

                            v = set(v, k, 2);
                        }

                        add(nxt[id[v]], val);
                    } else if (get(u, j + 1) && !get(u, j + 2)) {
                        // 左侧插头
                        int c = get(u, j + 1);
                        add(nxt[s], val);
                        v = set(u, j + 1, 0);
                        v = set(v, j + 2, c);
                        add(nxt[id[v]], val);
                    } else if (!get(u, j + 1) && get(u, j + 2)) {
                        // 顶部插头
                        int c = get(u, j + 2);
                        add(nxt[s], val);
                        v = set(u, j + 2, 0);
                        v = set(v, j + 1, c);
                        add(nxt[id[v]], val);
                    } else {
                        // 新建连通分量
                        v = set(u, j + 1, 1);
                        v = set(v, j + 2, 2);
                        add(nxt[id[v]], val);
                    }
                }
            }
        }

        // 转移到下一行第一个以及去除无效状态
        memset(&cur, 0, sizeof(cur));
        for (int s = 1; s <= cnt; s++) {
            int u = state[s], v;

            if (get(u, m + 1))
                nxt[s] = 0;
            else if (i < n) {
                int val = nxt[s];
                if (!val)
                    continue;

                // 空插头
                if (!get(u, 1))
                    add(cur[id[u << 2]], val);

                if (!mat[i + 1][1]) {
                    if (!get(u, 1)) {
                        // 新建连通分量
                        v = set(u << 2, 1, 1);
                        v = set(v, 2, 2);
                        add(cur[id[v]], val);
                    } else {
                        // 延伸连通分量
                        v = u << 2;
                        add(cur[id[v]], val);
                        assert(get(u, 1) == 1);
                        v = set(v, 2, 0);
                        v = set(v, 1, 1);
                        add(cur[id[v]], val);
                    }
                }
            }
        }

        // printf("i = %d\n", i);
        // nxt.print();
        dest.push_back(nxt);
        memcpy(&nxt, &cur, sizeof(nxt));
    }
}

static vector<DP> pre, suf;
static vector<int> ok[SMAX + 10];
static bool has[MMAX * 2 + 10];
static int adj[MMAX * 2 + 10];

void walk(int x) {
    has[x] = false;

    if (adj[x] && has[adj[x]])
        walk(adj[x]);
    else if (x <= m && has[m + x])
        walk(m + x);
    else if (x > m && has[x - m])
        walk(x - m);
}

inline bool check(int u, int v) {
    memset(has, 0, sizeof(has));
    memset(adj, 0, sizeof(adj));

    stack<int> stk;
    for (int i = 1; i <= m; i++) {
        has[i] = get(u, i);

        if (get(u, i) == 1)
            stk.push(i);
        else if (get(u, i) == 2) {
            adj[stk.top()] = i;
            adj[i] = stk.top();
            stk.pop();
        }
    }

    for (int i = 1; i <= m; i++) {
        has[m + i] = get(v, i);

        if (get(v, i) == 1)
            stk.push(i);
        else if (get(v, i) == 2) {
            adj[m + stk.top()] = m + i;
            adj[m + i] = m + stk.top();
            stk.pop();
        }
    }

    for (int i = 1; i <= 2 * m; i++) {
        if (has[i] && !has[i <= m ? i + m : i - m])
            return false;
    }

    for (int i = 1; i <= 2 * m; i++) {
        if (has[i]) {
            walk(i);
            break;
        }
    }

    for (int i = 1; i <= 2 * m; i++) {
        if (has[i])
            return false;
    }
    
    return true;
}

void initialize() {
    scanf("%d%d%d", &n, &m, &K);

    for (int i = 1; i <= K; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        mat[x][y] = true;
    }

    dfs(0, 1, 0);

    dp(pre);

    for (int i = 1, j = n; i < j; i++, j--) {
        for (int k = 1; k <= m; k++) {
            swap(mat[i][k], mat[j][k]);
        }
    }

    dp(suf);

    for (int s = 1; s <= cnt; s++) {
        if (get(state[s], m + 1))
            continue;

        for (int t = 1; t <= cnt; t++) {
            if (get(state[t], m + 1))
                continue;
            if (check(state[s], state[t]))
                ok[s].push_back(t);
        }
    }
}

int main() {
    // freopen("data.in", "r", stdin);
    initialize();

    scanf("%d", &q);
    while (q--) {
        int x, y;
        scanf("%d%d", &x, &y);

        int ans = 0;
        for (int s = 1; s <= cnt; s++) {
            for (int t : ok[s]) {
                if (get(state[s], y) && get(state[t], y)) {
                    // show(state[s], false);
                    // printf(" x ");
                    // show(state[t], false);
                    // printf(": %lld\n", (i64) pre[x - 1][s] * suf[n - x - 1][t] % MOD);
                    add(ans, (i64) pre[x - 1][s] * suf[n - x - 1][t] % MOD);
                }
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}
