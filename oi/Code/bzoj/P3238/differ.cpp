#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 500000
#define SIGMA 27
#define EOFCHAR 26

typedef long long int64;

class SuffixTree {
 public:
    SuffixTree(char *buf) : size(strlen(buf + 1)), str(buf), root(new Node) {
        for (int i = 1; i <= size; i++) {
            str[i] -= 'a';
            append(str[i]);
        }  // for
        append(EOFCHAR);
    }

    int64 solve() {
        return size * (size + 1) / 2 * (size - 1) - _solve(root);
    }

 private:
    struct Node {
        struct Edge {
            Edge(int l, int r, Node *nxt) : left(l), right(r), next(nxt) {}

            int length() const {
                return right - left + 1;
            }

            int left;
            int right;
            Node *next;
        };  // struct Edge

        Node() : count(0), depth(0), suffix_link(NULL) {
            memset(trans, 0, sizeof(trans));
        }

        int64 count;
        int64 depth;
        Node *suffix_link;
        Edge *trans[SIGMA];
    };  // struct Node

    typedef Node::Edge Edge;

    void append(char c) {
        static Node *active = root;
        static char dir = -1;
        static int len = 0, cnt = 0, cur = 0;

        cur++;
        cnt++;
        Node *last = NULL;
        while (cnt) {
            if (cnt - 1 < len) {
                len = cnt - 1;
                dir = len ? str[cur - len] : -1;
            }

            while (dir >= 0 && len >= active->trans[dir]->length()) {
                len -= active->trans[dir]->length();
                active = active->trans[dir]->next;
                dir = len ? str[cur - len] : -1;
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
                active->trans[c] = new Edge(cur, size, new Node);
                x = active;
            } else {
                Edge *t = active->trans[dir];
                x = new Node;
                x->trans[c] = new Edge(cur, size, new Node);
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
    }

    int64 _solve(Node *x) {
        int64 answer = 0;
        bool has_child = false;
        for (char c = 0; c < SIGMA; c++) {
            Edge *t = x->trans[c];

            if (!t)
                continue;

            has_child = true;
            Node *v = t->next;
            v->depth = x->depth + t->length();
            answer += _solve(v);
            x->count += v->count;
        }  // for

        if (!has_child)
            x->count = 1;

        for (char c = 0; c < SIGMA; c++) {
            Edge *t = x->trans[c];

            if (!t)
                continue;

            Node *v = t->next;
            answer += x->depth * v->count * (x->count - v->count);
        }  // for

        return answer;
    }

    int64 size;
    char *str;
    Node *root;
};  // class SuffixTree

static char buffer[NMAX + 10];

int main() {
    scanf("%s", buffer + 1);
    SuffixTree *tree = new SuffixTree(buffer);

    printf("%lld\n", tree->solve());

    return 0;
}  // function main
