//
// Copyright 2015 riteme
//

#include "PriorityQueue.hpp"

#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

#define N 10000000

static int a[N];

int main() {
    ios::sync_with_stdio(false);

    int cnt = 0;
    std::generate_n(begin(a), N, [&cnt]() { return cnt++; });
    std::random_shuffle(begin(a), end(a));

    PriorityQueue<int> pq;
    assert(pq.Size() == 0);

    for (auto i : a) { pq.Push(i); }  // foreach in a

    assert(pq.Size() == N);

    for (auto beg = begin(a); beg != end(a); beg++) {
        *beg = pq.Top();
        pq.Pop();
    }  // for

    assert(pq.Size() == 0);
    assert(std::is_sorted(begin(a), end(a)));

    return 0;
}  // function main
