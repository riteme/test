#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 50000
#define SIGMA 27
#define EOFCHAR 26

typedef long long int64;

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
    }

    int64 solve() {
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

        Node() : suffix_link(NULL) {
            memset(trans, 0, sizeof(trans));
        }

        Node *suffix_link;
        Edge *trans[SIGMA];
    };  // struct Node

    typedef Node::Edge Edge;

    int length(const Edge *e) {
        return e->right ? e->right - e->left + 1 : size - e->left + 1;
    }

    int64 _solve(Node *x) {
        int64 answer = 0;

        for (char p = 0; p < SIGMA; p++) {
            Edge *t = x->trans[p];

            if (t) {
                answer += length(t);
                answer += _solve(t->next);
            }
        }  // for

        return answer;
    }

    int size;
    char str[NMAX + 10];
    Node *root;
};  // class SuffixTree

static int64 n;
static char buf[NMAX + 10];

int main() {
    freopen("subst1.in", "r", stdin);
    freopen("subst1.out", "w", stdout);

    scanf("%s", buf);
    n = strlen(buf);

    SuffixTree *tree = new SuffixTree;
    for (size_t pos = 0; buf[pos]; pos++) {
        tree->append(buf[pos] - 'A');
    }  // for
    tree->append(EOFCHAR);
    printf("%lld\n", tree->solve() - n - 1);

    return 0;
}  // function main
