#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>

#include <algorithm>

using namespace std;

#define NMAX 50000
#define SIGMA 26

typedef long long int64;

class SuffixAutomaton {
 public:
    SuffixAutomaton() : root(new Node), last(root) {}

    void append(char c) {
        Node *p = new Node;
        Node *x = last;

        while (x && !x->trans[c]) {
            x->trans[c] = p;
            x = x->suffix_link;
        }  // while

        if (!x)
            p->suffix_link = root;
        else {
            if (x->right + 1 != x->trans[c]->right) {
                Node *target = x->trans[c];
                Node *y = new Node(*target);

                y->suffix_link = target->suffix_link;
                target->suffix_link = y;
                p->suffix_link = y;
                y->right = x->right + 1;

                while (x && x->trans[c] == target) {
                    x->trans[c] = y;
                    x = x->suffix_link;
                }  // while
            } else
                p->suffix_link = x->trans[c];
        }

        p->right = ++size;
        last = p;
    }

    void process() {
        _process(root);
        root->min = root->max = 0;
        _get_minmax(root);
    }

    int64 count() {
        return _count(root);
    }

 private:
    struct Node {
        Node()
                : in(0)
                , min(INT_MAX)
                , max(INT_MIN)
                , right(0)
                , marked(false)
                , suffix_link(NULL) {
            memset(trans, 0, sizeof(trans));
        }

        int in;
        int min, max;
        int right;
        bool marked;
        Node *suffix_link;
        Node *trans[SIGMA];
    };  // struct Node

    void _process(Node *x) {
        for (char c = 0; c < SIGMA; c++) {
            Node *v = x->trans[c];

            if (v) {
                v->in++;

                if (v->in == 1)
                    _process(v);
            }
        }  // for
    }

    void _get_minmax(Node *x) {
        for (char c = 0; c < SIGMA; c++) {
            Node *v = x->trans[c];

            if (v) {
                v->min = min(v->min, x->min + 1);
                v->max = max(v->max, x->max + 1);
                v->in--;

                if (!v->in)
                    _get_minmax(v);
            }
        }  // for
    }

    int64 _count(Node *x) {
        x->marked = true;
        int64 answer = 0;
        for (char c = 0; c < SIGMA; c++) {
            Node *v = x->trans[c];

            if (v && !v->marked)
                answer += _count(v);
        }  // for

        return answer + x->max - x->min + 1;
    }

    int size;
    Node *root;
    Node *last;
};  // class SuffixAutomaton

static int n;
static char str[NMAX + 10];

int main() {
    freopen("subst1.in", "r", stdin);
    freopen("subst1.out", "w", stdout);

    scanf("%s", str);
    n = strlen(str);

    SuffixAutomaton *mac = new SuffixAutomaton;
    for (size_t i = 0; str[i]; i++) {
        mac->append(str[i] - 'A');
    }  // for

    mac->process();
    printf("%lld\n", mac->count() - 1);

    return 0;
}  // function main
