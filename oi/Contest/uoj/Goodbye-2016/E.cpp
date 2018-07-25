#include "isomorphism.h"
using namespace std;

void hack() {
    graph a, b;
    a.n = 11;
    a.e.push_back(make_pair(1, 2));
    a.e.push_back(make_pair(2, 3));
    a.e.push_back(make_pair(3, 4));
    a.e.push_back(make_pair(4, 5));
    a.e.push_back(make_pair(5, 6));
    a.e.push_back(make_pair(6, 7));
    a.e.push_back(make_pair(7, 8));
    a.e.push_back(make_pair(8, 9));
    a.e.push_back(make_pair(9, 10));
    a.e.push_back(make_pair(10, 11));

    b.n = 11;
    b.e.push_back(make_pair(1, 2));
    b.e.push_back(make_pair(2, 3));
    b.e.push_back(make_pair(3, 4));
    b.e.push_back(make_pair(4, 5));
    b.e.push_back(make_pair(5, 6));
    b.e.push_back(make_pair(6, 7));
    b.e.push_back(make_pair(7, 8));
    b.e.push_back(make_pair(8, 9));
    b.e.push_back(make_pair(9, 10));
    b.e.push_back(make_pair(9, 11));

    propose(a, b);
}

int identify(graph g) {
    int cnt[20] = {0};

    for (auto &e : g.e) {
        int u = e.first;
        int v = e.second;
        cnt[u]++;
        cnt[v]++;
    }  // foreach in g.e

    int maxcnt = 0;
    for (int i = 1; i <= 11; i++) {
        maxcnt = max(maxcnt, cnt[i]);
    }  // for

    return maxcnt >= 3 ? 2 : 1;
}
