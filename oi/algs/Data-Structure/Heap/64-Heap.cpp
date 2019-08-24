#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <chrono>
#include <queue>

using namespace std;

typedef unsigned long long u64;

class Heap {
 public:
    Heap(int n) : ans(0), size(0) {
        root = _build(0, n);
    }

    ~Heap() {}

    void insert(int key) {
        _insert(root, key);

        size++;
        ans = max(ans, key);
    }

    void remove(int key) {
        _remove(root, key);

        size--;
        if (size && ans == key)
            ans = query();
    }

    int top() {
        return ans;
    }

    int query() {
        return _query(root);
    }

    int ans, size;

    static int lowtb[1 << 16];

 private:
    static int lowbit(u64 x) {
        u64 l = x & (-x);
        return (l >> 16) ? ((l >> 32) ? ((l >> 48) ? lowtb[l >> 48] + 48
                                                   : lowtb[l >> 32] + 32)
                                      : lowtb[l >> 16] + 16)
                         : lowtb[l];
    }

    struct Node;

    struct Node {
        Node() : w(0), set(0) {}
        Node(int l, int r) : w((r - l + 1) / 64 + 1), set(0) {
            child = new Node *[64];
            memset(child, 0, sizeof(Node *) * 64);
        }

        int w;
        u64 set;
        Node **child;
    };  // struct Node

    Node *root;

    Node *_build(int l, int r) {
        if (l == r)
            return new Node;

        Node *x = new Node(l, r);
        for (int i = 63; i >= 0; i--) {
            if (l > r)
                break;

            x->child[i] = _build(l, min(r, l + x->w - 1));
            l += x->w;
        }  // for

        return x;
    }

    void _insert(Node *x, int key) {
        if (x->w == 0)
            x->set++;
        else {
            int pos = key / x->w;
            _insert(x->child[63 - pos], key % x->w);
            x->set |= 1ULL << (63 - pos);
        }
    }

    void _remove(Node *x, int key) {
        if (x->w == 0)
            x->set--;
        else {
            int pos = key / x->w;
            _remove(x->child[63 - pos], key % x->w);

            if (!x->child[63 - pos]->set)
                x->set ^= 1ULL << (63 - pos);
        }
    }

    int _query(Node *x) {
        if (x->w == 0)
            return 0;
        else {
            int nxt = lowbit(x->set);

            return _query(x->child[nxt]) + x->w * (63 - nxt);
        }
    }
};  // class Heap

int Heap::lowtb[1 << 16];

static struct init {
    init() {
        for (int i = 0; i < 16; i++) {
            Heap::lowtb[1 << i] = i;
        }  // for
    }
} _init;

const int n = 1000000;
static int seq[2000000];
static int ans1[2000000];
static int ans2[2000000];

int main() {
    srand(time(0));
    for (int i = 1; i <= n; i++) {
        seq[i] = rand() % 2000001;
    }  // for

    auto start = chrono::high_resolution_clock::now();

    Heap q(2000000);
    for (int i = 1; i <= n; i++) {
        q.insert(seq[i]);
        ans1[i] = q.top();

        if (q.size && (seq[i] & 1))
            q.remove(q.top());
    }  // for

    auto stop = chrono::high_resolution_clock::now();
    printf("%ld\n",
           chrono::duration_cast<chrono::milliseconds>(stop - start).count());

    start = chrono::high_resolution_clock::now();

    priority_queue<int> std;
    for (int i = 1; i <= n; i++) {
        std.push(seq[i]);
        ans2[i] = std.top();

        if (!std.empty() && (seq[i] & 1))
            std.pop();
    }  // for

    stop = chrono::high_resolution_clock::now();
    printf("%ld\n",
           chrono::duration_cast<chrono::milliseconds>(stop - start).count());

    if (memcmp(ans1 + 1, ans2 + 1, sizeof(int) * n) != 0)
        puts("Wrong Answer");
    else
        puts("Accepted");

    return 0;
}  // function main
