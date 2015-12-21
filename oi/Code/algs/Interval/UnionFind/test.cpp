#include <iostream>
#include "UnionFind.hpp"

#define UNION 'C'
#define QUERY 'Q'

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    int n;
    cout << "n: ";
    cin >> n;

    UnionFind uf(n);
    char command;
    int a, b;
    while (cin >> command >> a >> b) {
        switch (command) {
            case UNION: uf.Union(a - 1, b - 1); break;
            case QUERY:
                cout << boolalpha << (uf.Find(a - 1) == uf.Find(b - 1)) << endl;
                break;
        }  // switch to command
    }

    return 0;
}  // function main
