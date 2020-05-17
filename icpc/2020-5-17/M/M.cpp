#include "lcs.h"

#include <numeric>
#include <algorithm>

void find_permutation(int n, int v[]) {
    std::iota(v, v + n, 1);
    std::stable_sort(v, v + n, [](int a, int b) {
        int arr[] = {a, b};
        int len = get_lcs(2, arr);
        return len == 2;
    });
}