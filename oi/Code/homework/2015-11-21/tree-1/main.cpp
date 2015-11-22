#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

typedef int ntype;

static ntype D, I;
static vector<bool> tree;
static vector<ntype> h;

inline ntype left(ntype x) { return x * 2; }

inline ntype right(ntype x) { return x * 2 + 1; }

inline ntype pow_of_two(ntype e) {
    if (e == 0) return 1;

    ntype result = 2;

    while (e > 1) {
        result *= 2;
        e--;
    }  // while

    return result;
}

int main() {
    ios::sync_with_stdio(false);

    cin >> D >> I;

    ntype size = pow_of_two(D - 1);
    ntype n = 0;
    for (int i = 0; i < D; i++) { n += pow_of_two(i); }  // for

    tree.resize(n + 1, false);
    h.resize(size + 1, 0);

    for (ntype i = 1; i < h.size(); i++) {
        ntype depth = 1;
        ntype pos = 1;

        // cout << pos;
        while (depth < D) {
            bool flag = tree[pos];
            tree[pos] = !flag;

            if (flag == false)
                pos = left(pos);
            else
                pos = right(pos);

            // cout << " -> " << pos;
            depth++;
        }  // while
        // cout << endl;

        h[i] = pos;
    }  // for

    h[0] = h[h.size() - 1];

    // for (auto i : h) { cout << i << " "; }  // foreach in h
    // cout << endl;

    cout << h[I % (h.size() - 1)];

    return 0;
}  // function main
