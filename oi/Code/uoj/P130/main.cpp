// NOI2015 荷马史诗

#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <algorithm>
#include <functional>

// #include <bits/stdc++.h>

using namespace std;

#define NMAX 100000
#define KMAX 9

typedef long long ntype;

void initialize();
void quit();

struct Node {
    // Memory leak here
    // That doesn't matter.
    Node() : size(0), freq(0), height(0) {}

    ntype size;
    ntype freq;
    ntype height;
    Node **child;
};  // struct Node

namespace std {
template <>
struct greater<Node *> {
    auto operator()(const Node *a, const Node *b) const -> bool {
        return a->freq > b->freq or
               (a->freq == b->freq and a->height > b->height);
    }
};  // struct greater<Node *>
}  // namespace std

inline Node *new_node(const ntype k) {
    Node *pNode = new Node();

    pNode->child = new Node *[k];

    return pNode;
}

inline void insert_node(Node *x, Node *c) { x->child[x->size++] = c; }

static ntype n, k;
static ntype w[NMAX + 10];
static Node *root;
static priority_queue<Node *, vector<Node *>, greater<Node *>> pq;

int main() {
    initialize();

    ntype k0;
    while (pq.size() > 1) {
        n = pq.size();
        k0 = (n - 1) % (k - 1);

        if (k0 != 0) {
            for (ntype i = 0; i < k - k0 - 1; i++) {
                pq.push(new_node(k));
            }  // for
        }

        Node *pParent = new_node(k);
        for (ntype i = 0; i < k; i++) {
            Node *pChild = pq.top();
            pq.pop();

            pParent->freq += pChild->freq;
            pParent->height = max(pParent->height, pChild->height + 1);

            insert_node(pParent, pChild);
        }  // for

        pq.push(pParent);
    }  // while

    root = pq.top();

    quit();
    return 0;
}  // function main

void initialize() {
    scanf("%lld %lld", &n, &k);

    for (ntype i = 1; i <= n; i++) scanf("%lld", w + i);

    root = nullptr;
    for (ntype i = 1; i <= n; i++) {
        Node *ptr = new_node(k);
        ptr->freq = w[i];

        pq.push(ptr);
    }  // for
}

static ntype length;
static ntype max_length;
ntype dfs(const Node *x, const ntype depth);

void quit() {
    // 计算答案
    max_length = 0;
    length = dfs(root, 0);

    printf("%lld\n%lld", length, max_length);
}

ntype dfs(const Node *x, const ntype depth) {
    if (depth > max_length) max_length = depth;

    if (x->size == 0) {
        // printf("%lld * %lld\n", x->freq, depth);
        return x->freq * depth;
    } else {
        ntype result = 0;

        for (ntype i = 0; i < x->size; i++) {
            result += dfs(x->child[i], depth + 1);
        }  // for

        return result;
    }
}
