#define NDEBUG

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

enum Clockwise { PARALLEL, CW, CCW };  // enum Clockwise

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

static Treap *insert(Treap *x, const Vector2 &p) {
    if (!x)
        return new Treap(p);

    if (p.x < x->vec.x) {
        x->left = insert(x->left, p);

        if (x->left->prev == x->left) {
            x->prev->next = x->left;
            x->left->prev = x->prev;
            x->left->next = x;
            x->prev = x->left;
        }

        if (x->left->weight < x->weight)
            return left_rotate(x);
    } else if (p.x > x->vec.x) {
        x->right = insert(x->right, p);

        if (x->right->prev == x->right) {
            x->right->next = x->next;
            x->next->prev = x->right;
            x->next = x->right;
            x->right->prev = x;
        }

        if (x->right->weight < x->weight)
            return right_rotate(x);
    }

    assert(x->vec.x != p.x);

    return x;
}

static Treap *remove(Treap *x) {
    if (!x)
        return NULL;

    if (x->left && x->right) {
        if (x->left->weight < x->right->weight) {
            Treap *y = left_rotate(x);
            remove(x);
            return y;
        } else {
            Treap *y = right_rotate(x);
            remove(x);
            return y;
        }
    } else {
        Treap *y = x->left ? x->left : x->right;
        x->prev->next = x->next;
        x->next->prev = x->prev;

        // delete x;

        return y;
    }
}

static Treap *remove(Treap *x, const Vector2 &p) {
    if (!x)
        return NULL;

    if (p.x < x->vec.x)
        x->left = remove(x->left, p);
    else if (p.x > x->vec.x)
        x->right = remove(x->right, p);
    else
        return remove(x);

    return x;
}

static Treap *query(Treap *x, const Vector2 &p) {
    if (!x)
        return NULL;

    if (p.x < x->vec.x)
        return query(x->left, p);
    else if (p.x > x->vec.x)
        return query(x->right, p);
    else
        return x;
}

static TreapPair nearest(Treap *x, const Vector2 &p) {
    TreapPair result;

    while (x) {
        if (p.x < x->vec.x) {
            result.second = x;
            x = x->left;
        } else {
            result.first = x;
            x = x->right;
        }
    }  // while

    return result;
}

/////////////////
// Convex Hull //
/////////////////

class ConvexHull {
 public:
    /**
     * Must initialize with a non-degerative triangle.
     */
    ConvexHull(const Vector2 &p1, const Vector2 &p2, const Vector2 &p3) {
        Vector2 sorted[] = { p1, p2, p3 };
        sort(begin(sorted), end(sorted),
             [](const Vector2 &a, const Vector2 &b) {
                 return a.x < b.x || (a.x == b.x && a.y > b.y);
             });

        left = sorted[0];
        right = sorted[2];

        up = insert(up, left);
        up = insert(up, right);
        down = insert(down, left);
        down = insert(down, right);

        if (turn(left, right, sorted[1]) == CCW)
            up = insert(up, sorted[1]);
        else
            down = insert(down, sorted[1]);
    }

    void insert_point(const Vector2 &p) {
        if (p.x < left.x) {
            up = remove(up, left);
            up = insert(up, p);
            down = remove(down, left);
            down = insert(down, p);
            left = p;

            Treap *x = query(up, p);
            while (turn(x->vec, x->next->vec, x->next->next->vec) == CCW)
                up = remove(up, x->next->vec);
            x = query(down, p);
            while (turn(x->vec, x->next->vec, x->next->next->vec) == CW)
                down = remove(down, x->next->vec);
        } else if (p.x > right.x) {
            up = remove(up, right);
            up = insert(up, p);
            down = remove(down, right);
            down = insert(down, p);
            right = p;

            Treap *x = query(up, p);
            while (turn(x->vec, x->prev->vec, x->prev->prev->vec) == CW)
                up = remove(up, x->prev->vec);
            x = query(down, p);
            while (turn(x->vec, x->prev->vec, x->prev->prev->vec) == CCW)
                down = remove(down, x->prev->vec);
        } else {
            _insert_point(p);
        }
    }

    bool contain(const Vector2 &p) {
        if (p.x < left.x || p.x > right.x)
            return false;
        else
            return _contain(p);
    }

 private:
    void _insert_point_to_up(const Vector2 &p) {
        TreapPair neighbor = nearest(up, p);

        assert(neighbor.first);
        assert(neighbor.second);
        assert(neighbor.first->vec.x <= p.x && p.x <= neighbor.second->vec.x);

        Clockwise turning = turn(neighbor.first->vec, neighbor.second->vec, p);
        if (turning == PARALLEL || turning == CW)
            return;

        if (almost_equal(neighbor.first->vec.x, p.x))
            up = remove(up, neighbor.first->vec);
        else if (almost_equal(neighbor.second->vec.x, p.x))
            up = remove(up, neighbor.second->vec);

        up = insert(up, p);
        Treap *x = query(up, p);
        while (turn(p, x->prev->vec, x->prev->prev->vec) == CW)
            up = remove(up, x->prev->vec);
        while (turn(p, x->next->vec, x->next->next->vec) == CCW)
            up = remove(up, x->next->vec);
    }

    void _insert_point_to_down(const Vector2 &p) {
        TreapPair neighbor = nearest(down, p);

        assert(neighbor.first);
        assert(neighbor.second);
        assert(neighbor.first->vec.x <= p.x && p.x <= neighbor.second->vec.x);

        Clockwise turning = turn(neighbor.first->vec, neighbor.second->vec, p);
        if (turning == PARALLEL || turning == CCW)
            return;

        if (almost_equal(neighbor.first->vec.x, p.x))
            down = remove(down, neighbor.first->vec);
        else if (almost_equal(neighbor.second->vec.x, p.x))
            down = remove(down, neighbor.second->vec);

        down = insert(down, p);
        Treap *x = query(down, p);
        while (turn(p, x->prev->vec, x->prev->prev->vec) == CCW)
            down = remove(down, x->prev->vec);
        while (turn(p, x->next->vec, x->next->next->vec) == CW)
            down = remove(down, x->next->vec);
    }

    void _insert_point(const Vector2 &p) {
        Clockwise turning = turn(left, right, p);

        if (turning == PARALLEL)  // Invalid point on a edge
            return;
        if (turning == CCW)
            _insert_point_to_up(p);
        else
            _insert_point_to_down(p);
    }

    bool _contain_test_up(const Vector2 &p) {
        TreapPair neighbor = nearest(up, p);

        assert(neighbor.first);
        assert(neighbor.second);
        assert(neighbor.first->vec.x <= p.x && p.x <= neighbor.second->vec.x);

        Clockwise turning = turn(neighbor.first->vec, neighbor.second->vec, p);
        if (turning == PARALLEL || turning == CW)
            return true;
        return false;
    }

    bool _contain_test_down(const Vector2 &p) {
        TreapPair neighbor = nearest(down, p);

        assert(neighbor.first);
        assert(neighbor.second);
        assert(neighbor.first->vec.x <= p.x && p.x <= neighbor.second->vec.x);

        Clockwise turning = turn(neighbor.first->vec, neighbor.second->vec, p);
        if (turning == PARALLEL || turning == CCW)
            return true;
        return false;
    }

    bool _contain(const Vector2 &p) {
        Clockwise turning = turn(left, right, p);

        if (turning == PARALLEL)
            return true;
        if (turning == CCW)
            return _contain_test_up(p);
        else
            return _contain_test_down(p);
    }

    Treap *up, *down;
    Vector2 left, right;
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
    }  // while

    return 0;
}  // function main
