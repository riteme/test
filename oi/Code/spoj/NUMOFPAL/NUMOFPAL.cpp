/**
 * Palindrome Tree
 * Accepted
 * NOTICE!: Counting occurance here is wrong
 *     See UOJ P103 instead
 */

#define NDEBUG

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#ifndef NDEBUG
#define TRACE printf("At %d (%s) traced.\n", __LINE__, __PRETTY_FUNCTION__);
#else
#define TRACE
#endif  // IFNDEF NDEBUG

#define BUFFERSIZE 100000
#define SIGMA 26

struct Node {
    Node() : id(0), length(0), fail(NULL) {
        memset(transitions, 0, sizeof(transitions));
    }

    int id;
    int length;
    Node *fail;
    Node *transitions[SIGMA];
};  // struct Node

static char S[BUFFERSIZE];
static vector<Node *> fail[BUFFERSIZE];

static Node *build_palindrome_tree() {
    int idcnt = 1;
    Node *root = new Node;
    Node *subroot = new Node;
    root->id = 1;
    subroot->id = 0;
    root->fail = subroot;
    subroot->length = -1;
    for (size_t i = 0; i < SIGMA; i++)
        subroot->transitions[i] = root;

    Node *last = root;
    for (int pos = 0; S[pos] != '\0'; pos++) {
        // printf("Adding %c...\n", S[pos]);
        size_t chr = S[pos] - 'a';
        int target = pos - last->length - 1;
        while (target < 0 || S[target] != chr + 'a') {
            last = last->fail;
            target = pos - last->length - 1;
        }

        Node *x = new Node;
        x->id = ++idcnt;
        Node *y = last->fail;

        // Remember to check whether the new suffix is a palindrome!
        while (y && (y->transitions[chr] == NULL || pos - y->length - 1 < 0 ||
                     S[pos - y->length - 1] != chr + 'a'))
            y = y->fail;
        if (!y)
            x->fail = root;
        else
            x->fail = y->transitions[chr];
        x->length = last->length + 2;
        last->transitions[chr] = x;
        last = x;
    }  // for

    for (size_t i = 0; i < SIGMA; i++)
        if (subroot->transitions[i] == root)
            subroot->transitions[i] = NULL;

    return root;
}

static void dfs(Node *x) {
    if (x->fail)
        fail[x->fail->id].push_back(x);
    for (size_t i = 0; i < SIGMA; i++) {
        if (x->transitions[i])
            dfs(x->transitions[i]);
    }  // for
}

static int answer;
static int size[BUFFERSIZE];

static void dfs_fail(int x) {
    size[x] = 1;
    for (unsigned i = 0; i < fail[x].size(); i++) {
        Node *v = fail[x][i];
        dfs_fail(v->id);
        size[x] += size[v->id];
        answer += size[v->id];
    }  // for
}

static string txt;
static void _dfs(Node *x) {
    printf("%s: %d\n", txt.c_str(), size[x->id]);
    for (size_t i = 0; i < SIGMA; i++) {
        if (x->transitions[i]) {
            txt.push_back(i + 'a');
            _dfs(x->transitions[i]);
            txt.pop_back();
        }
    }  // for
}

static void initialize() {
    scanf("%s", S);
}

int main() {
    initialize();

    Node *tree = build_palindrome_tree();
    TRACE
    dfs(tree);
    dfs(tree->fail);
    dfs_fail(1);
    // _dfs(tree);
    // _dfs(tree->fail);
    printf("%d\n", answer);

    return 0;
}  // function main
