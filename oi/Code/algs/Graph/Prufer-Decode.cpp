#include <cassert>

#include <iostream>
#include <queue>

using namespace std;

#define NMAX 1000

static int n;
static int seq[NMAX - 1];

static void initialize() {
    cin >> n;

    for (int i = 0; i < n - 2; i++) {
        cin >> seq[i];
    }
}

static int deg[NMAX + 1];
static int U[NMAX];
static int V[NMAX];

static void decode() {
    for (int i = 1; i <= n; i++) {
        deg[i] = 1;
    }
    for (size_t i = 0; i < n - 2; i++) {
        deg[seq[i]]++;
    }

    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1)
            q.push(i);
    }

    int pos = 0;
    while (pos < n - 2) {
        assert(!q.empty());

        int u = q.top();
        int v = seq[pos];
        q.pop();

        U[pos] = u;
        V[pos] = v;
        deg[v]--;

        if (deg[v] == 1)
            q.push(v);

        pos++;
    }

    assert(q.size() == 2);
    U[pos] = q.top();
    q.pop();
    V[pos] = q.top();
}

int main() {
    initialize();
    decode();

    cout << n << endl;
    for (size_t i = 0; i < n - 1; i++) {
        cout << U[i] << " " << V[i] << endl;
    }

    return 0;
}
