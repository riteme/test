#include <iostream>
#include <set>

using namespace std;

typedef FILE *FilePtr;

class StreamRedirect {
 public:
    StreamRedirect(const std::string &in, const std::string &out) {
        if (!in.empty()) { freopen(in.data(), "r", stdin); }
        if (!out.empty()) { freopen(out.data(), "w", stdout); }
    }
    StreamRedirect(const StreamRedirect &other) = default;

    ~StreamRedirect() {
        fclose(stdin);
        fclose(stdout);
    }
};

template <typename T>
bool IsUnique(T a, T b, T c);

template <typename T>
void DivideNumber(set<T> &s, T num);

int main() {
    auto io = StreamRedirect("", "arrange.out");

    constexpr int NUMBER_MAX = 987 / 3;

    int currentNumber = 0;
    for (int i = 1; i <= 9 && currentNumber <= NUMBER_MAX; i++) {
        for (int j = 1; j <= 9 && currentNumber <= NUMBER_MAX; j++) {
            if (j != i) {
                for (int k = 1; k <= 9 && currentNumber <= NUMBER_MAX; k++) {
                    if (k != i && k != j) {
                        currentNumber = i * 100 + j * 10 + k;

                        if (currentNumber > NUMBER_MAX) { break; }

                        if (IsUnique(currentNumber, currentNumber * 2, currentNumber * 3)) {
                            cout << currentNumber << ' ' << currentNumber * 2 << ' ' << currentNumber * 3 << endl;
                        }  // if  IsUnique
                    }      // if  k != j && k != i
                }          // for k
            }              // if  j != i
        }                  // for j
    }                      // for i

    return 0;
}  // function main

template <typename T>
bool IsUnique(T a, T b, T c) {
    set<int> s;

    DivideNumber(s, a);
    DivideNumber(s, b);
    DivideNumber(s, c);

    return s.size() == 9;
}

template <typename T>
void DivideNumber(set<T> &s, T num) {
    while (num % 10 != 0) {
        s.insert(num % 10);
        num /= 10;
    }  // while
}
