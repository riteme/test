#include <cstdio>
#include <cstring>

#include <unordered_map>
#include <algorithm>

using namespace std;

#define NMAX 300000

struct Node {
    Node() {
        go[0] = go[1] = NULL;
    }

    Node *go[2];
};

Node *insert(Node *x, int key, int pos = 30) {
    if (x)
        x = new Node(*x);
    else
        x = new Node;

    if (pos >= 0) {
        if ((key >> pos) & 1)
            x->go[1] = insert(x->go[1], key, pos - 1);
        else
            x->go[0] = insert(x->go[0], key, pos - 1);
    }

    return x;
}

int query_max(Node *x, int key, int pos = 30) {
    if (pos < 0)
        return 0;

    int bit = (key >> pos) & 1;
    if (x->go[bit ^ 1])
        return query_max(x->go[bit ^ 1], key, pos - 1) + (1 << pos);
    else
        return query_max(x->go[bit], key, pos - 1);
}

int query_min(Node *x, int key, int pos = 30) {
    if (pos < 0)
        return 0;

    int bit = (key >> pos) & 1;
    if (x->go[bit])
        return query_min(x->go[bit], key, pos - 1);
    else
        return query_min(x->go[bit ^ 1], key, pos - 1) + (1 << pos);
}

static int n, q, k, root, lans;
static unordered_map<int, Node *> trie;

int main() {
    // freopen("data.in", "r", stdin);
    scanf("%d%d", &n, &q);
    scanf("%d%d", &root, &k);

    trie[root] = insert(trie[root], k);
    
    for (int i = 0; i < n - 1; i++) {
        int u, v, k;
        scanf("%d%d%d", &u, &v, &k);
        trie[u] = insert(trie[v], k);
    }

    while (q--) {
        int type;
        scanf("%d", &type);

        type ^= lans;

        if (type == 0) {
            int u, v, k;
            scanf("%d%d%d", &v, &u, &k);

            u ^= lans;
            v ^= lans;
            k ^= lans;

            trie[u] = insert(trie[v], k);
        } else {
            int u, k;
            scanf("%d%d", &u, &k);

            u ^= lans;
            k ^= lans;

            int maxv = query_max(trie[u], k);
            int minv = query_min(trie[u], k);

            lans = maxv ^ minv;
            printf("%d %d\n", minv, maxv);
        }
    }

    return 0;
}
