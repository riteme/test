#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef unsigned long long FuckableType;

typedef vector<int> VectorType;
typedef VectorType::iterator Iterator;

void Merge(VectorType &a, VectorType &aux, int l, int m, int r,
           FuckableType &result);
FuckableType Compute(VectorType &a);
void Compute(VectorType &a, VectorType &aux, int l, int r,
             FuckableType &result);

int main() {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    VectorType d(n);
    for (int i = 0; i < n; i++) { cin >> d[i]; }  // for

    cout << Compute(d);

    // assert(std::is_sorted(d.begin(), d.end()));

    return 0;
}  // function main

void Merge(VectorType &a, VectorType &aux, int l, int m, int r,
           FuckableType &result) {
    for (int pos = l; pos <= r; pos++) { aux[pos] = a[pos]; }  // for

    int i = l;
    int j = m + 1;
    int k = l;

    while (k <= r) {
        if (i > m)
            a[k++] = aux[j++];
        else if (j > r) {
            a[k++] = aux[i++];
            result += r - m;  // when left part is empty, the remianing elements
                              // of right part must be greater than all the
                              // elements in left part.
        } else if (aux[i] <= aux[j]) {
            a[k++] = aux[i++];
            result += j - m - 1;  // if aux[i] <= aux[j],then aux[i] > aux[j -
                                  // 1], aux[j - 2], ... , aux[m + 1].
        } else
            a[k++] = aux[j++];
    }  // while
}

FuckableType Compute(VectorType &a) {
    VectorType aux(a.size());
    FuckableType result = 0;

    Compute(a, aux, 0, a.size() - 1, result);

    return result;
}

void Compute(VectorType &a, VectorType &aux, int l, int r,
             FuckableType &result) {
    if (r <= l) { return; }

    int m = (l + r) / 2;

    Compute(a, aux, l, m, result);
    Compute(a, aux, m + 1, r, result);

    Merge(a, aux, l, m, r, result);
}
