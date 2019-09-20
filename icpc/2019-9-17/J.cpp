#include <cstdio>
#include <cctype>
#include <cstring>

#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
static char buf[BUFFERSIZE];
static size_t pos = BUFFERSIZE;

inline void _getc(char &c) {
    if (pos == BUFFERSIZE) {
        pos = 0;
        fread(buf, 1, BUFFERSIZE, stdin);
    }
    c = buf[pos++];
}

template <typename T>
inline void read(T &x) {
    x = 0;
    char c;
    do _getc(c); while (!isdigit(c));
    do {
        x = x * 10 + (c - '0');
        _getc(c);
    } while (isdigit(c));
}

#define NMAX 300000
#define MMAX 1500

static int n, m, sum;
static int xl[NMAX + 10], xr[NMAX + 10], yl[NMAX + 10], yr[NMAX + 10];
static int c1[NMAX + 10];
static bool mark[NMAX + 10];
static int cnt[MMAX + 10][MMAX + 10], fa[MMAX + 10][MMAX + 10][2];
static int mat[MMAX + 10][MMAX + 10];

struct Node {
    Node(int _l, int _r) : l(_l), r(_r), mi((l + r) >> 1), lch(NULL), rch(NULL) {
        if (l < r) {
            lch = new Node(l, mi);
            rch = new Node(mi + 1, r);
        }
    }
    ~Node() {
        if (lch) {
            delete lch;
            delete rch;
        }
    }

    int l, r, mi;
    deque<int> cov;
    Node *lch, *rch;

    void cover(int L, int R, int x) {
        if (L <= l && r <= R) cov.push_front(x);
        else {
            if (L <= mi) lch->cover(L, R, x);
            if (R > mi) rch->cover(L, R, x);
        }
    }

    void push(int x, int c, int p1, int p2) {
        if (c > 2) {
            sum += r - l + 1;
            for (int i = l; i <= r; i++) {
                cnt[x][i] = 3;
                //fprintf(stderr, "(%d, %d) 3\n", x, i);
            }
        } else {
            while (!cov.empty() && mark[cov[0]]) cov.pop_front();
            if (!cov.empty()) {
                c++;
                p2 = p1;
                p1 = cov[0];
            }
            while (cov.size() >= 2 && mark[cov[1]]) {
                cov[1] = cov[0];
                cov.pop_front();
            }
            if (cov.size() >= 2) {
                c++;
                p2 = cov[1];
            }
            while (cov.size() > 2 && mark[cov.back()]) cov.pop_back();
            if (cov.size() > 2) c = 3;
            if (lch) {
                lch->push(x, c, p1, p2);
                rch->push(x, c, p1, p2);
            } else {
                cnt[x][l] = c;
                fa[x][l][0] = p1;
                fa[x][l][1] = p2;
                if (c) sum++;
                if (c == 1) c1[p1]++;
                //fprintf(stderr, "(%d, %d) %d, %d, %d\n", x, l, c, p1, p2);
            }
        }
    }
};

static vector<int> ins[MMAX + 10], del[MMAX + 10];

int main() {
    int T;
    //scanf("%d", &T);
    read(T);
    Node *tr = NULL;
    while (T--) {
        //scanf("%d%d", &n, &m);
        read(n); read(m);
        sum = 0;
        memset(mark + 1, 0, n);
        if (tr) delete tr;
        tr = new Node(1, m);
        for (int i = 1; i <= m; i++) {
            ins[i].clear();
            del[i].clear();
        }
        for (int i = 1; i <= n; i++) {
            //scanf("%d%d%d%d", xl + i, xr + i, yl + i, yr + i);
            read(xl[i]); read(xr[i]); read(yl[i]); read(yr[i]);
            ins[xl[i]].push_back(i);
            del[xr[i]].push_back(i);
            c1[i] = 0;
        }
        for (int x = 1; x <= m; x++) {
            for (int i : ins[x]) tr->cover(yl[i], yr[i], i);
            tr->push(x, 0, 0, 0);
            for (int i : del[x]) mark[i] = true;
        }
        for (int x = 1; x <= m; x++) for (int y = 1; y <= m; y++)
            mat[x][y] = mat[x - 1][y] + mat[x][y - 1] - mat[x - 1][y - 1]
                      + (cnt[x][y] == 2);
        int mx = 0, mx2 = 0;
        for (int i = 1; i <= n; i++) {
            if (c1[i] > mx) {
                mx2 = mx;
                mx = c1[i];
            } else if (c1[i] > mx2) mx2 = c1[i];
        }
        mx += mx2;
        for (int x = 1; x <= m; x++) for (int y = 1; y <= m; y++) if (cnt[x][y] == 2) {
            int p1 = fa[x][y][0], p2 = fa[x][y][1];
            int ixl = max(xl[p1], xl[p2]);
            int ixr = min(xr[p1], xr[p2]);
            int iyl = max(yl[p1], yl[p2]);
            int iyr = min(yr[p1], yr[p2]);
            int i = mat[ixr][iyr] - mat[ixl - 1][iyr] - mat[ixr][iyl - 1] + mat[ixl - 1][iyl - 1];
            mx = max(mx, c1[p1] + c1[p2] + i);
        }
        printf("%d\n", sum - mx);
    }
    return 0;
}
