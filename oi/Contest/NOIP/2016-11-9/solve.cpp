#pragma GCC optimize(3)

#include <cstdio>
#include <climits>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 60

struct Array {
    Array() : _size(0) {
        memset(_array, 0, sizeof(_array));
    }

    int _size;
    int _array[NMAX + 10];

    int &operator[](const size_t i) {
        return _array[i];
    }

    int *begin() {
        return _array;
    }

    int *end() {
        return _array + _size;
    }

    bool empty() const {
        return _size == 0;
    }

    int size() const {
        return _size;
    }

    void push_back(int v) {
        _array[_size++] = v;
    }

    void erase(int v) {
        int *iter = find(begin(), end(), v);

        if (iter != end()) {
            swap(*iter, *(end() - 1));
            _size--;
        }
    }
};

static int n, w;
static Array to[NMAX + 10];
static Array has[NMAX + 10];
static int cnt[NMAX + 10];
static bool marked[NMAX + 10];
static bool invalid[NMAX + 10];
static int answer = INT_MAX;

static void dfs(int x, int sum) {
    if (sum >= answer)
        return;
    if (x == n + 1) {
        answer = sum;
        return;
    }

    if (cnt[x])
        dfs(x + 1, sum);
    else {
        if (sum >= answer - 1)
            return;

        for (size_t pos = 0; pos < has[x].size(); pos++) {
            int i = has[x][pos];

            for (size_t j = 0; j < to[i].size(); j++)
                cnt[to[i][j]]++;

            dfs(x + 1, sum + 1);

            for (size_t j = 0; j < to[i].size(); j++)
                cnt[to[i][j]]--;
        }
    }
}

inline bool subset(Array &a, Array &b) {
    for (size_t i = 0; i < a.size(); i++)
        if (find(b.begin(), b.end(), a[i]) == b.end())
            return false;

    return true;
}

int main() {
    freopen("solve.in", "r", stdin);
    freopen("solve.out", "w", stdout);
    scanf("%d%d", &n, &w);

    for (int i = 1; i <= w; i++) {
        int l;
        scanf("%d", &l);

        for (int j = 0; j < l; j++) {
            int v;
            scanf("%d", &v);

            to[i].push_back(v);
            has[v].push_back(i);
        }
    }

    for (int i = 1; i <= w; i++)
        for (int j = i + 1; j <= w; j++)
            if (subset(to[i], to[j]))
                invalid[i] = true;
            else if (subset(to[j], to[i]))
                invalid[j] = true;

    int addon = 0;
    for (int i = 1; i <= n; i++) {
        if (has[i].size() == 1) {
            int u = has[i][0];

            if (!invalid[u])
                addon++; 

            invalid[u] = true;
            for (size_t j = 0; j < to[has[i][0]].size(); j++)
                cnt[to[u][j]]++;
        }
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= w; j++)
            if (invalid[j])
                has[i].erase(j);

    dfs(1, 0);
    printf("%d\n", answer + addon);

    fclose(stdin);
    fclose(stdout);
    return 0;
}
