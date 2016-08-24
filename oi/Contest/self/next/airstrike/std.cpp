#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

#include <vector>
#include <utility>
#include <algorithm>

using std::vector;
using std::pair;
using std::sort;
using std::min;
using std::max;

typedef long long int64;

struct Vector2 {
    Vector2() : x(0), y(0) {}
    Vector2(const int64 _x, const int64 _y) : x(_x), y(_y) {}
    Vector2(const Vector2 &lhs) : x(lhs.x), y(lhs.y) {}
    Vector2(Vector2 &&rhs) : x(rhs.x), y(rhs.y) {}

    Vector2 &operator=(const Vector2 &lhs) {
        x = lhs.x;
        y = lhs.y;

        return *this;
    }

    Vector2 &operator=(Vector2 &&rhs) {
        x = rhs.x;
        y = rhs.y;

        return *this;
    }

    bool operator==(const Vector2 &lhs) const {
        return x == lhs.x && y == lhs.y;
    }

    bool operator!=(const Vector2 &lhs) const {
        return x != lhs.x || y != lhs.y;
    }

    Vector2 operator+(const Vector2 &lhs) const {
        return Vector2(x + lhs.x, y + lhs.y);
    }

    Vector2 operator-(const Vector2 &lhs) const {
        return Vector2(x - lhs.x, y - lhs.y);
    }

    Vector2 operator*(const int64 lhs) const {
        return Vector2(x * lhs, y * lhs);
    }

    Vector2 &operator+=(const Vector2 &lhs) {
        x += lhs.x;
        y += lhs.y;

        return *this;
    }

    Vector2 &operator-=(const Vector2 &lhs) {
        x -= lhs.x;
        y -= lhs.y;

        return *this;
    }

    Vector2 &operator*=(const int64 lhs) {
        x *= lhs;
        y *= lhs;

        return *this;
    }

    int64 x, y;
};  // struct Vector2

inline int64 dot(const Vector2 &a, const Vector2 &b) noexcept {
    return a.x * b.x + a.y * b.y;
}

inline int64 cross(const Vector2 &a, const Vector2 &b) noexcept {
    return a.x * b.y - a.y * b.x;
}

struct Line {
    Line() : reversed(false) {}
    Line(const Vector2 &p1, const Vector2 &p2) {
        if (p1.x < p2.x) {
            left = p1;
            right = p2;
            reversed = false;
        } else {
            left = p2;
            right = p1;
            reversed = true;
        }
    }
    Line(const Line &lhs)
            : left(lhs.left), right(lhs.right), reversed(lhs.reversed) {}
    Line(Line &&rhs)
            : left(rhs.left), right(rhs.right), reversed(rhs.reversed) {}

    bool operator==(const Line &lhs) const {
        return left == lhs.left && right == lhs.right;
    }

    bool is_on_line(const Vector2 &p) const {
        return cross(right - left, p - left) == 0;
    }

    bool is_upper(const Vector2 &p) const {
        return cross(right - left, p - left) > 0;
    }

    bool is_lower(const Vector2 &p) const {
        return cross(right - left, p - left) < 0;
    }

    bool is_in_range(const Vector2 &p) const {
        if (is_on_line(p))
            return true;

        if (reversed)
            return is_lower(p);
        else
            return is_upper(p);
    }

    bool is_out_range(const Vector2 &p) const {
        return !is_in_range(p);
    }

    bool is_horizontal() const {
        return left.y == right.y;
    }

    bool is_vertical() const {
        return left.x == right.x;
    }

    Vector2 left;
    Vector2 right;
    bool reversed;
};  // struct Line

constexpr int RandomSeed = 23324;

struct Random {
    Random() {
        srand(RandomSeed);
    }

    int operator()() const {
        return rand();
    }
};  // struct Random

static Random randint;

struct Treap {
    Treap() : key(nullptr), left(nullptr), right(nullptr), weight(randint()) {}
    Treap(Line *line)
            : key(line), left(nullptr), right(nullptr), weight(randint()) {}
    Treap(const Treap &lhs)
            : key(lhs.key)
            , left(lhs.left)
            , right(lhs.right)
            , weight(lhs.weight) {}
    Treap(Treap &&lhs)
            : key(lhs.key)
            , left(lhs.left)
            , right(lhs.right)
            , weight(lhs.weight) {}

