// #define NDEBUG
#define NPROFILE
// #define USE_FILE_IO

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <algorithm>

using namespace std;

// #define SEED (time(0))
#define SEED 233
struct MyRandom {
    MyRandom() {
        srand(SEED);
    }

    int operator()() const {
        return rand();
    }
};  // struct MyRandom

static MyRandom randint;

typedef long long longint;

class Treap {
 public:
    Treap(int _key, longint _value);
    ~Treap();

    int key;
    int weight;
    int size;
    longint value;
    longint sum;

    struct Mark {
        longint sum;
    } mark;

    Treap *left;
    Treap *right;

    longint get_sum();

    Treap *left_rotate();
    Treap *right_rotate();

    void update();
    void pushdown();

    Treap *insert(int _key, int _value);
    longint query(int _key);
    Treap *remove(int _key);

 private:
    Treap *remove();
};  // class Treap

static Treap *null = new Treap(0, 0);

Treap::Treap(int _key, longint _value)
        : key(_key)
        , weight(randint())
        , size(1)
        , value(_value)
        , sum(_value)
        , left(null)
        , right(null) {}

Treap::~Treap() {
    // if (left)
    // delete left;
    // if (right)
    // delete right;
}

longint Treap::get_sum() {
    return sum + mark.sum * size;
}

Treap *Treap::left_rotate() {
    assert(mark.sum == 0);
    assert(left->mark.sum == 0);

    Treap *x = this->left;
    this->left = x->right;
    x->right = this;
    this->update();
    x->update();

    return x;
}

Treap *Treap::right_rotate() {
    assert(mark.sum == 0);
    assert(right->mark.sum == 0);

    Treap *x = this->right;
    this->right = x->left;
    x->left = this;
    this->update();
    x->update();

    return x;
}

void Treap::update() {
    size = left->size + right->size + 1;
    sum = left->get_sum() + right->get_sum() + value;
}

void Treap::pushdown() {
    if (mark.sum != 0) {
        value += mark.sum;
        sum += mark.sum * size;

        if (left != null)
            left->mark.sum += mark.sum;
        if (right != null)
            right->mark.sum += mark.sum;

        mark.sum = 0;
        // this->update();
    }
}

Treap *Treap::insert(int _key, int _value) {
    if (this == null) {
        return new Treap(_key, _value);
    }

    this->pushdown();
    if (_key < this->key) {
        this->left = this->left->insert(_key, _value);

        if (this->weight > this->left->weight)
            return this->left_rotate();
    } else {
        this->right = this->right->insert(_key, _value);

        if (this->weight > this->right->weight)
            return this->right_rotate();
    }

    this->update();
    return this;
}

longint Treap::query(int _key) {
    if (this == null)
        return INT_MIN;

    if (_key < this->key)
        return this->left->query(_key);
    else if (_key > this->key)
        return this->right->query(_key);
    else
        return this->value;
}

Treap *Treap::remove() {
    if (this->left != null && this->right != null) {
        this->pushdown();

        Treap *x;
        if (left->weight < right->weight) {
            left->pushdown();
            x = this->left_rotate();
            x->right = x->right->remove();
        } else {
            right->pushdown();
            x = this->right_rotate();
            x->left = x->left->remove();
        }

        x->update();
        return x;
    } else {
        this->pushdown();

        Treap *next;
        if (left != null)
            next = left;
        else
            next = right;
        // delete this;

        return next;
    }
}

Treap *Treap::remove(int _key) {
    this->pushdown();
    if (_key < this->key)
        left = left->remove(_key);
    else if (_key > this->key)
        right = right->remove(_key);
    else
        return this->remove();

    this->update();
    return this;
}

typedef pair<Treap *, Treap *> TreapPair;

static TreapPair split(Treap *h, int k) {
    if (h == null)
        return make_pair(null, null);

    h->pushdown();
    TreapPair result;
    if (k <= h->left->size) {
        result = split(h->left, k);
        h->left = result.second;
        result.second = h;
        h->update();
    } else {
        result = split(h->right, k - h->left->size - 1);
        h->right = result.first;
        result.first = h;
        h->update();
    }

    return result;
}

static Treap *merge(Treap *a, Treap *b) {
    if (a == null)
        return b;
    if (b == null)
        return a;

    if (a->weight < b->weight) {
        a->pushdown();
        a->right = merge(a->right, b);
        a->update();

        return a;
    } else {
        b->pushdown();
        b->left = merge(a, b->left);
        b->update();

        return b;
    }
}

static void initialize() {
    null->size = 0;
    null->left = null;
    null->right = null;

#ifdef USE_FILE_IO
    freopen("interval.in", "r", stdin);
    freopen("interval.out", "w", stdout);
#endif  // IFDEF USE_FILE_IO
}

static void shutdown() {
#ifdef USE_FILE_IO
    fcloseall();
#endif  // IFDEF USE_FILE_IO
}

int main() {
    initialize();

    char buffer[10];
    Treap *tree = null;
    while (scanf("%s", buffer) != EOF) {
        switch (buffer[0]) {
            case 'A': {
                int key, value;
                scanf("%d%d", &key, &value);

                tree = tree->insert(key, value);
            } break;
            case 'D': {
                int key;
                scanf("%d", &key);

                tree = tree->remove(key);
            } break;
            case 'Q': {
                int x, y;
                scanf("%d%d", &x, &y);

                TreapPair a = split(tree, x - 1);
                TreapPair b = split(a.second, y - x + 1);

                printf("%lld\n", b.first->get_sum());
                tree = merge(a.first, merge(b.first, b.second));
            } break;
            case 'C': {
                int x, y, value;
                scanf("%d%d%d", &x, &y, &value);

                TreapPair a = split(tree, x - 1);
                TreapPair b = split(a.second, y - x + 1);
                b.first->mark.sum += value;

                tree = merge(a.first, merge(b.first, b.second));
            } break;
        }  // switch to buffer[0]
    }      // while

    shutdown();
    return 0;
}  // function main
