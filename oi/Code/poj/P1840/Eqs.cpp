#include <cstring>
#include <cstdlib>
#include <climits>
#include <cstdio>
#include <cmath>
#include <list>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#define MOD 1000007
#define MAXN 1030302

struct Result {
    Result() : value(0), count(0) {}
    Result(int _v, int _c) : value(_v), count(_c) {}

    int value;
    int count;

    bool operator==(const int lhs) const { return value == lhs; }
};  // struct Result

template <typename T>
struct Node {
    T value;
    Node *next;
    // unsigned next;
};  // struct Node

typedef unsigned hash_t;
typedef Node<Result> NodeType;

// typedef list<Result>::iterator iterator_t;
// static list<Result> hb[MOD];

// typedef vector<Result>::iterator iterator_t;
// static vector<Result> hb[MOD];
static NodeType *hb[MOD];
static NodeType memory[MAXN + 1];
static int n = 1;

static int a1, a2, a3, a4, a5;

NodeType *list_allocate();
void list_push(NodeType **node, int v);
NodeType *list_find(NodeType *node, int v);
void increase(int v);
int count(int v);

inline hash_t h(int v) {
    return (v >= 0 ? v : -v) % MOD;
    // int n = v >= 0 ? v : -v;
    // return (n % MOD + n / MOD) % MOD;
}

inline int compute(int x1, int x2, int x3) {
    return a1 * x1 * x1 * x1 + a2 * x2 * x2 * x2 + a3 * x3 * x3 * x3;
}

inline int compute(int x4, int x5) {
    return -(a4 * x4 * x4 * x4 + a5 * x5 * x5 * x5);
}

inline NodeType *list_allocate() { return &memory[n++]; }

void list_push(NodeType **node, int v) {
    if (node == NULL) {
        // *node = new NodeType();
        *node = list_allocate();
        (*node)->value.value = v;
        (*node)->value.count = 1;
        (*node)->next = NULL;
    } else {
        NodeType *origin = *node;

        // *node = new NodeType();
        *node = list_allocate();
        (*node)->value.value = v;
        (*node)->value.count = 1;
        (*node)->next = origin;
    }
}

NodeType *list_find(NodeType *node, int v) {
    while (node != NULL) {
        if (node->value.value == v)
            break;
        else
            node = node->next;
    }  // while

    return node;
}

/*inline*/ void increase(int v) {
    // hash_t hx = h(v);
    // iterator_t iter = std::find(hb[hx].begin(), hb[hx].end(), v);

    // if (iter == hb[hx].end())
    //     hb[hx].push_back(Result(v, 1));
    // else
    //     iter->count++;

    hash_t u = h(v);
    NodeType *iter = list_find(hb[u], v);

    if (iter == NULL)
        list_push(&hb[u], v);
    else
        iter->value.count++;
}

/*inline*/ int count(int v) {
    // for (iterator_t beg = hb[u].begin(); beg != hb[u].end(); beg++) {
    //     if (v == beg->value) cnt += beg->count;
    // }  // for

    hash_t u = h(v);

    NodeType *iter = list_find(hb[u], v);
    if (iter == NULL)
        return 0;
    else
        return iter->value.count;
}

int main(/*int argc, char *argv[]*/) {
    scanf("%d %d %d %d %d", &a1, &a2, &a3, &a4, &a5);

    memset(hb, NULL, sizeof(hb));

    // for (int x1 = -50; x1 <= 50; x1++)
    //     if (x1 != 0)
    //         for (int x2 = -50; x2 <= 50; x2++)
    //             if (x2 != 0)
    //                 for (int x3 = -50; x3 <= 50; x3++)
    //                     if (x3 != 0) increase(compute(x1, x2, x3));
    for (int x1 = 1; x1 <= 50; x1++)
        for (int x2 = 1; x2 <= 50; x2++)
            for (int x3 = 1; x3 <= 50; x3++) {
                increase(compute(x1, x2, x3));
                increase(compute(x1, x2, -x3));
                increase(compute(x1, -x2, x3));
                increase(compute(-x1, x2, x3));
                increase(compute(x1, -x2, -x3));
                increase(compute(-x1, x2, -x3));
                increase(compute(-x1, -x2, x3));
                increase(compute(-x1, -x2, -x3));
            }

    // int cnt = 0;
    // for (int x1 = -50; x1 <= 50; x1++)
    //     if (x1 != 0)
    //         for (int x2 = -50; x2 <= 50; x2++)
    //             if (x2 != 0) cnt += count(compute(x1, x2));
    int cnt = 0;
    for (int x1 = 1; x1 <= 50; x1++)
        for (int x2 = 1; x2 <= 50; x2++) {
            cnt += count(compute(x1, x2));
            cnt += count(compute(x1, -x2));
            cnt += count(compute(-x1, x2));
            cnt += count(compute(-x1, -x2));
        }

    printf("%d", cnt);

    return 0;
}  // function main
