#include <cstdio>
#include <algorithm>
#include <iterator>

using namespace std;

#define NMAX 100000
#define QMAX 100000
#define AMAX 1000000000
#define CMAX 10000
#define ADD_COMMAND 'C'
#define QUERY_COMMAND 'Q'

#define ZERO (1 << h)
#define LEFT(x) (x << 1)
#define RIGHT(x) (x << 1 | 1)
#define PARENT(x) (x >> 1)

#define MEMORY_SIZE 2097151

#define FMT "%lld"
typedef long long ntype;
typedef unsigned size_type;

struct Node {
    Node() : value(0) {}

    ntype value;
};  // struct Node

static ntype n, q;
static ntype a[NMAX];
static size_type h;
static Node tree[MEMORY_SIZE + 1];

void initialize();
void quit();

void build();
void insert(size_type s, size_type t, ntype value);
ntype query(size_type s, size_type t);

int main() {
    initialize();

    for (ntype cnt = 0; cnt < q; cnt++) {
        // Get the command
        char command = getchar();
        while (command != QUERY_COMMAND and command != ADD_COMMAND)
            command = getchar();

        size_type s, t;
        ntype c;

        scanf("%d %d", &s, &t);
        switch (command) {
            case ADD_COMMAND:
                scanf(FMT, &c);
                insert(s, t, c);
                break;

            case QUERY_COMMAND: printf(FMT "\n", query(s, t)); break;
        }  // switch to command
    }      // for

    quit();
    return 0;
}  // function main

void initialize() {
    scanf(FMT FMT, &n, &q);

    build();
}

void quit() {}

void build() {
    // Compute the height of ST.
    h = 0;
    size_type size = 1;
    while (size < n + 2) {
        size *= 2;
        h++;
    }  // while

    // Fill leafnodes.
    for (size_type i = ZERO | 1; i /*<=*/ < (ZERO | 1) + n; i++) {
        scanf(FMT, &tree[i].value);

        // Update fathers' value.
        for (size_type p = PARENT(i); p > 0; p = PARENT(p)) {
            tree[p].value += tree[i].value;
        }  // for
    }      // for
}

void insert(size_type s, size_type t, ntype value) {
    for (s += ZERO, t += ZERO; s <= t; s++) {
        tree[s].value += value;

        for (size_type p = PARENT(s); p > 0; p = PARENT(p)) {
            tree[p].value += value;
        }  // for
    }      // for
}

ntype query(size_type s, size_type t) {
    s -= 1, t += 1;
    s += ZERO, t += ZERO;

    ntype result = 0;
    while ((s ^ t) != 1) {
        if (!(s & 1)) result += tree[s ^ 1].value;
        if ((t & 1)) result += tree[t ^ 1].value;
        s >>= 1, t >>= 1;
    }  // while

    return result;
}
