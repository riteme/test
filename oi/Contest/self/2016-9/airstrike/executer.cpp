// Target program
#include "airstrike.cpp"

#include <cassert>
#include <cstdio>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <cmath>

#include <vector>
#include <chrono>
#include <random>
#include <bitset>
#include <thread>
#include <atomic>
#include <utility>
#include <algorithm>

using std::pair;
using std::sort;
using std::min;
using std::max;
using std::bitset;
using std::vector;
using std::thread;
using std::atomic;
using std::mt19937;
using std::random_device;
using std::random_device;
using std::chrono::milliseconds;
using std::chrono::microseconds;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

#define INITIALIZE_TIMELIMIE 3000
#define FINALIZE_TIMELIMIT 3000
#define WRONG_SCORE 1
#define BLOCKSIZE 1000000

// #define DEBUG(message, ...) printf(message, __VA_ARGS__);
#define DEBUG

typedef long long int64;

#ifndef STD

////////////////////////
// Vector computation //
////////////////////////

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

//////////////////
// Line objects //
//////////////////

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

//////////////////////
// Persistent Treap //
//////////////////////

struct Random {
    Random() {
        random_device rd;
        randomer = mt19937(rd());
    }

    int operator()() {
        return randomer();
    }

 private:
    mt19937 randomer;
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
        Treap *y;
        if (h->left->weight < h->right->weight) {
            h->left = new Treap(*h->left);
            y = left_rotate(h);

            y->right = persistent_remove(h);
        } else {
            h->right = new Treap(*h->right);
            y = right_rotate(h);

            y->left = persistent_remove(h);
        }

