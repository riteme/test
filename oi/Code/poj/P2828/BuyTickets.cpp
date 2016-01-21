#include <cstdio>
#include <bitset>

using namespace std;

#define NMAX 200000
#define TREE_SIZE 1500000

#define TO_BINARY(x) (bitset<32>(x).to_string().c_str())

struct Query {
    int pos;
    int val;
};  // struct Query

struct Node {
    int left;
    int right;
    int count;
};  // struct Node

static int n;
static int s;
static Node tree[TREE_SIZE];
static int queue[NMAX + 10];
static Query querys[NMAX + 1];

void build_tree(int x, int left, int right) {
    tree[x].left = left;
    tree[x].right = right;
    tree[x].count = right - left + 1;

    if (left == right and left == 1) s = x;

    // printf("tree[%s]: {left = %d, right = %d, count = %d}\n", TO_BINARY(x),
    //        tree[x].left, tree[x].right, tree[x].count);

    if (left < right) {
        int mid = (left + right) >> 1;

        build_tree(x << 1, left, mid);
        build_tree((x << 1) + 1, mid + 1, right);
    }
}

int get_position(int x, int pos) {
    if (tree[x].left == tree[x].right) {
        // printf("get_position(x = %s, pos = %d, offest = %d) -> %d\n",
        //        TO_BINARY(x), pos, offest, tree[x].left);

        return tree[x].left;
    }

    int mid = tree[x << 1].count;
    if (pos <= mid) {
        // printf("get_position(x = %s, pos = %d, offest = %d): Turn left.\n",
        //        TO_BINARY(x), pos, offest);

        return get_position(x << 1, pos);
    } else {
        // printf("get_position(x = %s, pos = %d, offest = %d): Turn right.\n",
        //        TO_BINARY(x), pos, offest);

        return get_position((x << 1) + 1, pos - mid);
    }
}

void decrease(int x) {
    x += s - 1;

    while (x > 0) {
        tree[x].count--;

        // printf("tree[%s]: {left = %d, right = %d, count = %d}\n",
        // TO_BINARY(x),
        //        tree[x].left, tree[x].right, tree[x].count);

        x >>= 1;
    }  // while
}

int main() {
    while (scanf("%d", &n) != EOF) {
        build_tree(1, 1, n);

        for (int i = 1; i <= n; i++) {
            scanf("%d %d", &querys[i].pos, &querys[i].val);
        }  // for

        for (int i = n; i > 0; i--) {
            int p = get_position(1, querys[i].pos + 1);
            decrease(p);

            queue[p] = querys[i].val;
        }  // for

        for (int i = 1; i <= n; i++) {
            printf("%d", queue[i]);

            if (i != n)
                printf(" ");
            else
                printf("\n");
        }

    }  // while

    return 0;
}  // function main
