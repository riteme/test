#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define SIGMA 28
#define EOFCHAR1 26
#define EOFCHAR2 27

class SuffixTree {
 public:
    SuffixTree() : size(0), root(new Node) {}

    void append(char c) {
        static Node *active = root;
        static char dir = -1;
        static int len = 0;
        static int cnt = 0;

        cnt++;
        Node *last = NULL;
        while (cnt) {
            if (cnt - 1 < len) {
                assert(active == root);

                len = cnt - 1;
                dir = len ? str[size - len + 1] : -1;
            }

            while (dir >= 0 && len >= length(active->trans[dir])) {
                len -= length(active->trans[dir]);
                active = active->trans[dir]->next;
                dir = len ? str[size - len + 1] : -1;
            }  // while

            if ((dir < 0 && active->trans[c]) ||
                (dir >= 0 && c == str[active->trans[dir]->left + len])) {
                if (dir < 0)
                    dir = c;

                len++;

                if (last)
                    last->suffix_link = active;

                break;
            }

            Node *x;
            if (dir < 0) {
                active->trans[c] = new Edge(size + 1, 0, new Node);
                x = active;
            } else {
                Edge *t = active->trans[dir];
                x = new Node;
                x->trans[c] = new Edge(size + 1, 0, new Node);
                x->trans[str[t->left + len]] =
                    new Edge(t->left + len, t->right, t->next);
                t->right = t->left + len - 1;
                t->next = x;
            }

            if (last)
                last->suffix_link = x;
            last = x;

            active = active->suffix_link ? active->suffix_link : root;
            cnt--;
        }  // while

        str[++size] = c;
        if (c == EOFCHAR1)
            eof1 = size;
        else if (c == EOFCHAR2)
            eof2 = size;
    }

    void reset() {
        _reset(root);
    }

    void process_mask() {
        _process_mask(root);
    }

    int solve() {
        return _solve(root);
    }

 private:
    struct Node {
        struct Edge {
            Edge(int l, int r, Node *nxt) : left(l), right(r), next(nxt) {}

            int left;
            int right;
            Node *next;
        };  // struct Edge

        Node() : mask(0), depth(0), suffix_link(NULL) {
            memset(trans, 0, sizeof(trans));
        }

        char mask;
        int depth;
        Node *suffix_link;
        Edge *trans[SIGMA];
    };  // struct Node

    typedef Node::Edge Edge;

    int length(const Edge *e) {
        return e->right ? e->right - e->left + 1 : size - e->left + 1;
    }

    void _reset(Node *x) {
        for (char p = 0; p < SIGMA; p++) {
            if (x->trans[p]) {
                Edge *t = x->trans[p];

                if (!t->right)
                    t->right = size;

                _reset(t->next);
            }
        }  // for
    }

    int _process_mask(Node *x) {
        for (char p = 0; p < SIGMA; p++) {
            Edge *t = x->trans[p];

            if (t) {
                t->next->depth = x->depth + length(t);

                if (t->left <= eof1 && eof1 <= t->right)
                    x->mask |= 1;
                if (t->left <= eof2 && eof2 <= t->right)
                    x->mask |= 2;

                x->mask |= _process_mask(t->next);
            }
        }  // for

        return x->mask;
    }

    int _solve(Node *x) {
        int answer = x->mask == 3 ? x->depth : 0;

        for (char p = 0; p < SIGMA; p++) {
            if (x->trans[p]) {
                answer = max(answer, _solve(x->trans[p]->next));
            }
        }  // for

        return answer;
    }

    int eof1, eof2;
    int size;
    char str[NMAX * 2 + 10];
    Node *root;
};  // class SuffixTree

static char buf1[NMAX + 10];
static char buf2[NMAX + 10];

int main() {
    scanf("%s%s", buf1, buf2);
    SuffixTree *tree = new SuffixTree;

    for (size_t pos = 0; buf1[pos]; pos++) {
        tree->append(buf1[pos] - 'a');
    }  // for
    tree->append(EOFCHAR1);
    tree->reset();

    for (size_t pos = 0; buf2[pos]; pos++) {
        tree->append(buf2[pos] - 'a');
    }  // for
    tree->append(EOFCHAR2);
    tree->reset();

    tree->process_mask();
    printf("%d\n", tree->solve());

    return 0;
}  // function main
