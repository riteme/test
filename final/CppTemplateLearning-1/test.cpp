#include <iostream>
#include <vector>
using namespace std;

template <typename T, unsigned N>
void Print(const T(&arr)[N]) {
    for (auto &e : arr) {
        cout << e << ' ';
    }
    cout << endl;
}

template <typename T, unsigned N>
T *Begin(T(&arr)[N]) {
    return &arr[0];
}

template <typename T, unsigned N>
T *End(T(&arr)[N]) {
    return &arr[N];
}

template <typename T, unsigned N>
constexpr unsigned Length(const T(&arr)[N]) {
    return N;
}

int main() {
    int ints[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    cout << Length(ints) << endl;
    Print(ints);
    vector<int> vec(Begin(ints), End(ints));
    for (auto &e : vec) {
        cout << e << ' ';
    }
    cout << endl;
    return 0;
}
