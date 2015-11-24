// What the ****...

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

#define USE_QUCIK_SORT
#define USE_MERGE_SORT
#define USE_HEAP_SORT

int main() {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> numbers;
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;

        numbers.push_back(tmp);
    }  // for

#ifdef USE_QUCIK_SORT
    std::random_shuffle(numbers.begin(), numbers.begin());
    std::sort(numbers.begin(), numbers.end());
#endif  // IFDEF USE_QUCIK_SORT

#ifdef USE_HEAP_SORT
    std::random_shuffle(numbers.begin(), numbers.begin());
    std::make_heap(numbers.begin(), numbers.end());
    std::sort_heap(numbers.begin(), numbers.end());
#endif  // IFDEF USE_HEAP_SORT

#ifdef USE_MERGE_SORT
    std::random_shuffle(numbers.begin(), numbers.begin());
    std::stable_sort(numbers.begin(), numbers.end());
#endif  // IFDEF USE_MERGE_SORT

    if (numbers.size() % 2 == 1)
        cout << numbers[numbers.size() / 2];
    else
        cout << (numbers[numbers.size() / 2] +
                 numbers[numbers.size() / 2 - 1]) /
                    2;

    return 0;
}  // function main
