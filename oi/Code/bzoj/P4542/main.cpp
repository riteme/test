#include <cmath>
#include <cstdio>
#include <cstring>

#include <map>
#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long int64;

static int BLOCKSIZE;

struct Interval {
    void reset(int l, int r) {
        left = l;
        right = r;
        x = l / BLOCKSIZE;
        answer = 0;
    }

    int left;
    int right;
    int x;
    int64 answer;
};

static int P, n, m;
static char str[NMAX + 10];
static Interval que[NMAX + 10];
static Interval *ref[NMAX + 10];

struct Solver {
    int64 answer;

    virtual void initialize() = 0;
    virtual void expand_left(int x) = 0;
    virtual void expand_right(int x) = 0;
    virtual void shrink_left(int x) = 0;
    virtual void shrink_right(int x) = 0;
};

struct NormalSolver : public Solver {
    int64 suf[NMAX + 10];
    int val[NMAX + 10];
    int cnt[NMAX + 10];

    virtual void initialize() {
        suf[n + 1] = 0;
        int64 tpow = 1;
        for (int i = n; i >= 1; i--) {
            suf[i] = ((str[i] - '0') * tpow + suf[i + 1]) % P;
            tpow = tpow * 10 % P;
        }

        int id = 1;
        map<int64, int> table;
        for (int i = 1; i <= n + 1; i++) {
            if (table.count(suf[i]))
                val[i] = table[suf[i]];
            else {
                val[i] = id++;
                table[suf[i]] = val[i];
            }
        }

        for (int i = 1; i <= m; i++) {
            que[i].right++;
        }

        memset(cnt, 0, sizeof(cnt));
    }

    virtual void expand_left(int x) {
        answer += cnt[val[x]];
        cnt[val[x]]++;
    }

    virtual void expand_right(int x) {
        expand_left(x);
    }

    virtual void shrink_left(int x) {
        cnt[val[x]]--;
        answer -= cnt[val[x]];
    }

    virtual void shrink_right(int x) {
        shrink_left(x);
    }
};

struct SpecialSolver : public Solver {
    int left;
    int cnt;
    int val[NMAX + 10];

    virtual void initialize() {
        left = 1;
        cnt = 0;

        for (int i = 1; i <= n; i++) {
            val[i] = str[i] - '0';
        }
    }

    virtual void expand_left(int x) {
        left--;

        if (val[x] % P == 0)
            cnt++;

        answer += cnt;
    }

    virtual void expand_right(int x) {
        if (val[x] % P == 0) {
            cnt++;

            answer += x - left + 1;
        }
    }

    virtual void shrink_left(int x) {
        left++;
        answer -= cnt;

        if (val[x] % P == 0)
            cnt--;
    }

    virtual void shrink_right(int x) {
        if (val[x] % P == 0) {
            answer -= x - left + 1;
            cnt--;
        }
    }
};

static bool cmp(const Interval *a, const Interval *b) {
    return a->x < b->x || (a->x == b->x && a->right < b->right);
}

static void initialize() {
    scanf("%d", &P);
    scanf("%s", str + 1);
    n = strlen(str + 1);
    BLOCKSIZE = max(int(sqrt(n)), 1);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);

        que[i].reset(l, r);
        ref[i] = que + i;
    }
    sort(ref + 1, ref + m + 1, cmp);
}

int main() {
    // freopen("number.in", "r", stdin);
    // freopen("number.out", "w", stdout);
    initialize();

    Solver *solver;
    
    if (P == 2 || P == 5)
        solver = new SpecialSolver;
    else
        solver = new NormalSolver;

    solver->initialize();
    int lastx = 1, lasty = 1;
    solver->expand_right(1);
    for (int i = 1; i <= m; i++) {
        Interval *current = ref[i];

        for (int p = lastx - 1; p >= current->left; p--) {
            solver->expand_left(p);
        }

        for (int p = lasty + 1; p <= current->right; p++) {
            solver->expand_right(p);
        }

        for (int p = lastx; p < current->left; p++) {
            solver->shrink_left(p);
        }

        for (int p = lasty; p > current->right; p--) {
            solver->shrink_right(p);
        }

        current->answer = solver->answer;
        lastx = current->left;
        lasty = current->right;
    }

    for (int i = 1; i <= m; i++) {
        printf("%lld\n", que[i].answer);
    }

    return 0;
}
