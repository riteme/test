#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>

using namespace std;

inline int readint() {
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while ('0' <= c && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }

    return x;
}

#define OUTPUT_BUFFER 1000000
static size_t _pos = 0;
static char _buffer[OUTPUT_BUFFER];

inline void putint(int x) {
    _pos += sprintf(_buffer + _pos, "%d\n", x);
}

#define NMAX 40000
// #define NMAX 100

#define NOT_DETERMINED 0
#define SELECTED 1
#define NOT_SELECTED 2

struct Queue {
    int head, tail;
    int items[NMAX + 10];

    void reset() {
        head = tail = 0;
    }

    int front() const {
        return items[head];
    }

    bool empty() const {
        return head == tail;
    }

    void push(int x) {
        items[tail++] = x;
    }

    void pop() {
        head++;
    }
};  // struct Queue

static int n, m;
static vector<int> G[NMAX + 10];
static vector<int> RG[NMAX + 10];
static char state[NMAX + 10];

static void initialize() {
    // scanf("%d%d", &n, &m);
    n = readint();
    m = readint();

    for (int i = 1; i <= n; i++) {
        G[2 * i - 1].push_back(2 * i + n * 2);
        G[2 * i].push_back(2 * i - 1 + n * 2);
        G[2 * i + n * 2].push_back(2 * i - 1);
        G[2 * i - 1 + n * 2].push_back(2 * i);
    }  // for

    // For convinence, n is multiplied by two.
    n *= 2;

    for (int i = 0; i < m; i++) {
        int u, v;
        // scanf("%d%d", &u, &v);
        u = readint();
        v = readint();

        G[u].push_back(v + n);
        G[v].push_back(u + n);
    }  // for

    for (int i = 1; i <= n; i++) {
        for (size_t pos = 0; pos < G[i].size(); pos++) {
            RG[G[i][pos]].push_back(i);
        }  // for
    }      // for
}

inline int rev(int x) {
    if (x > n)
        return x - n;
    return x + n;
}

static bool try_select(int x) {
    if (state[x] == NOT_SELECTED)
        return false;
    if (state[x] == SELECTED)
        return true;
    if (state[rev(x)] == SELECTED)
        return false;

    // Q1 and Q2
    static bool in_q1[NMAX + 10], in_q2[NMAX + 10];
    memset(in_q1, 0, sizeof(in_q1));
    memset(in_q2, 0, sizeof(in_q2));

    // queue<int> q1, q2;
    static Queue q1, q2;
    q1.reset();
    q2.reset();

    // Push x to Q! and push rev(x) to Q2
    // (Select x so we can't select rev(x))
    in_q1[x] = true;
    q1.push(x);
    in_q2[rev(x)] = true;
    q2.push(rev(x));

    // Spread the range of selection by x
    // The edge u -> v means when I select u,
    // v must be selected at the same time.
    while (!q1.empty()) {
        int u = q1.front();
        q1.pop();

        for (size_t i = 0; i < G[u].size(); i++) {
            int v = G[u][i];

            // Already process, skip.
            if (in_q1[v])
                continue;

            // v should be selected, but the fact shows that it have been not
            // selected.
            if (state[v] == NOT_SELECTED)
                return false;
            if (state[v] == NOT_DETERMINED) {
                // not determined? Select it!
                // we should be careful that Q1 and Q2 is null.
                if (in_q2[v])
                    return false;
                in_q1[v] = true;
                q1.push(v);

                // Validate the state of rev(v).
                int rv = rev(v);
                if (state[rv] == SELECTED)
                    return false;
                else if (state[rv] == NOT_DETERMINED) {
                    // rev(v) is not selected.
                    if (in_q1[rv])
                        return false;
                    if (!in_q2[rv]) {
                        in_q2[rv] = true;
                        q2.push(rv);
                    }
                }
            }
        }  // for
    }      // while

    // Almost the same procedure as above.
    while (!q2.empty()) {
        int u = q2.front();
        q2.pop();

        for (size_t i = 0; i < RG[u].size(); i++) {
            int v = RG[u][i];

            if (in_q2[v])
                continue;

            // It seems that no more ifs are needed.
            if (in_q1[v])
                return false;
            in_q2[v] = true;
            q2.push(v);
        }  // for
    }      // while

    // If no error reported in the process, then we can save our work.
    for (int i = 1; i <= n * 2; i++) {
        if (in_q1[i])
            state[i] = SELECTED;
        else if (in_q2[i])
            state[i] = NOT_SELECTED;
    }  // for

    // OK
    return true;
}

int main() {
    // freopen("spo.in", "r", stdin);
    // freopen("spo.out", "w", stdout);
    initialize();

    for (int i = 1; i <= n; i++) {
        // i must be true of false, instead of not determined.
        if (!state[i] && !state[rev(i)]) {
            if (!try_select(i)) {
                if (!try_select(rev(i))) {
                    puts("NIE");
                    return 0;
                }
            }
        }
    }  // for

    for (int i = 1; i <= n; i++) {
        if (state[i] == SELECTED) {
            // printf("%d\n", i);
            putint(i);
        }
    }  // for

    fwrite(_buffer, 1, _pos, stdout);

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
