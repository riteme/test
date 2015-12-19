#include <iostream>
#include <list>
#include <iterator>

using namespace std;

typedef list<short>::iterator iterator_t;

static int n;
static list<short> l;

int main() {
    ios::sync_with_stdio(false);

    while (cin >> n) {
        l.clear();
        l.push_back(-1);
        for (int i = 0; i < n; i++) {
            int p;
            short v;
            cin >> p >> v;

            iterator_t iter = l.begin();
            for (int j = 0; j <= p; ++j) ++iter;

            l.insert(iter, v);
        }  // for

        for (iterator_t beg = ++l.begin(); beg != l.end(); beg++) {
            cout << *beg << " ";
        }  // for
        cout << "\n";
    }  // while

    return 0;
}  // function main
