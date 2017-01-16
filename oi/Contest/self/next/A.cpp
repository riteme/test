#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define MOD 1000000007

typedef long long int64;

static int t, n, m;

static int64 fenwick[NMAX + 10];

inline void modify(int x, int64 v) {
    for (; x <= n; x += x & (-x)) {
        fenwick[x] += v;
        fenwick[x] %= MOD;
    }
}

inline int64 query(int r) {
    int64 answer = 0;

    for (; r; r -= r & (-r)) {
        answer += fenwick[r];
        answer %= MOD;
    }

    return answer;
}

#define MODIFY 0
#define QUERY 1
#define LEFT 1
#define RIGHT 0

class Solver123 {
 public:
    struct Point {
        int type;
        int id;
        int f;
        char dir;
        int x, y;
        int64 answer;

        int get_x() const {
            if (type == QUERY && dir == RIGHT)
                return n + 1;
            return x;
        }

        bool operator<(const Point &b) const {
            return y < b.y || (y == b.y && get_x() < b.get_x()) ||
                   (y == b.y && get_x() == b.get_x() && type < b.type);
        }
    };

    int qcnt;
    Point op[NMAX * 30 + 10];
    int pcnt;
    int prime[NMAX + 10];
    bool marked[NMAX + 10];
    int miu[NMAX + 10];
    int64 phi[NMAX + 10];
    void compute_primes() {
        pcnt = 0;
        memset(prime, 0, sizeof(prime));
        memset(marked, 0, sizeof(marked));
        memset(miu, 0, sizeof(miu));
        memset(phi, 0, sizeof(phi));
        marked[1] = true;
        miu[1] = 1;
        phi[1] = 1;

        for (int i = 2; i <= NMAX; i++) {
            if (!marked[i]) {
                prime[++pcnt] = i;
                miu[i] = -1;
                phi[i] = i - 1;
            }

            for (int j = 1; j <= pcnt && prime[j] * i <= NMAX; j++) {
                int p = prime[j];
                marked[p * i] = true;

                if (i % p == 0) {
                    miu[i * p] = 0;
                    phi[i * p] = phi[i] * p % MOD;
                    break;
                } else {
                    miu[i * p] = miu[i] * miu[p];
                    phi[i * p] = phi[i] * phi[p] % MOD;
                }
            }  // for
        }      // for
    }

    void add_point(int x, int y, int id, int f, char dir) {
        qcnt++;
        Point &p = op[qcnt];
        p.type = QUERY;
        p.id = id;
        p.x = x;
        p.y = y;
        p.f = f;
        p.dir = dir;
    }

    void add_query(int id, int l, int r, int left, int right) {
        add_point(l - 1, right, id, 1, LEFT);
        add_point(l - 1, left - 1, id, -1, LEFT);
        add_point(r + 1, right, id, 1, RIGHT);
        add_point(r + 1, left - 1, id, -1, RIGHT);
    }

    void solve() {
        compute_primes();

        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j += i) {
                qcnt++;
                Point &p = op[qcnt];
                p.type = MODIFY;
                p.x = i;
                p.y = j; 

                if (t == 1)
                    p.answer = i;
                else if (t == 2)
                    p.answer = phi[i];
                else if (t == 3)
                    p.answer = miu[i];
            }
        }

        sort(op + 1, op + qcnt + 1);
        for (int i = 1; i <= qcnt; i++) {
            Point &p = op[i];

            if (p.type == MODIFY) {
                modify(p.x, p.answer);
            } else {
                if (p.dir == LEFT) {
                    p.answer = query(p.x);
                } else {
                    p.answer = query(n) - query(p.x - 1);
                }
            }
        }
    }
};

class Solver4 {
 public:
    virtual int64 query(int64 zl, int64 zr, int64 l, int64 r) {
        if (zl <= 1)
            return 0;
        else
            return r - l + 1;
    }
};

static int64 answer[NMAX + 10];

int main() {
    scanf("%d%d%d", &t, &n, &m);

    if (t == 4) {
        Solver4 *solver = new Solver4;

        while (m--) {
            int l, r, left, right;
            scanf("%d%d%d%d", &l, &r, &left, &right);

            printf("%lld\n", solver->query(l, r, left, right));
        }
    } else {
        Solver123 *solver = new Solver123;

        for (int i = 1; i <= m; i++) {
            int l, r, left, right;
            scanf("%d%d%d%d", &l, &r, &left, &right);

            solver->add_query(i, l, r, left, right);
        }

        solver->solve();

        for (int i = 1; i <= solver->qcnt; i++) {
            Solver123::Point &p = solver->op[i];

            if (p.type == QUERY) {
                answer[p.id] += p.f * p.answer;
                answer[p.id] %= MOD;
            }
        }

        for (int i = 1; i <= m; i++) {
            if (answer[i] < 0)
                answer[i] += MOD;

            printf("%lld\n", answer[i]);
        }
    }

    return 0;
}
