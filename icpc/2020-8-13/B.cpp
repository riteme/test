#pragma GCC optimize(3)

#include <cstdio>
#include <cstring>
#include <cctype>
#include <cassert>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define BUFSIZE 65536
char _buf[BUFSIZE];
size_t _pos = BUFSIZE, _sz = BUFSIZE;

char _getc() {
    if (_pos == BUFSIZE) {
        _pos = 0;
        _sz = fread(_buf, 1, BUFSIZE, stdin);
    }
    return _pos < _sz ? _buf[_pos++] : 0;
}

template <typename T>
void read(T &x) {
    x = 0;
    char c;
    do {
        c = _getc();
    } while (!isdigit(c) && c != '-');
    int f = 1;
    if (c == '-') {
        f = -1;
        c = _getc();
    }
    do {
        x = x * 10 + c - '0';
        c = _getc();
    } while (isdigit(c));
    x *= f;
}

#define NMAX 1000000
int O = NMAX + 1;
#define INF 1000000000

template <typename T>
struct Deque {
    int l;
    vector<T> vec;

    T &head() {
        return vec[l];
    }

    T &tail() {
        return vec[vec.size() - 1];
    }

    void push(T x) {
        vec.push_back(x);
    }

    void pop_left() {
        l++;
    }

    void pop_right() {
        vec.pop_back();
    }

    void clear() {
        vec.clear();
        l = 0;
    }

    bool empty() {
        return l == vec.size();
    }
};

template <typename T>
struct Heap {
    priority_queue<T> q, q0;

    void update() {
        while (!q.empty() && !q0.empty() && q.top() == q0.top()) {
            q.pop();
            q0.pop();
        }
    }

    T top() {
        update();
        return q.top();
    }

    bool empty() {
        update();
        return q.empty();
    }

    void push(T x) {
        q.push(x);
    }

    void pop(T x) {
        q0.push(x);
    }
};

int n, L, R, mi, mx;
int a[NMAX + 10];
int f[NMAX + 10];
Deque<int> buc[NMAX * 2 + 10];

int val(int i) {
    return buc[O + i].empty() ? -INF : f[buc[O + i].head()];
}

void solve() {
    Heap<int> q0, q1;

    for (int i = 1; i <= n; i++) {
        if (a[i] > a[i - 1]) {
            if (!buc[O + a[i]].empty())
                q0.pop(f[buc[O + a[i]].head()]);
            if (!buc[O + a[i] - 1].empty())
                q1.push(f[buc[O + a[i] - 1].head()]);
        } else if (a[i] < a[i - 1]) {
            if (!buc[O + a[i] + 1].empty())
                q0.push(f[buc[O + a[i] + 1].head()]);
            if (!buc[O + a[i]].empty())
                q1.pop(f[buc[O + a[i]].head()]);
        }

        if (i >= L) {
            int j = a[i - L];

            if (!buc[O + j].empty()) {
                int v = f[buc[O + j].head()];
                if (j > a[i])
                    q0.pop(v);
                else if (j < a[i])
                    q1.pop(v);
            }

            while (!buc[O + j].empty() && f[buc[O + j].tail()] <= f[i - L]) {
                buc[O + j].pop_right();
            }
            buc[O + j].push(i - L);

            int v = f[buc[O + j].head()];
            if (j > a[i])
                q0.push(v);
            else if (j < a[i])
                q1.push(v);
        }

        f[i] = val(a[i]);
        if (!q0.empty()) {
            f[i] = max(f[i], q0.top() - 1);
        }
        if (!q1.empty()) {
            f[i] = max(f[i], q1.top() + 1);
        }

        if (i >= R) {
            int j = a[i - R];
            if (!buc[O + j].empty() && buc[O + j].head() == i - R) {
                buc[O + j].pop_left();
                if (j > a[i])
                    q0.pop(f[i - R]);
                else if (j < a[i])
                    q1.pop(f[i - R]);

                if (!buc[O + j].empty()) {
                    int v = f[buc[O + j].head()];
                    if (j > a[i])
                        q0.push(v);
                    else if (j < a[i])
                        q1.push(v);
                }
            }
        }
    }
}

void _main() {
    read(n); read(L); read(R);
    mi = mx = 0;
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        a[i] += a[i - 1];
        mi = min(mi, a[i]);
        mx = max(mx, a[i]);
    }

    solve();
    printf("%d\n", f[n]);

    for (int i = mi; i <= mx; i++) {
        buc[O + i].clear();
    }
}

int main() {
    int T;
    read(T);
    while (T--) {
        _main();
    }
    return 0;
}