        return y;
    } else {
        Treap *next = h->left;

        if (h->right != nullptr)
            next = h->right;

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

enum class EventType : int {
    Enter = 1,
    Exit = 2,
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
        // Speed up vector insert.
        x.reserve(points.size());
        edges.reserve(points.size());
        version.reserve(points.size());

        events.reserve(points.size() * 2);

        for (auto beg = points.begin(); beg != points.end(); beg++) {
            x.push_back(beg->x);

            auto next = beg + 1;
            if (next == points.end())
                edges.push_back(Line(*beg, *points.begin()));
            else
                edges.push_back(Line(*beg, *next));

            events.push_back(EventPoint(&edges.back(), EventType::Enter));
            events.push_back(EventPoint(&edges.back(), EventType::Exit));
        }  // for

        sort(x.begin(), x.end());
        auto iter = std::unique(x.begin(), x.end());
        x.resize(std::distance(x.begin(), iter));

        stable_sort(events.begin(),
                    events.end(),
                    [](const EventPoint &a, const EventPoint &b) {
                        int64 ax = a.type == EventType::Enter ? a.line->left.x
                                                              : a.line->right.x;
                        int64 bx = b.type == EventType::Enter ? b.line->left.x
                                                              : b.line->right.x;

                        return ax < bx ||
                               (ax == bx && a.type == EventType::Exit);
                    });

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

#endif  // IFNDEF STD

class Timer {
 public:
    static void tick() {
        _last = high_resolution_clock::now();
    }

    static int64 elapsed() {
        auto current = high_resolution_clock::now();
        auto span = current - _last;

        return duration_cast<milliseconds>(span).count();
    }

 private:
    static high_resolution_clock::time_point _last;
};  // class Timer

high_resolution_clock::time_point Timer::_last;

struct {
    int id;
    size_t n;

    struct {
        int left;
        int right;
        int top;
        int bottom;
    } margin;

    struct {
        int left = INT_MAX;
        int right = INT_MIN;
        int top = INT_MIN;
        int bottom = INT_MAX;
    } rect;

    struct {
        double *x;
        double *y;
    } polygon;

    struct {
        int64 s1;
        int64 s2;
        int64 s3;
        int64 s4;
        int64 s5;
    } level;

    int64 fullscore;

    int64 timelimit;

    int64 passed_time = 0;
    int64 processed = 0;
    int64 wrong = 0;
} config;

static Polgyon *standard;

static void executer_initialize() {
    scanf("%d", &config.id);
    scanf("%zu", &config.n);
    scanf("%d%d%d%d", &config.margin.left, &config.margin.right,
          &config.margin.top, &config.margin.bottom);
    scanf("%lld", &config.timelimit);
    scanf("%lld%lld%lld%lld%lld", &config.level.s1, &config.level.s2,
          &config.level.s3, &config.level.s4, &config.level.s5);
    scanf("%lld", &config.fullscore);

    config.polygon.x = new double[config.n];
    config.polygon.y = new double[config.n];
    for (size_t i = 0; i < config.n; i++) {
        scanf("%lf%lf", config.polygon.x + i, config.polygon.y + i);

        config.rect.left =
            min(config.rect.left, static_cast<int>(config.polygon.x[i]));
        config.rect.right =
            max(config.rect.right, static_cast<int>(config.polygon.x[i]));
        config.rect.top =
            max(config.rect.top, static_cast<int>(config.polygon.y[i]));
        config.rect.bottom =
            min(config.rect.bottom, static_cast<int>(config.polygon.y[i]));
    }  // for

    config.rect.left -= config.margin.left;
    config.rect.right += config.margin.right;
    config.rect.top += config.margin.top;
    config.rect.bottom -= config.margin.bottom;

    vector<Vector2> points;
    points.reserve(config.n);

    for (size_t i = 0; i < config.n; i++) {
        points.push_back(Vector2(config.polygon.x[i], config.polygon.y[i]));
    }

    standard = new Polgyon(points);

    Timer::tick();
    initialize(config.polygon.x, config.polygon.y, config.n, config.id);
    if (Timer::elapsed() > INITIALIZE_TIMELIMIE) {
        printf("0 Initialization time limit exceeded.");
        exit(233);
    }
}

static void executer_finalize() {
    Timer::tick();
    finalize();
    if (Timer::elapsed() > FINALIZE_TIMELIMIT) {
        printf("0 Finalization time limit exceeded.");
        exit(233);
    }

    delete[] config.polygon.x;
    delete[] config.polygon.y;

    double ratio[] = { 0.2, 0.4, 0.6, 0.8, 1.0 };
    double r = 0.0;
    if (config.processed >= config.level.s1)
        r = ratio[0];
    if (config.processed >= config.level.s2)
        r = ratio[1];
    if (config.processed >= config.level.s3)
        r = ratio[2];
    if (config.processed >= config.level.s4)
        r = ratio[3];
    if (config.processed >= config.level.s5)
        r = ratio[4];

    int64 score =
        max(0, static_cast<int>(static_cast<int64>(config.fullscore * r) -
                                WRONG_SCORE * config.wrong));

    printf("%lld processed = %lld, r = %.2lf, wrong = %lld\n", score,
           config.processed, r, config.wrong);
}

static double qx[BLOCKSIZE];
static double qy[BLOCKSIZE];
static bitset<BLOCKSIZE> answer;
static bitset<BLOCKSIZE> user;
static atomic<int64> processed;
static atomic<bool> flag;

static int executer_randint(int left, int right) {
    static random_device rd;

    return (rd() % (right - left + 1)) + left;
}

static void generate_querys() {
    for (size_t i = 0; i < 1000; i++) {
        size_t p = executer_randint(0, config.n - 1);
        int offest_x = executer_randint(-15, 15);
        int offest_y = executer_randint(-15, 15);
        qx[i] = config.polygon.x[p] + offest_x;
        qy[i] = config.polygon.y[p] + offest_y;
    }

    for (size_t i = 1000; i < BLOCKSIZE; i++) {
        qx[i] = executer_randint(config.rect.left, config.rect.right);
        qy[i] = executer_randint(config.rect.bottom, config.rect.top);
    }  // for
}

static void query_standard() {
    answer.reset();

    for (size_t i = 0; i < BLOCKSIZE; i++) {
        answer[i] = standard->contain(Vector2(qx[i], qy[i]));
    }  // for
}

static void query_user() {
    user.reset();

    int64 passed = config.passed_time;
    atomic<size_t> pos(0);
    processed = 0;
    flag = true;

    thread runner = thread([&pos]() {
        while (flag && pos < BLOCKSIZE) {
            user[pos] = query(qx[pos], qy[pos]);

            // int s = answer[pos];
            // int u = user[pos];
            // if (s != u)
            //     printf("(%lf, %lf): answer = %d, user = %d\n", qx[pos],
            //     qy[pos],
            //            s, u);

            pos++;
        }
    });

    Timer::tick();
    while (passed + Timer::elapsed() < config.timelimit && pos < BLOCKSIZE) {
        // std::this_thread::sleep_for(microseconds(1));
    }  // while
    config.passed_time += Timer::elapsed();

    processed.store(pos);
    flag = false;

    runner.join();
}

static void check() {
    int64 not_processed = BLOCKSIZE - processed;

    if (not_processed > 0)
        DEBUG("not_processed = %lld\n", not_processed);

    user <<= not_processed;
    answer <<= not_processed;
    answer ^= user;

    config.wrong += answer.count();
    config.processed += processed;
    // DEBUG("config.processed = %lld\n", config.processed);
    // DEBUG("config.passed_time = %lld\n", config.passed_time);
}

int main() {
    executer_initialize();
    atexit(executer_finalize);

    while (config.passed_time < config.timelimit) {
        generate_querys();
        query_standard();
        query_user();
        check();
    }  // while

    DEBUG("passed_time = %lld\n", config.passed_time);
    DEBUG("processed = %lld\n", config.processed);
    DEBUG("wrong = %lld\n", config.wrong);

    return 0;
}  // function main
