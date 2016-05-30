/**
 * You can also use the **standard program** ('std.cpp').
 * This uses normal binary tree to ensure that everything is right.
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define NMAX 200000

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

static unsigned _memcount;
static Node _memory[NMAX];

static Node *allocate() {
    return &_memory[_memcount++];
}

static Node *tree;
static int distance[NMAX + 1];

static unsigned count;
static int p[NMAX];
static int k[NMAX];

static Node *insert(Node *x, int key, int depth) {
    if (!x) {
        distance[key] = depth;

        x = allocate();
        x->key = key;
        x->left = NULL;
        x->right = NULL;

        return x;
    }

    if (key < x->key)
        x->left = insert(x->left, key, depth + 1);
    else
        x->right = insert(x->right, key, depth + 1);

    return x;
}

inline int randint(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s [INPUT FILE] [OUTPUT FILE]\n", argv[0]);
        exit(-1);
    }

    srand(time(0));

    FILE *fp = NULL;
    fp = fopen(argv[1], "r");

    if (!fp) {
        fputs("(error) Can't open input file.\n", stderr);
        exit(-1);
    }

    int x;
    while (fscanf(fp, "%d", &x) != EOF) {
        tree = insert(tree, x, 1);

        p[count] = x;
        k[count] = randint(1, distance[x]);
        count++;
    }  // while

    fclose(fp);
    fp = NULL;

    fp = fopen(argv[2], "w");

    if (!fp) {
        fputs("(error) Can't open output file.\n", stderr);
        exit(-1);
    }

    fprintf(fp, "%d\n", count);

    for (unsigned i = 0; i < count; i++) {
        fprintf(fp, "%d %d\n", p[i], k[i]);
    }  // for

    fclose(fp);

    return 0;
}  // function main
