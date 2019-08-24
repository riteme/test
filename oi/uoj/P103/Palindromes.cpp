/**
 * Passed
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define NMAX 300000

typedef long long ntype;

static char S[NMAX + 10];

struct Node {
    Node() : length(0), occurance(1), fail(NULL) {
        memset(transitions, 0, sizeof(transitions));
    }

    ntype length;
    ntype occurance;
    Node *fail;
    Node *transitions[26];
    vector<Node *> fail_next;
};  // struct Node

static Node *build_palindrome_tree() {
    Node *root = new Node;
    Node *subroot = new Node;
    root->fail = subroot;
    subroot->length = -1;
    subroot->fail_next.push_back(root);

    Node *last = root;
    for (int p = 0; S[p] != '\0'; p++) {
        int chr = S[p] - 'a';
        while (p - last->length - 1 < 0 || S[p - last->length - 1] != S[p])
            last = last->fail;

        if (last->transitions[chr]) {  // Matched a original palindrome
            last = last->transitions[chr];
            last->occurance++;
        } else {
            Node *y = last->fail;
            while (y && (y->transitions[chr] == NULL || p - y->length - 1 < 0 ||
                         S[p - y->length - 1] != S[p]))
                y = y->fail;

            Node *x = new Node;
            x->fail = y ? y->transitions[chr] : root;
            x->fail->fail_next.push_back(x);
            x->length = last->length + 2;
            last->transitions[chr] = x;
            last = x;
        }
    }  // for

    return root;
}

static void initialize() {
    scanf("%s", S);
}

static ntype answer = 0;

static void dfs_fail(Node *x) {
    for (size_t i = 0; i < x->fail_next.size(); i++) {
        Node *v = x->fail_next[i];

        dfs_fail(v);
        x->occurance += v->occurance;
    }  // for

    answer = max(answer, x->length * x->occurance);
}

static string txt;

static void dfs_print(Node *x) {
    printf("%s: %lld\n", txt.c_str(), x->occurance);

    for (size_t c = 0; c < 26; c++) {
        if (x->transitions[c]) {
            txt.push_back(c + 'a');
            dfs_print(x->transitions[c]);
            txt.pop_back();
        }
    }  // for
}

int main() {
    initialize();

    Node *tree = build_palindrome_tree();
    dfs_fail(tree);
    // dfs_print(tree);
    // putchar('\n');
    // dfs_print(tree->fail);
    printf("%lld\n", answer);

    return 0;
}  // function main
