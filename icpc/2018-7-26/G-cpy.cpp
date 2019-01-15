#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100
#define OPMAX 15
#define LMAX 10
#define SIZE 9
#define DATA_SIZE 8

constexpr int dat[][DATA_SIZE] = {
    {'A', 1, 4},
    {'B', 4, 1, 1, 1, 1},
    {'C', 2, 2, 2},
    {'D', 3, 1, 2, 1},
    {'E', 2, 1, 3},
    {'F', 3, 2, 1, 1},
    {'G', 2, 3, 1},
    {'H', 3, 1, 1, 2}
};

struct Vector {
    Vector() {
        memset(dat, 0, sizeof(dat));
    }

    Vector(int *H) {
        memcpy(dat, H, sizeof(dat));
    }

    Vector(const initializer_list<int> &il) {
        int i = 0;
        for (int v : il) {
            dat[i] = v;
            i++;
        }
    }

    int dat[SIZE];

    int value() const {
        int ret = 0;
        for (int i = 0; i < SIZE; i++)
            ret = max(ret, abs(dat[i]));
        return ret;
    }

    int operator[](const int i) const {
        return dat[i];
    }

    int &operator[](const int i) {
        return dat[i];
    }

    Vector operator+(const Vector &b) const {
        Vector tmp;
        for (int i = 0; i < SIZE; i++)
            tmp[i] = dat[i] + b[i];
        return tmp;
    }

    Vector &operator+=(const Vector &b) {
        for (int i = 0; i < SIZE; i++)
            dat[i] += b[i];
        return *this;
    }
};

static int A[LMAX];
static int n, seq[LMAX];
static char name[NMAX];
static int pos[NMAX];
static Vector B[NMAX];

inline void add(char s, int p) {
    for (int i = 0; i < LMAX - 1; i++)
        seq[i] = seq[i + 1] - seq[i];
    name[n] = s;
    pos[n] = p;
    B[n++] = Vector(seq);
}

void initialize() {
    for (int i = 0; i < LMAX; i++) {
        scanf("%d", A + i);
        if (i) A[i - 1] = A[i] - A[i - 1];
    }

    for (int i = 0; i < DATA_SIZE; i++) {
        int m = dat[i][1];
        for (int j = 0; j <= LMAX - m; j++) {
            memset(seq, 0, sizeof(seq));
            memcpy(seq + j, dat[i] + 2, sizeof(int) * m);
            add(dat[i][0], j + 1);
        }
    }
}

static int op[OPMAX], cnt;
static int val[NMAX];

bool dfs(const Vector &cur) {
    if (cur.value() == 0) return true;
    if (cnt == OPMAX) return false;

    int sorted[n];
    for (int i = 0; i < n; i++) {
        val[i] = (cur + B[i]).value();
        sorted[i] = i;
    }

    sort(sorted, sorted + n, [](int x, int y) {
        return val[x] < val[y];
    });

    for (int i = 0; i < n; i++) {
        op[cnt++] = sorted[i];
        if (dfs(cur + B[sorted[i]])) return true;
        cnt--;
    }

    return false;
}

int main() {
    initialize();

    assert(dfs(A));
    printf("%d\n", cnt);
    for (int i = 0; i < cnt; i++)
        printf("%c %d\n", name[op[i]], pos[op[i]]);

    return 0;
}
