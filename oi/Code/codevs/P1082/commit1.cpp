#include <climits>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <bitset>

using namespace std;

#define DEBUG

#define NMAX 100000
#define QMAX 100000
#define AMAX 1000000000
#define CMAX 10000
#define ADD_COMMAND 'C'
#define QUERY_COMMAND 'Q'
#define EXIT_COMMAND 'E'

#define ZERO (1 << h)
#define LEFT(x) (x << 1)
#define RIGHT(x) (x << 1 | 1)
#define PARENT(x) (x >> 1)

#define TO_STRING(x) bitset<sizeof(size_type) * 8>((x)).to_string()

#ifdef DEBUG
#define LOG(msg) cout << msg << endl
#else
#define LOG(msg)
#endif  // IFDEF DEBUG

#define MEMORY_SIZE 2097151

#define FMT "%lld"
typedef unsigned long long ntype;
typedef unsigned size_type;

struct Node {
    Node() : value(0), mark(0), size(0), left(LLONG_MAX), right(0) {}

    ntype value;
    ntype mark;
    ntype size;
    ntype left;
    ntype right;
};  // struct Node

static ntype n, q;
static size_type h;
static Node tree[MEMORY_SIZE + 1];

template <typename TReturn>
inline TReturn read() {
    TReturn x = 0;
    char c = getchar();
    while (c < '0' or c > '9') c = getchar();
    while ('0' <= c and c <= '9') x = x * 10 + c - '0', c = getchar();

    return x;
}

void initialize();
void quit();

void build();
void insert(size_type s, size_type t, ntype value);
ntype query(size_type s, size_type t);

int main() {
    initialize();

    // for (ntype cnt = 0; cnt < q; cnt++) {
    while (true) {
        // Get the command.
        char command = getchar();
        while (command != QUERY_COMMAND and command != ADD_COMMAND and
               command != EXIT_COMMAND)
            command = getchar();

        size_type s, t;
        ntype c;

        // scanf("%d %d", &s, &t);
        switch (command) {
            case ADD_COMMAND:
                // scanf(FMT, &c);
                s = read<size_type>();
                t = read<size_type>();
                c = read<ntype>();

                insert(s, t, c);
                break;

            case QUERY_COMMAND:
                s = read<size_type>();
                t = read<size_type>();

                printf(FMT "\n", query(s, t));
                break;

            case EXIT_COMMAND: goto exit_point;
        }  // switch to command
    }      // for

exit_point:
    quit();
    return 0;
}  // function main

void initialize() {
    // scanf(FMT, &n);
    n = read<ntype>();

    build();
}

void quit() {}

inline void update(size_type x) {
    tree[x].value = tree[LEFT(x)].value + tree[RIGHT(x)].value;

    LOG("update: " << TO_STRING(x));
}

// O(nlogn)
void build() {
    // Compute the height of ST.
    h = 0;
    size_type size = 1;
    while (size < n + 2) {
        size <<= 1;
        h++;
    }  // while

    LOG("build: h = " << h);

    // Fill leafnodes.
    for (size_type i = ZERO | 1, j = 1; j <= n; i++, j++) {
        tree[i].value = read<ntype>();
        tree[i].size = 1;
        tree[i].left = tree[i].right = i;

        LOG("build: generate leafnode: " << TO_STRING(i));

        // Update fathers' value.
        for (size_type p = PARENT(i); p != 0; p = PARENT(p)) {
            tree[p].value += tree[i].value;
            tree[p].size++;

            if (j < tree[p].left) tree[p].left = j;
            if (j > tree[p].right) tree[p].right = j;

            LOG("build: left: " << tree[p].left
                                << ", right: " << tree[p].right);
            LOG("build: update father: " << TO_STRING(p));
        }  // for
    }      // for
}

void insert(size_type s, size_type t, ntype value) {
    for (s += ZERO - 1, t += ZERO + 1; s + 1 != t;
         s = PARENT(s), t = PARENT(t)) {
        // if s is the left subtree.
        if ((s & 1) == 0) {
            tree[s + 1].mark += value;
            tree[s + 1].value += value * tree[s + 1].size;

            LOG("insert: s + 1 = " << TO_STRING(s + 1));
        }

        // if t is right subtree.
        if ((t & 1) == 1) {
            tree[t - 1].mark += value;
            tree[t - 1].value += value * tree[t - 1].size;

            LOG("insert: t - 1 = " << TO_STRING(t - 1));
        }

        update(PARENT(s));
        update(PARENT(t));
    }  // for

    // update parents.
    for (size_type x = PARENT(s); x != 0; x = PARENT(x)) {
        update(x);

        LOG("insert: update father: " << TO_STRING(x));
    }  // for
}

ntype query(size_type s, size_type t) {
    ntype os = s, ot = t;
    ntype result = 0;
    ntype length = t - s + 1;

    for (s += ZERO - 1, t += ZERO + 1; s + 1 != t;
         s = PARENT(s), t = PARENT(t)) {
        LOG("query: s = " << TO_STRING(s));
        LOG("query: t = " << TO_STRING(t));

        // if s is the left subtree.
        if ((s & 1) == 0) {
            result += tree[s + 1].value;

            LOG("query: s + 1 = " << TO_STRING(s + 1));
        }

        // if t is right subtree.
        if ((t & 1) == 1) {
            result += tree[t - 1].value;

            LOG("query: t - 1 = " << TO_STRING(t - 1));
        }
    }  // for

    // Add current s and t's mark.
    result += tree[s].mark * ((tree[s].right + 1) - os);
    result += tree[t].mark * ((ot + 1) - tree[t].left);

    LOG("query: current s = " << TO_STRING(s));
    LOG("query: current t = " << TO_STRING(t));
    LOG("query: s: left: " << tree[s].left << ", right: " << tree[s].right);
    LOG("query: t: left: " << tree[t].left << ", right: " << tree[t].right);

    // Sum all the marks of parents.
    for (size_type x = PARENT(s); x != 0; x = PARENT(x)) {
        result += tree[x].mark * length;

        LOG("query: query father: " << TO_STRING(x));
    }  // for

    return result;
}
