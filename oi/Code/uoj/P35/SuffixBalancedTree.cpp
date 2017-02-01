#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

static struct MyRandom {
    static constexpr int SEED = 577777777;

    MyRandom() {
        srand(SEED);
    }

    int operator()() const {
        return rand();
    }
} randint;  // struct MyRandom

class Hasher {
 public:
    typedef pair<unsigned int, unsigned long long> CodeType;

    Hasher() : size(0) {
        bin1[0] = bin2[0] = 1;
        val1[0] = val2[0] = 0;
    }

    void append(char c) {
        str[++size] = c;
        bin1[size] = bin1[size - 1] * BASE1;
        val1[size] = val1[size - 1] * BASE1 + c;
        bin2[size] = bin2[size - 1] * BASE2;
        val2[size] = val2[size - 1] * BASE2 + c;
    }

    CodeType hash(int left, int right) const {
        // printf("left = %d, right = %d\n", left, right);
        // assert(0 < left && left <= size);
        // assert(left <= right && right <= size);
        return make_pair(val1[right] - val1[left - 1] * bin1[right - left + 1],
                         val2[right] - val2[left - 1] * bin2[right - left + 1]);
    }

    bool equal(int l1, int r1, int l2, int r2) const {
        if (r1 - l1 != r2 - l2)
            return false;
        if (r1 < l1)
            return true;
        return hash(l1, r1) == hash(l2, r2);
    }

    // Length of longest common suffix
    int lcs(int p1, int p2) {
        int left = 0, right = min(p1, p2);
        while (left + 1 < right) {
            int mid = (left + right) / 2;

            if (equal(p1 - mid + 1, p1, p2 - mid + 1, p2))
                left = mid;
            else
                right = mid - 1;
        }

        if (left != right && equal(p1 - right + 1, p1, p2 - right + 1, p2))
            left = right;

        return left;
    }

    char get_char(const int i) const {
        // assert(1 <= i && i <= size);
        return str[i];
    }

    int get_size() const {
        // assert(0 <= size && size <= NMAX + 1);
        return size;
    }

 private:
    static constexpr unsigned int BASE1 = 257;
    static constexpr unsigned long long BASE2 = 277;

    int size;
    unsigned int bin1[NMAX + 10];
    unsigned int val1[NMAX + 10];
    unsigned long long bin2[NMAX + 10];
    unsigned long long val2[NMAX + 10];
    char str[NMAX + 10];
};  // class Hasher

class SuffixBalancedTree {
 public:
    SuffixBalancedTree() : root(nullptr) {}

    void append(char c) {
        hash.append(c);
        root = _insert(root, hash.get_size());
    }

    void get_sa(int *arr) {
        int p = 0;
        _get_sa(root, p, arr);
    }

 private:
    struct Node {
        Node(int _key)
            : key(_key), weight(randint()), left(nullptr), right(nullptr) {}

        int key;
        int weight;
        Node *left;
        Node *right;

        Node *left_rotate() {
            Node *y = left;
            left = y->right;
            y->right = this;

            return y;
        }

        Node *right_rotate() {
            Node *y = right;
            right = y->left;
            y->left = this;

            return y;
        }
    };  // struct Node

    Node *_insert(Node *x, int key) {
        if (!x)
            return new Node(key);

        int lcs = hash.lcs(x->key, key);
        if (hash.get_char(key - lcs) < hash.get_char(x->key - lcs)) {
            x->left = _insert(x->left, key);

            if (x->left->weight < x->weight)
                return x->left_rotate();
        } else {
            x->right = _insert(x->right, key);

            if (x->right->weight < x->weight)
                return x->right_rotate();
        }

        return x;
    }

    void _get_sa(Node *x, int &pos, int *arr) {
        if (!x)
            return;

        _get_sa(x->left, pos, arr);
        // assert(pos <= hash.get_size());
        arr[++pos] = x->key;
        _get_sa(x->right, pos, arr);
    }

    Hasher hash;
    Node *root;
};  // class SuffixBalancedTree

static int n;
static char buffer[NMAX + 10];
static int sa[NMAX + 10];
static int rnk[NMAX + 10];
static int lcp[NMAX + 10];

int main() {
    scanf("%s", buffer + 1);
    n = strlen(buffer + 1);
    buffer[n + 1] = '$';

    SuffixBalancedTree *tree = new SuffixBalancedTree;
    for (int i = n + 1; i >= 1; i--) {
        tree->append(buffer[i]);
    }  // for
    tree->get_sa(sa);

    for (int i = 1; i <= n; i++) {
        sa[i] = n + 2 - sa[i + 1];
    }  // for

    for (int i = 1; i <= n; i++) {
        rnk[sa[i]] = i;
    }  // for

    int j = 0;
    for (int i = 1; i <= n; i++) {
        if (rnk[i] == 1)
            continue;

        j--;

        if (j < 0)
            j = 0;

        while (buffer[sa[rnk[i]] + j] == buffer[sa[rnk[i] - 1] + j]) {
            j++;
        }  // while

        lcp[rnk[i]] = j;
    }  // for

    for (int i = 1; i <= n; i++) {
        printf("%d ", sa[i]);
    }  // for
    printf("\n");

    for (int i = 2; i <= n; i++) {
        printf("%d ", lcp[i]);
    }  // for
    printf("\n");

    return 0;
}  // function main
