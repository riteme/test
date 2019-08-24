#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define KMAX 200

typedef long long int64;

template <typename T>
struct Queue {
    Queue() : head(0), tail(0) {}

    void push_back(const T &v) {
        data[tail++] = v;
    }

    void pop_front() {
        head++;
    }

    void pop_back() {
        tail--;
    }

    void clear() {
        head = tail = 0;
    }

    size_t size() const {
        return tail - head;
    }

    bool empty() const {
        return head == tail;
    }

    T &operator[](const size_t i) {
        return data[i + head];
    }

    T &last() {
        return data[tail - 1];
    }

    T &second() {
        return data[tail - 2];
    }

    size_t head, tail;
    T data[NMAX + 10];
};  // struct Queue

struct Vector {
    Vector() : index(0), x(0.0L), y(0.0L) {}
    Vector(const int id, const int64 &_x, const int64 &_y)
        : index(id), x(_x), y(_y) {}

    int index;
    int64 x, y;

    int64 eval(const int64 pn) const {
        return y + x * pn;
    }

    Vector operator-(const Vector &b) const {
        return Vector(0, x - b.x, y - b.y);
    }
};  // struct Vector

inline int64 cross(const Vector &a, const Vector &b) {
    return a.x * b.y - a.y * b.x;
}

static int n, K;
static int64 seq[NMAX + 10];
static int64 pre[NMAX + 10];
static int64 f[KMAX + 10][NMAX + 10];
static int maxp[KMAX + 10][NMAX + 10];
static int op[KMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &K);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", seq + i);
        pre[i] = pre[i - 1] + seq[i];
    }  // for
}

int main() {
    initialize();

    Queue<Vector> q;
    for (int k = 1; k <= K; k++) {
        q.clear();
        for (int i = 1; i <= n; i++) {
            if (i > k) {
                while (q.size() >= 2 &&
                       q[0].eval(pre[i]) <= q[1].eval(pre[i])) {
                    q.pop_front();
                }  // while

                maxp[k][i] = q[0].index;
                f[k][i] = q[0].eval(pre[i]);
            }

            Vector u(i, pre[i], f[k - 1][i] - pre[i] * pre[i]);

            while (q.size() >= 2 && cross(u - q.last(), u - q.second()) <= 0) {
                q.pop_back();
            }  // while

            if (q.size() == 1 && u.x == q.last().x)
                q.pop_back();

            q.push_back(u);
        }  // for
    }      // for

    printf("%lld\n", f[K][n]);

    int x = n;
    for (int i = K; i >= 1; i--) {
        op[i] = maxp[i][x];
        x = op[i];
    }  // for

    for (int i = 1; i <= K; i++) {
        printf("%d ", op[i]);
    }  // for
    printf("\n");

    return 0;
}  // function main
