#include <cstring>
#include <iostream>

using namespace std;

#define NODE_MAX 1048575
#define END_MAX 524288

typedef int ntype;

static ntype D, I;
static bool tree[NODE_MAX + 10];
static ntype h[END_MAX + 10];

inline ntype left(ntype x) { return x * 2; }

inline ntype right(ntype x) { return x * 2 + 1; }

inline ntype pow_of_two(ntype e) {
    ntype result = 2;

    while (e > 1) {
        result *= 2;
        e--;
    }  // while

    return result;
}

int main() {
    ios::sync_with_stdio(false);

    cin >> D >> I;

    memset(tree, false, sizeof(tree));
    memset(h, 0, sizeof(h));

    ntype bound = pow_of_two(D - 1);
    for (ntype i = 1; i <= bound; i++) {
        ntype pos = 1;
        ntype depth = 1;

        while (depth < D) {
            if (tree[pos] == false)
                pos = left(pos);
            else
                pos = right(pos);

            tree[i] = !tree[i];
            depth++;
        }  // while

        h[i] = pos;
    }  // for

    h[0] = h[bound - 1];

    cout << h[I % (bound - 1)];

    return 0;
}  // function main