    Line *key;
    Treap *left;
    Treap *right;
    int weight;
};  // struct Treap

typedef pair<Treap *, Treap *> TreapPair;

inline Treap *left_rotate(Treap *x) {
    assert(x);
    assert(x->left);

    Treap *y = x->left;
    x->left = y->right;
    y->right = x;

    return y;
}

inline Treap *right_rotate(Treap *x) {
    assert(x);
    assert(x->right);

    Treap *y = x->right;
    x->right = y->left;
    y->left = x;

    return y;
}

template <typename TCompare>
static Treap *persistent_insert(Treap *h, Line *key, const TCompare &cmp) {
    if (!h)
        return new Treap(key);

    Treap *x = new Treap(*h);
    if (cmp(key, x->key)) {
        x->left = persistent_insert(x->left, key, cmp);

        if (x->left->weight < x->weight)
            return left_rotate(x);
    } else {
        x->right = persistent_insert(x->right, key, cmp);

        if (x->right->weight < x->weight)
            return right_rotate(x);
    }

    return x;
}

static Treap *persistent_remove(Treap *h) {
    if (h->left != nullptr && h->right != nullptr) {
        if (h->left->weight < h->right->weight) {
            h->left = new Treap(*h->left);
            Treap *y = left_rotate(h);

            y->right = persistent_remove(h);

            return y;
        } else {
            h->right = new Treap(*h->right);
            Treap *y = right_rotate(h);

            y->left = persistent_remove(h);

            return y;
        }
    } else {
        Treap *next = h->left;

        if (h->right != nullptr)
            next = h->right;

        // delete h;

        return next;
    }
}

template <typename TCompare>
static Treap *persistent_remove(Treap *h, Line *key, const TCompare &cmp) {
    assert(h != nullptr);

    Treap *x = new Treap(*h);
    if ((*x->key) == (*key))
        return persistent_remove(x);
    else if (cmp(key, x->key))
        x->left = persistent_remove(x->left, key, cmp);
    else
        x->right = persistent_remove(x->right, key, cmp);

    return x;
}

template <typename TCompare>
inline TreapPair query_range(Treap *h, const Vector2 &p, const TCompare &cmp) {
    Treap *x = h;
    TreapPair result(nullptr, nullptr);
    while (x) {
        if (cmp(p, x->key)) {
            result.second = x;
            x = x->left;
        } else {
            result.first = x;
            x = x->right;
        }
    }  // while

    return result;
}

// static void print_tree(Treap *x) {
//     if (!x)
//         return;

//     print_tree(x->left);

//     printf("(%lld, %lld) - (%lld, %lld),\n", x->key->left.x, x->key->left.y,
//            x->key->right.x, x->key->right.y);

//     print_tree(x->right);
// }

enum class EventType {
    Enter,
    Exit,
};  // enum class EventType

struct EventPoint {
    EventPoint() : line(nullptr) {}
    EventPoint(Line *_line, const EventType _type) : line(_line), type(_type) {}
    EventPoint(const EventPoint &lhs) : line(lhs.line), type(lhs.type) {}
    EventPoint(EventPoint &&lhs) : line(lhs.line), type(lhs.type) {}

    EventPoint &operator=(const EventPoint &lhs) {
        line = lhs.line;
        type = lhs.type;

        return *this;
    }

    EventPoint &operator=(EventPoint &&lhs) {
        line = lhs.line;
        type = lhs.type;

        return *this;
    }

    Line *line;
    EventType type;
};  // struct EventPoint

