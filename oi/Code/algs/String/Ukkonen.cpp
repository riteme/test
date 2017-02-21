#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

#define NMAX 100000
#define SIGMA 256

class SuffixTree;
void show(SuffixTree &tree);

class SuffixTree {
 public:
    SuffixTree() : size(0) {
        root = new Node;
        active = root;
    }
    // ~SuffixTree();

    void trie(char *s) {
        memcpy(str + 1, s, strlen(s));

        for (int i = 1; str[i]; i++) {
            trie_insert(str + i, i);
        }  // for
    }

    void trie_insert(char *s, int start) {
        Node *cur = root;
        for (size_t i = 0; s[i]; i++) {
            char c = s[i];

            if (!cur->trans[c])
                cur->trans[c] = new Edge(start + i, start + i, new Node);

            cur = cur->trans[c]->next;
        }  // for
    }

    void add_char(char c) {
        // static Node *active = root;
        // static char active_trans = -1;
        // static int active_len = 0;
        // static int remain = 0;
        str[++size] = c;

        Node *last = nullptr;
        while (remain >= 0) {
            // Correct active point
            if (active == root && remain < active_len) {
                if (remain) {
                    active_trans = str[size - remain];
                    active_len = remain;
                } else {
                    active_trans = -1;
                    active_len = 0;
                }

                show(*this);
            }

            assert(remain >= active_len);

            while (active_trans >= 0 &&
                   active_len >= length(active->trans[active_trans])) {
                active_len -= length(active->trans[active_trans]);
                active = active->trans[active_trans]->next;

                if (active_len)
                    active_trans = str[size - active_len];
                else
                    active_trans = -1;
            }  // while

            // Try going towards
            if (active_trans < 0) {
                if (active->trans[c]) {
                    active_trans = c;
                    active_len = 1;
                    remain++;

                    if (last)
                        last->suffix_link = active;

                    show(*this);
                    return;
                }
            } else if (str[active->trans[active_trans]->left + active_len] ==
                       c) {
                active_len++;
                remain++;

                if (last)
                    last->suffix_link = active;

                show(*this);
                return;
            }

            assert(active_trans < 0 ||
                   active_len < length(active->trans[active_trans]));

            // Check and insert empty suffix
            if (remain == 0) {
                assert(active == root);
                assert(!root->trans[c]);

                root->trans[c] = new Edge(size, 0, new Node);

                if (last)
                    last->suffix_link = root;

                show(*this);
                return;
            }

            // Create new nodes
            Node *x;
            if (active_len == 0) {
                assert(!active->trans[c]);

                active->trans[c] = new Edge(size, 0, new Node);
                x = active;
            } else {
                Edge *t = active->trans[active_trans];
                x = new Node;

                x->trans[c] = new Edge(size, 0, new Node);
                x->trans[str[t->left + active_len]] =
                    new Edge(t->left + active_len, t->right, t->next);
                t->right = t->left + active_len - 1;
                t->next = x;
            }

            if (last)
                last->suffix_link = x;
            last = x;

            show(*this);

            // Go back along suffix link
            if (active->suffix_link)
                active = active->suffix_link;
            else
                active = root;
            remain--;

            show(*this);
        }  // while
    }

    void print(stringstream &buffer) {
        buffer << "digraph {" << endl;
        buffer
            << "node[shape=circle width=0.4 "
               "height=0.4 fixedsize=true "
               "fontname=\"consolas\"];edge[fontname=\"consolas\"];rankdir=LR;"
            << endl;
        buffer << remain << ";" << endl;
        _print(root, buffer);
        buffer << "}" << endl;
    }

 private:
    struct Node {
        Node() : suffix_link(nullptr) {
            memset(trans, 0, sizeof(trans));
        }

        struct Edge {
            Edge() : left(0), right(0), next(nullptr) {}
            Edge(int l, int r, Node *nxt) : left(l), right(r), next(nxt) {}

            int left;
            int right;
            Node *next;
        };  // struct Edge

        Node *suffix_link;
        Edge *trans[SIGMA];
    };  // struct Node

    typedef Node::Edge Edge;

    int length(const Edge *e) const {
        if (e->right == 0)
            return size - e->left + 1;
        return e->right - e->left + 1;
    }

    void _print(Node *x, stringstream &buffer) {
#define IDX(ptr) reinterpret_cast<unsigned long long>(ptr)

        if (!x)
            return;

        buffer << IDX(x) << "[";

        if (x == active)
            buffer << " color=red label=\"" << active_len << "/"
                   << (active_trans >= 0 ? static_cast<char>(active_trans)
                                         : '*')
                   << "\"";
        // buffer << " color=red label=\"\"";
        else
            buffer << "label=\"\"";

        buffer << "];" << endl;

        // if (x->suffix_link)
        //     buffer << IDX(x) << "->" << IDX(x->suffix_link) << "[style=dashed];"
        //            << endl;

        for (int c = 0; c < SIGMA; c++) {
            Edge *t = x->trans[c];

            if (!t)
                continue;

            buffer << IDX(x) << "->" << IDX(t->next) << "[label=\"";
            for (int i = t->left; i <= (t->right ? t->right : size); i++) {
                buffer << str[i];
            }

            buffer << "\"";

            if (x == active && c == active_trans)
                buffer << " color=red";

            buffer << "];" << endl;

            _print(t->next, buffer);
        }

#undef ID
    }

    Node *root;

    int size;
    char str[NMAX + 10];
    Node *active;
    char active_trans = -1;
    int active_len = 0;
    int remain = 0;
};  // class SuffixTree

void show(SuffixTree &tree) {
    static int cnt = 0;
    cnt++;

    stringstream buf;
    tree.print(buf);
    ofstream writer("/tmp/suffix-tree.dot");
    writer << buf.str();
    writer.close();
    system((string("dot /tmp/suffix-tree.dot -Tsvg > /tmp/suffix-tree-") +
            to_string(cnt) + ".svg")
               .data());
}

int main() {
    char buffer[1024];
    SuffixTree tree;
    scanf("%s", buffer);

    // tree.trie(buffer);
    for (size_t pos = 0; buffer[pos]; pos++) {
        tree.add_char(buffer[pos]);
    }  // for
    show(tree);

    return 0;
}  // function main
