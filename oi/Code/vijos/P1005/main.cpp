// 16/40 TLE - Commit #1

#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<unsigned> VectorType;
typedef VectorType BigNumber;
typedef unsigned long long Number;

void Increase(BigNumber &n);
inline unsigned ToNumber(const char c);
Number ToNumber(const BigNumber &n);
Number GetPosition(const Number n);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    VectorType pat;
    pat.reserve(200);

    char tmp;
    while (cin >> tmp) { pat.push_back(ToNumber(tmp)); }  // while
    std::reverse(pat.begin(), pat.end());

    BigNumber n;
    BigNumber s;
    Number offest = 0;
    bool found = false;
    for (unsigned len = 1; len <= pat.size() && !found; len++) {
        for (unsigned j = 0; j < len; j++) {
            n.resize(len);
            std::copy_n(pat.end() - j - 1, len, n.begin());
            s = n;

            found = true;
            for (unsigned k = j + len; k < pat.size(); k += len) {
                // for (auto &e : n) { cout << e; }  // foreach in s
                // cout << endl;

                for (auto beg = pat.end() - k; beg != pat.end() - k + len;
                     beg++) {
                    cout << *beg;
                }  // for
                cout << endl;

                if (!std::equal(pat.end() - k, pat.end() - k + len,
                                n.begin())) {
                    found = false;

                    break;
                }

                Increase(n);
            }  // for

            if (found) {
                offest = j;

                break;
            }
        }  // for
    }      // for

    for (auto &e : s) { cout << e; }  // foreach in s
    cout << endl;

    cout << GetPosition(ToNumber(s)) - offest << endl;

    return 0;
}  // function main

void Increase(BigNumber &n) {
    unsigned upload = 1U;
    unsigned i = 0U;

    while (i < n.size()) {
        n[i] += upload;

        if (n[i] > 9U) {
            upload = n[i] / 10U;
            n[i] = n[i] % 10U;
            i++;
        } else {
            upload = 0U;
            break;
        }
    }  // while

    if (upload > 0U) { n.push_back(upload); }
}

Number GetPosition(const Number n) {
    if (n < 10ULL) { return n; }

    Number length = Number(log10(n));
    Number down = pow(10ULL, length) - 1ULL;
    return (n - down) * (length + 1) + GetPosition(down) - length;
}

inline unsigned ToNumber(const char c) {
    switch (c) {
        case '0': return 0U;
        case '1': return 1U;
        case '2': return 2U;
        case '3': return 3U;
        case '4': return 4U;
        case '5': return 5U;
        case '6': return 6U;
        case '7': return 7U;
        case '8': return 8U;
        case '9': return 9U;
    }  // switch to c

    return 10U;
}

inline Number ToNumber(const BigNumber &n) {
    Number result = 0ULL;

    for (int i = n.size() - 1; i >= 0; i--) {
        result *= 10ULL;
        result += n[i];
    }  // for

    return result;
}