class Polgyon {
 public:
    Polgyon(const vector<Vector2> &points) : latest(nullptr) {
        x.reserve(points.size());
        edges.reserve(points.size());
        events.reserve(points.size() * 2);
        version.reserve(points.size());

        for (auto beg = points.begin(); beg != points.end(); beg++) {
            x.push_back(beg->x);

            auto next = beg + 1;
            if (next == points.end())
                edges.push_back(Line(*beg, *points.begin()));
            else
                edges.push_back(Line(*beg, *next));

            assert(&edges.back());
            events.push_back(EventPoint(&edges.back(), EventType::Enter));
            events.push_back(EventPoint(&edges.back(), EventType::Exit));
        }  // for

        sort(x.begin(), x.end());
        auto iter = std::unique(x.begin(), x.end());
        x.resize(std::distance(x.begin(), iter));

        stable_sort(events.begin(),
                    events.end(),
                    [](const EventPoint &a, const EventPoint &b) {
                        assert(a.line != nullptr);
                        assert(b.line != nullptr);

                        int64 ax = a.type == EventType::Enter ? a.line->left.x
                                                              : a.line->right.x;
                        int64 bx = b.type == EventType::Enter ? b.line->left.x
                                                              : b.line->right.x;
                        return ax < bx ||
                               (ax == bx && a.type == EventType::Exit);
                    });

        // printf("x: ");
        // for (auto &e : x) {
        //     printf("%lld ", e);
        // }  // foreach in x
        // printf("\n");

        // printf("Event Points: \n");
        // for (auto &e : events) {
        //     printf("(%lld, %lld) - (%lld, %lld): %d\n", e.line->left.x,
        //            e.line->left.y, e.line->right.x, e.line->right.y,
        //            (e.type == EventType::Enter ? 1 : 0));
        // }  // foreach in events

        _scan_once();
    }

    bool contain(const Vector2 &p) const {
        if (p.x < x.front() || p.x > x.back())
            return false;

        size_t left = 1, right = x.size() - 1;
        while (left + 1 < right) {
            int mid = (left + right) / 2;

            if (x[mid] <= p.x)
                left = mid;
            else
                right = mid;
        }  // while

        if (left != right && x[left] <= p.x)
            left = right;

        return _test(left, p) || (x[left - 1] == p.x && _test(left - 1, p));
    }

 private:
    bool _test(size_t i, const Vector2 &p) const {
        Treap *tree = version[i];
        TreapPair result = query_range(tree,
                                       p,
                                       [](const Vector2 &p, const Line *line) {
                                           return line->is_lower(p);
                                       });

        Treap *x = result.first;
        Treap *y = result.second;
        if ((x != NULL && x->key->is_on_line(p)) ||
            (y != NULL && y->key->is_on_line(p)))
            return true;
        return x != NULL && y != NULL && x->key->is_in_range(p) &&
               y->key->is_in_range(p);
    }

    void _scan_once() {
        auto pos = x.begin();
        auto iter = events.begin();

        while (pos != x.end() && iter != events.end()) {
            int64 current = *pos;
            version.push_back(latest);

            // print_tree(latest);
            // printf("current = %lld\n", current);

            auto cmp = [](const Line *a, const Line *b) {
                if (a->left == b->left)
                    return a->is_upper(b->right);
                else if (a->right == b->right)
                    return a->is_upper(b->left);

                if ((a->is_upper(b->left) && a->is_lower(b->right)) ||
                    (a->is_lower(b->left) && a->is_upper(b->right)) ||
                    a->is_on_line(b->left) || a->is_on_line(b->right))
                    return b->is_lower(a->left) && b->is_lower(a->right);
                else
                    return a->is_upper(b->left) && a->is_upper(b->right);
            };

            while (iter != events.end()) {
                if (iter->line->is_vertical()) {
                    iter++;
                    continue;
                }

                if (current == (iter->type == EventType::Enter
                                    ? iter->line->left.x
                                    : iter->line->right.x)) {
                    // printf("Processing (%lld, %lld) - (%lld, %lld): %d...\n",
                    // iter->line->left.x, iter->line->left.y,
                    // iter->line->right.x, iter->line->right.y,
                    // (iter->type == EventType::Enter ? 1 : 0));

                    if (iter->type == EventType::Enter)
                        latest = persistent_insert(latest, iter->line, cmp);
                    else
                        latest = persistent_remove(latest, iter->line, cmp);

                    iter++;
                } else
                    break;
            }

            pos++;
        }  // while
    }

    vector<int64> x;
    vector<Line> edges;
    vector<EventPoint> events;
    Treap *latest;
    vector<Treap *> version;
};  // class Polgyon

int main() {
    int n;
    scanf("%d", &n);

    vector<Vector2> points;
    for (int i = 0; i < n; i++) {
        int64 x, y;
        scanf("%lld%lld", &x, &y);

        points.push_back(Vector2(x, y));
    }  // for

    Polgyon shape(points);

    int64 x, y;
    while (scanf("%lld%lld", &x, &y) != EOF) {
        bool result = shape.contain(Vector2(x, y));

        puts(result ? "YES" : "NO");
    }  // while

    return 0;
}  // function main
