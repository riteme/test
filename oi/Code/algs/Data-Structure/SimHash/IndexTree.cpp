// Failed

#include <cassert>
#include <cstdints>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

class IndexTree {
 public:
    typedef unordered_map<uint64_t, size_t> HashMap;

    IndexTree(const HashMap &data, const int base, const int k)
        : _base(base), _k(k) {
        root = new Node;
        root->data = new HashMap(data);
        setup(root, base, k);
    }

    ~IndexTree() {
        delete root;
    }

    size_t search(const uint64_t key) {}

 private:
    struct Node {
        ~Node() {
            if (data) {
                delete data;

                assert(partition.empty());
            } else {
                for (auto &sub : partition) {
                    assert(sub);

                    delete sub;
                }  // foreach in partition
            }
        }

        struct Subnode {
            Subnode(int _left, int _right) : left(_left), right(_right) {}

            ~Subnode() {
                for (auto &e : match) {
                    if (e)
                        delete e;
                }  // foreach in match
            }

            uint64_t extract(const uint64_t &v) {
                uint64_t mask = ((1ULL << right) - 1) - ((1ULL << left) - 1);
                return (v & mask) >> left;
            }

            uint64_t reduce(const uint64_t &v) {
                uint64_t pre = (v >> right) << left;
                uint64_t suf = v & ((1ULL << left) - 1);
                return pre + suf;
            }

            int left, right;
            vector<Node *> match;
        };  // struct Subnode

        vector<Subnode *> partition;
        HashMap *data;
    };  // struct Node

    Node::Subnode *make_partition(const HashMap &data, const int base,
                                  const int left, const int right,
                                  const int k) {
        Node::Subnode *u = new Node::Subnode(left, right);
        u->match.resize(1 << (right - left + 1), nullptr);

        for (auto &p : data) {
            uint64_t id = u->extract(p.first);
            uint64_t val = u->reduce(p.first);
            int cnt = p.second;

            if (!u->match[id]) {
                u->match[id] = new Node;
                u->match[id]->data = new HashMap;
            }

            u->match[id]->data[val] += cnt;
        }  // foreach in data

        for (auto &e : u->match) {
            if (e)
                setup(e, base - (right - left + 1), k);
        }  // foreach in u->match

        return u;
    }

    void setup(Node *node, const int base, const int k) {
        if (k > base) {
            int len = base / k;
            for (int l = 0; l + len <= base; l += len) {
                int r = (l + 2 * len > base ? base - 1 : l + len - 1);
                node->partition.push_back(
                    make_partition(node->data, base, l, r, k));
            }  // for

            delete node->data;
            node->data = nullptr;
        }
    }

    size_t _search(Node *x, const uint64_t key) {
        if (x->data) {
            size_t answer = 0;

            for (auto &p : x->data) {
            }  // foreach in x->data
        }
    }

    int _base;
    int _k;
    Node *root;
};  // class IndexTree
