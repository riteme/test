// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

//////////////////////
// Float comparison //
//////////////////////

#define EPSILON 0.0000001

template <typename T>
inline bool almost_equal(const T &a, const T &b) {
    return fabs(a - b) < EPSILON;
}

///////////////
// 2D Vector //
///////////////

enum Clockwise {
    PARALLEL = 1 << 0,
    CW = 1 << 1,
    CCW = 1 << 2
};  // enum Clockwise

struct Vector2 {
    Vector2() : x(0.0), y(0.0) {}
    Vector2(const double &_x, const double &_y) : x(_x), y(_y) {}

    double x, y;

    Vector2 &operator+=(const Vector2 &b) {
        x += b.x;
        y += b.y;

        return *this;
    }

    Vector2 &operator-=(const Vector2 &b) {
        x -= b.x;
        y -= b.y;

        return *this;
    }

    Vector2 &operator*=(const double &b) {
        x *= b;
        y *= b;

        return *this;
    }

    friend Vector2 operator+(const Vector2 &a, const Vector2 &b);
    friend Vector2 operator-(const Vector2 &a, const Vector2 &b);
    friend Vector2 operator*(const Vector2 &a, const double &b);

    bool operator<(const Vector2 &b) const {
        return x < b.x;
    }

    bool operator==(const Vector2 &b) const {
        return x == b.x && y == b.y;
    }
};  // struct Vector2

inline Vector2 operator+(const Vector2 &a, const Vector2 &b) {
    return Vector2(a.x + b.x, a.y + b.y);
}

inline Vector2 operator-(const Vector2 &a, const Vector2 &b) {
    return Vector2(a.x - b.x, a.y - b.y);
}

inline Vector2 operator*(const Vector2 &a, const double &b) {
    return Vector2(a.x * b, a.y * b);
}

inline double dot(const Vector2 &a, const Vector2 &b) {
    return a.x * b.x + a.y * b.y;
}

inline double cross(const Vector2 &a, const Vector2 &b) {
    return a.x * b.y - a.y * b.x;
}

