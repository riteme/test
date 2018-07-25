// #define NDEBUG
#pragma GCC optimize(3)

#include <bits/stdc++.h>

using namespace std;

// #define NMAX 80000
#define NMAX 100

#define SEED (233)
static struct MyRandom {
    MyRandom() {
        srand(SEED);
    }

    int operator()() const {
        return rand();
    }
} randint;  // struct MyRandom

template <typename TRemote>
struct Node {
    Node(int _key, TRemote *_remote)
            : key(_key)
            , remote(_remote)
            , left(NULL)
            , right(NULL)
            , weight(randint()) {}

    typedef TRemote RemoteType;
    typedef pair<Node *, Node *> NodePairType;

    int key;
    TRemote *remote;
    Node *left;
    Node *right;
    int weight;
};  // struct Node

template <typename TNode>
inline void update(TNode *x);

template <typename TNode>
inline void pushdown(TNode *x);

template <typename TNode>
inline TNode *left_rotate(TNode *x) {
    assert(x);
    assert(x->left);

    TNode *y = x->left;
    x->left = y->right;
    y->right = x;

    update(x);
    update(y);
    return y;
}

template <typename TNode>
inline TNode *right_rotate(TNode *x) {
    assert(x);
    assert(x->right);

    TNode *y = x->right;
    x->right = y->left;
    y->left = x;

    update(x);
    update(y);
    return y;
}

template <typename TNode>
static TNode *insert(TNode *x, int key, typename TNode::RemoteType *remote) {
    if (!x)
        return new TNode(key, remote);

    pushdown(x);
    if (key < x->key) {
        x->left = insert(x->left, key, remote);

        if (x->left->weight < x->weight)
            return left_rotate(x);
    } else if (key > x->key) {
        x->right = insert(x->right, key, remote);

        if (x->right->weight < x->weight)
            return right_rotate(x);
    }

    assert(x->key != key);

    update(x);
    return x;
}

template <typename TNode>
struct DefaultCmpare {
    bool operator()(const TNode *x, const int standard) const {
        return x->key < standard;
    }
};  // struct DefaultCmpare

template <typename TNode, typename TCompare = DefaultCmpare<TNode>>
static typename TNode::NodePairType split(TNode *x, int standard,
                                          const TCompare &cmp = TCompare()) {
    typedef typename TNode::NodePairType NodePair;

    if (!x)
        return NodePair(NULL, NULL);

    pushdown(x);
    NodePair result;
    if (cmp(x, standard)) {
        result = split(x->left, standard, cmp);
        x->left = result.second;
        result.second = x;
        update(x);
    } else {
        result = split(x->right, standard, cmp);
        x->right = result.first;
        result.first = x;
        update(x);
    }

    return result;
}

template <typename TNode>
static TNode *quick_merge(TNode *x, TNode *y) {
    if (!x)
        return y;
    if (!y)
        return x;

    if (x->weight < y->weight) {
        pushdown(x);
        x->right = quick_merge(x->right, y);
        update(x);

        return x;
    } else {
        pushdown(y);
        y->left = quick_merge(x, y->left);
        update(y);

        return y;
    }
}

template <typename TNode>
inline TNode *min_node(TNode *x) {
    while (x->left)
        x = x->left;
    return x;
}

template <typename TNode>
inline TNode *max_node(TNode *x) {
    while (x->right)
        x = x->right;
    return x;
}

template <typename TNode>
static void complete_free(TNode *x) {
    if (!x)
        return;

    complete_free(x->left);
    complete_free(x->right);
    delete x->remote;
    delete x;
}

struct PositionData {
    PositionData(int _position = 0) : position(_position) {}

    int position;
};  // struct PositionData

struct CountData {
    CountData(int _count = 0) : count(_count), maxcount(_count) {}

    int count;
    int maxcount;
};  // struct CountData

typedef Node<PositionData> PositionTreap;
typedef Node<CountData> CountTreap;

template <>
inline void pushdown(PositionTreap *x) {}

template <>
inline void pushdown(CountTreap *x) {}

template <>
inline void update(PositionTreap *x) {}

template <>
inline void update(CountTreap *x) {
    x->remote->maxcount = x->remote->count;

    if (x->left)
        x->remote->maxcount =
            max(x->remote->maxcount, x->left->remote->maxcount);
    if (x->right)
        x->remote->maxcount =
            max(x->remote->maxcount, x->right->remote->maxcount);
}

struct PositionCompare {
    bool operator()(const PositionTreap *x, int standard) const {
        return x->remote->position >= standard;
    }
};  // struct PositionCompare

struct CountCompare {
    bool operator()(const CountTreap *x, int standard) const {
        return x->key > standard;
    }
};  // struct CountCompare

static int n;
static int p, q;
static int seq1[NMAX + 10];
static int seq2[NMAX + 10];
static int map1[NMAX + 10];
static int map2[NMAX + 10];
static int cnt;
static PositionTreap *ptree;
static CountTreap *ctree;
static int answer;

static void initialize() {
    scanf("%d%d%d", &n, &p, &q);

    for (int i = 1; i <= p; i++) {
        scanf("%d", seq1 + i);
        map1[seq1[i]] = i;
    }

    for (int i = 1; i <= q; i++) {
        scanf("%d", seq2 + i);
        map2[seq2[i]] = i;
    }

    answer = 0;
    ptree = NULL;
    ctree = NULL;
}

int main() {
    // freopen("lcs.in", "r", stdin);
    // freopen("lcs.out", "w", stodut);

    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();

        for (int i = 1; i <= p; i++) {
            int pos = map2[seq1[i]];

            if (pos == 0)
                continue;

            PositionTreap::NodePairType u =
                split(ptree, pos, PositionCompare());

            cnt++;
            if (u.first) {
                PositionTreap *rightmost = max_node(u.first);
                CountTreap::NodePairType v =
                    split(ctree, rightmost->key, CountCompare());

                int maxlength = v.first->remote->maxcount;
                ctree = quick_merge(v.first, v.second);
                ctree = insert(ctree, cnt, new CountData(maxlength + 1));
            } else
                ctree = insert(ctree, cnt, new CountData(1));

            ptree = quick_merge(u.first, u.second);
            ptree = insert(ptree, cnt, new PositionData(pos));
        }  // for

        answer = ctree->remote->maxcount;
        printf("%d\n", answer);

        complete_free(ptree);
        complete_free(ctree);
    }  // while

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
