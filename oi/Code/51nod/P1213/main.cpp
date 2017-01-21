#define NDEBUG

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>

#include <algorithm>
#include <functional>

using namespace std;

typedef long long int64;

class UnionFind {
 public:
    UnionFind(int size) : _size(size), _set(new int[size + 1]) {}

    ~UnionFind() {
        delete[] _set;
    }

    void reset() {
        memset(_set, 0, sizeof(int) * (_size + 1));
    }

    int find(int x) {
        return _set[x] ? _set[x] = find(_set[x]) : x;
    }

    void direct_link(int x, int y) {
        _set[x] = y;
    }

 private:
    int _size;
    int *_set;
};  // class UnionFind

class FenwickArray {
 public:
    typedef function<bool(int, int)> CompareFunction;

    FenwickArray(int size) : _size(size), _arr(new int[size + 1]) {}

    ~FenwickArray() {
        delete[] _arr;
    }

    void reset() {
        memset(_arr, 0, sizeof(int) * (_size + 1));
    }

    void set_cmp(const CompareFunction &cmp) {
        _cmp = cmp;
    }

    void modify(int x, int v) {
        assert(1 <= x && x <= _size);

        for (; x <= _size; x += x & (-x)) {
            if (_cmp(v, _arr[x]))
                _arr[x] = v;
        }  // for
    }

    int query(int x) const {
        assert(1 <= x && x <= _size);

        int answer = 0;

        for (; x; x -= x & (-x)) {
            if (_cmp(_arr[x], answer))
                answer = _arr[x];
        }  // for

        return answer;
    }

 private:
    int _size;
    int *_arr;
    CompareFunction _cmp;
};  // class FenwickArray

class OrderedHash {
 public:
    void reset() {
        _value.clear();
    }

    void add_value(int x) {
        _value.push_back(x);
    }

    void process() {
        sort(_value.begin(), _value.end());
        _end = unique(_value.begin(), _value.end());
    }

    int hash(int x) {
        return lower_bound(_value.begin(), _end, x) - _value.begin() + 1;
    }

 private:
    vector<int>::iterator _end;
    vector<int> _value;
};  // class OrderedHash

class Kruskal {
 public:
    Kruskal(int size) : n(size) {}

    void add_edge(int u, int v, int w) {
        if (u == 0 || v == 0)
            return;

        edges.push_back({u, v, w});
    }

    int64 solve() {
        sort(edges.begin(), edges.end());

        UnionFind uf(n);
        uf.reset();
        int cnt = 0;
        int64 answer = 0;
        for (auto &e : edges) {
            int u = uf.find(e.u);
            int v = uf.find(e.v);

            if (u != v) {
                uf.direct_link(u, v);
                cnt++;
                answer += e.w;
            }

            if (cnt == n - 1)
                break;
        }  // foreach in edges

        assert(cnt == n - 1);
        return answer;
    }

 private:
    struct Edge {
        int u, v, w;

        bool operator<(const Edge &e) const {
            return w < e.w;
        }
    };  // struct Edge

    int n;
    vector<Edge> edges;
};  // class Kruskal

class Solver {
 public:
    static constexpr int CoordMax = 1000000;

    Solver() {
        scanf("%d", &n);
        p = new Point[n + 1];

        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &p[i].x, &p[i].y);
            p[i].u = i;
        }  // for
    }

    ~Solver() {
        delete[] p;
    }

    void solve() {
        Kruskal mst(n);

        scan(mst);

        for (int i = 1; i <= n; i++) {
            swap(p[i].x, p[i].y);
        }
        scan(mst);

        for (int i = 1; i <= n; i++) {
            p[i].y = CoordMax - p[i].y;
        }  // for
        scan(mst);

        for (int i = 1; i <= n; i++) {
            swap(p[i].x, p[i].y);
        }
        scan(mst);

        printf("%lld\n", mst.solve());
    }

 private:
    struct Point {
        int u;
        int x, y;
    };  // struct Point

    int distance(const Point &a, const Point &b) {
        return abs(a.x - b.x) + abs(a.y - b.y);
    }

    void scan(Kruskal &mst) {
        OrderedHash hasher;
        for (int i = 1; i <= n; i++) {
            hasher.add_value(-p[i].y + p[i].x);
        }
        hasher.process();

        p[0].x = CoordMax + 1;
        p[0].y = CoordMax + 1;
        sort(p + 1, p + n + 1, [](const Point &a, const Point &b) {
            return a.x > b.x || (a.x == b.x && a.y > b.y);
        });
        FenwickArray arr(n);
        arr.set_cmp([this](int a, int b) {
            return this->p[a].y + this->p[a].x < this->p[b].y + this->p[b].x;
        });
        arr.reset();

        for (int i = 1; i <= n; i++) {
            int id = hasher.hash(-p[i].y + p[i].x);

            if (i > 1) {
                int v = arr.query(id);

                if (v)
                    mst.add_edge(p[i].u, p[v].u, distance(p[i], p[v]));
            }

            arr.modify(id, i);
        }  // for
    }

    int n;
    Point *p;
};  // class Solver

int main() {
    // freopen("data.in", "r", stdin);

    Solver solver;
    solver.solve();

    return 0;
}  // function main