inline double length(const Vector2 &a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

inline Vector2 normalize(const Vector2 &a) {
    return a * (1.0 / length(a));
}

inline Clockwise turn(const Vector2 &u, const Vector2 &v, const Vector2 &p) {
    double result = cross(v - u, p - u);

    if (almost_equal(result, 0.0))
        return PARALLEL;
    else if (result > 0.0)
        return CCW;
    else
        return CW;
}

///////////
// Treap //
///////////

#define SEED (233)

static struct MyRandom {
    MyRandom() {
        srand(SEED);
    }

    int operator()() const {
        return rand();
    }
} randint;

struct Treap {
    Treap()
            : left(NULL)
            , right(NULL)
            , prev(this)
            , next(this)
            , weight(randint()) {}
    Treap(const Vector2 &p)
            : vec(p)
            , left(NULL)
            , right(NULL)
            , prev(this)
            , next(this)
            , weight(randint()) {}

    Vector2 vec;
    Treap *left;
    Treap *right;
    Treap *prev;
    Treap *next;
    int weight;
};  // struct Treap

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

template <typename TCompare = std::less<Vector2>>
static Treap *insert(Treap *x, const Vector2 &p,
                     const TCompare &cmp = TCompare()) {
    if (!x)
        return new Treap(p);

    if (cmp(p, x->vec)) {
        x->left = insert(x->left, p, cmp);

        if (x->left->prev == x->left) {
            x->prev->next = x->left;
            x->left->prev = x->prev;
            x->left->next = x;
            x->prev = x->left;
        }

        if (x->left->weight < x->weight)
            return left_rotate(x);
    } else {
        x->right = insert(x->right, p, cmp);

        if (x->right->prev == x->right) {
            x->right->next = x->next;
            x->next->prev = x->right;
            x->next = x->right;
            x->right->prev = x;
        }

        if (x->right->weight < x->weight)
            return right_rotate(x);
    }

    return x;
}

static Treap *remove(Treap *x) {
    if (!x)
        return NULL;

    if (x->left && x->right) {
        if (x->left->weight < x->right->weight) {
            Treap *y = left_rotate(x);
            y->right = remove(x);
            return y;
        } else {
            Treap *y = right_rotate(x);
            y->left = remove(x);
            return y;
        }
    } else {
        printf("remove: Removed (%lf, %lf)\n", x->vec.x, x->vec.y);

        Treap *y = x->left ? x->left : x->right;
        x->prev->next = x->next;
        x->next->prev = x->prev;

        // delete x;

        return y;
    }
}

template <typename TCompare = std::less<Vector2>>
static Treap *remove(Treap *x, const Vector2 &p,
                     const TCompare &cmp = TCompare()) {
    if (!x)
        return NULL;

    if (p == x->vec)
        return remove(x);
    else if (cmp(p, x->vec))
        x->left = remove(x->left, p, cmp);
    else
        x->right = remove(x->right, p, cmp);

    return x;
}

template <typename TCompare = std::less<Vector2>>
static Treap *query(Treap *x, const Vector2 &p,
                    const TCompare &cmp = TCompare()) {
    if (!x)
        return NULL;

    if (p == x->vec)
        return x;
    if (cmp(p, x->vec))
        return query(x->left, p, cmp);
    else
        return query(x->right, p, cmp);
}

static Treap *lowerbound(Treap *x, const Vector2 &p) {
    Treap *y;

    while (x) {
        if (p.x < x->vec.x)
            x = x->left;
        else {
            y = x;
            x = x->right;
        }
    }  // while

    return y;
}

static Treap *min_node(Treap *x) {
    while (x->left)
        x = x->left;
    return x;
}

static Treap *max_node(Treap *x) {
    while (x->right)
        x = x->right;
    return x;
}

/////////////////
// Convex Hull //
/////////////////

static auto incy = [](const Vector2 &a, const Vector2 &b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
};

static auto decy = [](const Vector2 &a, const Vector2 &b) {
    return a.x < b.x || (a.x == b.x && a.y > b.y);
};

class ConvexHull {
 public:
    /**
     * Must initialize with a non-degerative triangle.
     */
    ConvexHull(const Vector2 &p1, const Vector2 &p2, const Vector2 &p3) {
        Vector2 sorted[] = { p1, p2, p3 };
        sort(begin(sorted), end(sorted), incy);

        left = sorted[0];
        right = sorted[2];

        up = insert(up, left);
        up = insert(up, right);
        down = insert(down, left);
        down = insert(down, right);

        right_maxy = right_miny = right.y;

        insert_point(sorted[1]);
    }

    void insert_point(const Vector2 &p) {
        if (contain(p))
            return;

        if (p.x < left.x) {
            up = insert(up, p);
            down = insert(down, p);

            Treap *x = query(up, p);
            while (turn(p, x->next->vec, x->next->next->vec) & (CCW | PARALLEL))
                up = remove(up, x->next->vec);
            x = query(down, p);
            while (turn(p, x->next->vec, x->next->next->vec) & (CW | PARALLEL))
                down = remove(down, x->next->vec);

            left = p;
        } else if (p.x > right.x) {
            up = insert(up, p);
            down = insert(down, p);

            Treap *x = query(up, p);
            while (turn(p, x->prev->vec, x->prev->prev->vec) & (CW | PARALLEL))
                up = remove(up, x->prev->vec);
            x = query(down, p);
            while (turn(p, x->prev->vec, x->prev->prev->vec) & (CCW | PARALLEL))
                down = remove(down, x->prev->vec);

            right_maxy = right_miny = p.y;
            right = p;
        } else
            _insert_point(p);
    }

    bool contain(const Vector2 &p) {
        if (p.x < left.x || p.x > right.x)
            return false;
        else if (almost_equal(p.x, right.x))
            return right_miny <= p.y && p.y <= right_maxy;
        else
            return _contain(p);
    }

 private:
    void _insert_point_to_up(const Vector2 &p) {
        if (almost_equal(p.x, left.x))
            up = insert(up, p, incy);
        else
            up = insert(up, p, decy);

        Treap *x = query(up, p);
        while (turn(p, x->prev->vec, x->prev->prev->vec) & (CW | PARALLEL))
            up = remove(up, x->prev->vec);
        while (turn(p, x->next->vec, x->next->next->vec) & (CCW | PARALLEL))
            up = remove(up, x->next->vec);
    }

    void _insert_point_to_down(const Vector2 &p) {
        if (almost_equal(p.x, left.x))
            down = insert(down, p, decy);
        else
            down = insert(down, p, incy);

        Treap *x = query(down, p);
        while (turn(p, x->prev->vec, x->prev->prev->vec) & (CCW | PARALLEL))
            down = remove(down, x->prev->vec);
        while (turn(p, x->next->vec, x->next->next->vec) & (CW | PARALLEL))
            down = remove(down, x->next->vec);
    }

    void _insert_point(const Vector2 &p) {
        if (almost_equal(p.x, right.x)) {
            right_maxy = max(right_maxy, p.y);
            right_miny = min(right_miny, p.y);
        }

        if (turn(left, right, p) == CCW)
            _insert_point_to_up(p);
        else
            _insert_point_to_down(p);
    }

    bool _contain_test_up(const Vector2 &p) {
        Treap *y = lowerbound(up, p);

        assert(y);
        assert(y->vec.x <= p.x);

        return turn(y->vec, y->next->vec, p) & (CW | PARALLEL);
    }

    bool _contain_test_down(const Vector2 &p) {
        Treap *y = lowerbound(down, p);

        assert(y);
        assert(y->vec.x <= p.x);

        return turn(y->vec, y->next->vec, p) & (CCW | PARALLEL);
    }

    bool _contain(const Vector2 &p) {
        return turn(left, right, p) == CCW ? _contain_test_up(p)
                                           : _contain_test_down(p);
    }

    Treap *up, *down;
    Vector2 left, right;
    double right_maxy, right_miny;
};  // class ConvexHull

static int q;
static Vector2 p1, p2, p3;
static ConvexHull *convex;

static void initialize() {
    int _;

    scanf("%d", &q);
    scanf("%d%lf%lf", &_, &p1.x, &p1.y);
    scanf("%d%lf%lf", &_, &p2.x, &p2.y);
    scanf("%d%lf%lf", &_, &p3.x, &p3.y);
    q -= 3;

    convex = new ConvexHull(p1, p2, p3);
}

int main() {
    initialize();

    while (q--) {
        int type, x, y;
        scanf("%d%d%d", &type, &x, &y);

        if (type == 1)
            convex->insert_point(Vector2(x, y));
        else
            puts(convex->contain(Vector2(x, y)) ? "YES" : "NO");

        printf("Completed %d %d %d.\n", type, x, y);
    }  // while

    return 0;
}  // function main
