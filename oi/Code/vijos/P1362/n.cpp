#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>

#include <vector>
#include <deque>
#include <algorithm>

#define NMAX 300

typedef long long int64;

struct Element {
    Element(int _v, int64 _w, Element *_next)
    : v(_v), w(_w), next(_next) {}

    int v;
    int64 w;

    Element *next;
};

static int n;
static int64 s;
static Element *G[NMAX + 10];
static vector<int> children[NMAX + 10];
static int64 w[NMAX + 10];
static bool marked[NMAX + 10];

inline void add_edge(int u, int v, int64 w) {
    G[u] = new Element(v, w, G[u]);
    G[v] = new Element(u, w, G[v]);
}

static void build_tree(int x) {
    marked[x] = true;

    for (Element *ptr = G[x]; ptr; ptr = ptr->next) {
        int v = ptr->v;

        if (marked[v])
            continue;

        children[x].push_back(x);
        w[v] = ptr->w;
        build_tree(v);
    }
}

static void initialize() {
    scanf("%d%lld", &n, &s);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        int64 w;
        scanf("%d%d%lld", &u, &v, &w);

        add_edge(u, v, w);
    }

    build_tree(1);
}

static int64 maxlength[NMAX + 10];
static int64 maxdist[NMAX + 10];
static int endpoint[NMAX + 10];
static int p1[NMAX + 10];
static int p2[NMAX + 10];

static void dp(int x) {
    marked[x] = true;

    if (children[x].empty()) {
        maxlength[x] = 0;
        maxdist[x] = 0;
        endpoint[x] = x;
        p1[x] = p2[x] = x;
    } else if (children[x].size() == 1) {
        int v = G[x]->v;

        dp(v);
        maxdist[x] = maxdist[v] + w[v];
        endpoint[x] = endpoint[v];

        if (maxdist[x] > maxlength[v]) {
            maxlength[x] = maxdist[x];
            p1[x] = x;
            p2[x] = endpoint[x];
        } else {
            maxlength[x] = maxlength[v];
            p1[x] = p1[v];
            p2[x] = p2[v];
        }
    } else {
        int64 first = 0, second = 0;
        int firstp, secondp, maxp;

        for (size_t i = 0; i < children[x].size(); i++) {
            int v = children[x][i];

            dp(v);
            
            if (maxlength[v] > maxlength[x]) {
                maxlength[x] = maxlength[v];
                maxp = v;
            }

            int64 distv = maxdist[v] + w[v];
            if (distv > first) {
                maxdist[x] = distv;
                second = first;
                secondp = firstp;
                first = distv;
                firstp = endpoint[v];
            } else if (distv > second) {
                second = distv;
                secondp = endpoint[v];
            }
        }

        int64 newdist = first + second;
        if (newdist > maxlength[x]) {
            maxlength[x] = newdist;
            p1[x] = firstp;
            p2[x] = secondp;
        } else {
            p1[x] = p1[maxp];
            p2[x] = p2[maxp];
        }
    }
}

static int len;
static int path[NMAX + 10];
static int64 dist_to_next[NMAX + 10];
static int64 dist[NMAX + 10];
static int64 weight[NMAX + 10];

static bool scan_path(int x, int pos, int t) {
    if (x == t) {
        path[pos] = x;
        len = pos;

        return true;
    }

    bool flag = false;
    for (size_t i = 0; i < children[x].size(); i++) {
        int v = children[x][i];

        dist[v] = dist[x] + w[v];

        if (scan_path(v, pos + 1, t)) {
            flag = true;

            path[pos] = x;
            dist_to_next[pos] = w[v];
        } else
            weight[pos] = max(weight[pos], dist[v]);
    }

    return flag;
}

int main() {
    initialize();

    dp(1);
    scan_path(p1[1], 1, p2[1]);

    for (int i = 1; i <= len; i++)
        dist_to_next[i] += dist_to_next[i - 1];

    deque<int> q;
    q.push_back(1);
    int i = 1, j = 1;
    int64 answer = LLONG_MAX;
    while (i < len && j < len) {
        if (j < i)
            j = i;

        while (j < len && dist[j] - dist[i - 1] <= s) {
            j++;

            while (!q.empty() && weight[q.back()] <= weight[j])
                q.pop_back();
            q.push_back(j);
        }

        answer = min(answer,
                     max(weight[q.front()],
                         max(dist_to_next[i - 1],
                             dist_to_next[len - 1] - dist_to_next[j - 1]
                            )
                        )
                    );
        i++;
        while (q.front() < i)
            q.pop_front();
    }

    printf("%lld\n", answer);

    return 0;
}
