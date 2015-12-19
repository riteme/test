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
    Node() : value(0), mark(0), size(0), left(0), right(0) {}

    ntype value;
    ntype mark;
    ntype size;
    ntype left;
    ntype right;
};  // struct Node

static ntype n, q;
static ntype v[NMAX + 1];
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
void insert(size_type l, size_type r, ntype value);
ntype query(size_type l, size_type r);

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

    for (int i = 1; i <= n; i++) { v[i] = read<ntype>(); }  // for

    build();
}

void quit() {}

inline void update(size_type x) {
    tree[x].value = tree[LEFT(x)].value + tree[RIGHT(x)].value;

    LOG("(update) tree[x]: {left: "
        << tree[x].left << ", right: " << tree[x].right
        << ", value: " << tree[x].value << ", mark: " << tree[x].mark
        << ", size: " << tree[x].size << "}");
}

ntype build(size_type x, ntype l, ntype r);
void insert(size_type x, ntype l, ntype r, ntype value);
ntype query(size_type x, ntype l, ntype r);

ntype build(size_type x, ntype l, ntype r) {
    if (l == r) {
        tree[x].value = v[l];
        tree[x].size = 1;
        tree[x].left = tree[x].right = l;
    } else {
        ntype mid = (l + r) / 2;
        tree[x].size += build(LEFT(x), l, mid);
        tree[x].size += build(RIGHT(x), mid + 1, r);
        tree[x].value = tree[LEFT(x)].value + tree[RIGHT(x)].value;
        tree[x].left = tree[LEFT(x)].left;
        tree[x].right = tree[RIGHT(x)].right;
    }

    LOG("(build) tree[x]: {left: "
        << tree[x].left << ", right: " << tree[x].right
        << ", value: " << tree[x].value << ", mark: " << tree[x].mark
        << ", size: " << tree[x].size << "}");

    return tree[x].size;
}

void insert(size_type x, ntype l, ntype r, ntype value) {
    if (l <= tree[x].left and r >= tree[x].right) {
        LOG("(insert) Set at [" << tree[x].left << ", " << tree[x].right
                                << "]");

        tree[x].mark += value;
        tree[x].value += value * tree[x].size;

        return;
    }

    ntype mid = (tree[x].left + tree[x].right) / 2;
    if (r <= mid) {
        LOG("(insert) Turn left at [" << tree[x].left << ", " << tree[x].right
                                      << "]");

        insert(LEFT(x), l, r, value);
    } else if (l > mid) {
        LOG("(insert) Turn right at [" << tree[x].left << ", " << tree[x].right
                                       << "]");

        insert(RIGHT(x), l, r, value);
    } else {
        LOG("(insert) Divide at [" << tree[x].left << ", " << tree[x].right
                                   << "]");

        insert(LEFT(x), l, r, value);
        insert(RIGHT(x), l, r, value);
    }

    update(x);
}

ntype query(size_type x, ntype l, ntype r) {
    if (l <= tree[x].left and r >= tree[x].right) {
        LOG("(query) Get at [" << tree[x].left << ", " << tree[x].right << "]");

        return tree[x].value;
    }

    if (tree[x].mark != 0) {
        LOG("(query) Seperate mark at [" << tree[x].left << ", "
                                         << tree[x].right << "]");

        ntype mark = tree[x].mark;
        tree[x].mark = 0;
        tree[LEFT(x)].mark += mark;
        tree[LEFT(x)].value += mark * tree[LEFT(x)].size;
        tree[RIGHT(x)].mark += mark;
        tree[RIGHT(x)].value += mark * tree[RIGHT(x)].size;
    }

    ntype mid = (tree[x].left + tree[x].right) / 2;
    if (r <= mid) {
        LOG("(query) Turn left at [" << tree[x].left << ", " << tree[x].right
                                     << "]");

        return query(LEFT(x), l, r);
    } else if (l > mid) {
        LOG("(query) Turn right at [" << tree[x].left << ", " << tree[x].right
                                      << "]");

        return query(RIGHT(x), l, r);
    } else {
        LOG("(query) Divide at [" << tree[x].left << ", " << tree[x].right
                                  << "]");

        return query(LEFT(x), l, r) + query(RIGHT(x), l, r);
    }
}

void build() { build(1, 1, n); }
void insert(size_type l, size_type r, ntype value) { insert(1, l, r, value); }
ntype query(size_type l, size_type r) { return query(1, l, r); }
