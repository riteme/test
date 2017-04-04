#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 100000
#define CMAX 10

struct Node {
    Node()
        : left(0), right(0), len(0), suffix_link(NULL) {
        memset(trans, 0, sizeof(trans));
    }

    int left, right;
    int len;
    Node *suffix_link;
    Node *trans[CMAX];
};

static Node *root, *last;

void copy_node(Node *u, Node *x, int c) {
    Node *target = u->trans[c];
    Node *newnode = new Node;

    newnode->len = u->len + 1;

    newnode->suffix_link = target->suffix_link;
    target->suffix_link = newnode;
    if (x)
        x->suffix_link = newnode;

    memcpy(newnode->trans, target->trans, sizeof(target->trans));

    while (u) {
        if (u->trans[c] == target)
            u->trans[c] = newnode;
        u = u->suffix_link;
    }
}

void append(int c) {
    if (last->trans[c]) {
        if (last->len + 1 != last->trans[c]->len)
            copy_node(last, NULL, c);

        last = last->trans[c];
        return;
    }

    Node *x = new Node;
    x->len = last->len + 1;

    Node *u = last;
    while (u && !u->trans[c]) {
        u->trans[c] = x;
        u = u->suffix_link;
    }

    if (u && u->len + 1 != u->trans[c]->len) {
        copy_node(u, x, c);
    } else if (u)
        x->suffix_link = u->trans[c];
    else
        x->suffix_link = root;

    last = x;
}

static int n, _c;
static int col[NMAX + 10];
static vector<int> G[NMAX + 10];

void initialize() {
    root = last = new Node;

    scanf("%d%d", &n, &_c);

    for (int i = 1; i <= n; i++) {
        scanf("%d", col + i);
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }
}

void dfs(int u, int f) {
    append(col[u]);
    Node *current = last;

    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];

        if (v != f) {
            last = current;
            dfs(v, u);
        }
    }
}

static int tail;
static Node *seq[NMAX * 20 * 4 + 10];

void scan(Node *u) {
    u->left = 1;

    for (int c = 0; c < CMAX; c++) {
        Node *v = u->trans[c];
        if (!v)
            continue;

        v->right++;
        if (!v->left)
            scan(v);
    }
}

void topological_sort() {
    queue<Node *> q;
    q.push(root);

    while (!q.empty()) {
        Node *u = q.front();
        q.pop();
        u->left = INT_MAX;
        u->right = 0;
        seq[++tail] = u;

        for (int c = 0; c < CMAX; c++) {
            Node *v = u->trans[c];
            if (!v)
                continue;

            v->right--;
            if (v->right == 0)
                q.push(v);
        }
    }
}

int main() {
    freopen("zjoi15_substring.in", "r", stdin);
    freopen("zjoi15_substring.out", "w", stdout);
    initialize();

    for (int u = 1; u <= n; u++) {
        if (G[u].size() == 1) {
            last = root;
            dfs(u, 0);
        }
    }

    scan(root);
    topological_sort();

    root->left = root->right = 0;
    for (int i = 1; i <= tail; i++) {
        Node *u = seq[i];

        for (int c = 0; c < CMAX; c++) {
            Node *v = u->trans[c];
            if (!v)
                continue;

            v->left = min(v->left, u->left + 1);
            v->right = max(v->right, u->right + 1);
        }
    }

    i64 answer = 0;
    for (int i = 2; i <= tail; i++) {
        answer += seq[i]->right - seq[i]->left + 1;
    }

    printf("%lld\n", answer);

    return 0;
}
