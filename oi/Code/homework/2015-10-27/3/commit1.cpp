#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Item {
    int Value;
    int Position;

    bool operator<(const Item &lhs) const { return lhs.Value < lhs.Value; }
};  // struct Item

typedef vector<Item> VectorType;
typedef VectorType::iterator Iterator;

int Count(const VectorType &a, int l, int m, int r);
void Merge(VectorType &a, VectorType &aux, int l, int m, int r);
int Compute(VectorType &a);
void Compute(VectorType &a, VectorType &aux, int l, int r, int &result);

int main() {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    VectorType d(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i].Value;
        d[i].Position = i;
    }  // for

    cout << Compute(d);

    return 0;
}  // function main

int Count(const VectorType &a, int l, int m, int r);

void Merge(VectorType &a, VectorType &aux, int l, int m, int r) {
    for (int pos = l; pos <= r; pos++) { aux[pos] = a[pos]; }  // for

    int i = l;
    int j = m + 1;
    int k = l;

    while (k <= r) {
        if (i > m)
            a[k++] = aux[j++];
        else if (j > r)
            a[k++] = aux[i++];
        else if (aux[i] < aux[j])
            a[k++] = aux[i++];
        else
            a[k++] = aux[j++];
    }  // while

    // assert(std::is_sorted(a.begin() + l, a.begin() + r));
}

int Compute(VectorType &a) {
    VectorType aux(a.size());
    int result = 0;

    Compute(a, aux, 0, a.size() - 1, result);

    return result;
}

void Compute(VectorType &a, VectorType &aux, int l, int r, int &result) {
    if (r <= l) { return; }

    int m = (l + r) / 2;

    Compute(a, aux, l, m, result);
    Compute(a, aux, m + 1, r, result);

    result += Count(a, l, m, r);
    Merge(a, aux, l, m, r);
}
