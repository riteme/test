// 16/40 TLE
// DFA test

#include <cmath>
#include <iostream>
#include <vector>

// #pragma GCC optimize("O2")

using namespace std;

typedef vector<unsigned> VectorType;
typedef vector<unsigned> PrefixArray;
typedef VectorType BigNumber;

void GeneratePrefixArray(const string &pattern, PrefixArray &target);
void Increase(BigNumber &n);
inline unsigned ToNumber(const char c);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    string pat;
    cin >> pat;

    PrefixArray prefix;
    GeneratePrefixArray(pat, prefix);

    unsigned i = 1U, j = 0U;
    BigNumber n;
    n.push_back(1U);
    n.reserve(200U);

    while (j < pat.size()) {
        for (VectorType::reverse_iterator beg = n.rbegin();
             beg != n.rend() && j < pat.size(); beg++, i++) {
            while (j != 0 && pat[j] != (*beg + '0')) {
                j = prefix[j];
            }  // while

            if (pat[j] == (*beg + '0')) {
                j++;
            }
        }  // for

        Increase(n);
    }  // while

    cout << i - pat.size() << endl;

    return 0;
}  // function main

void GeneratePrefixArray(const string &pattern, PrefixArray &target) {
    target.resize(pattern.size() + 1);
    target[0] = target[1] = 0;

    for (unsigned i = 1; i < pattern.size(); i++) {
        int k = target[i];
        while (k != 0 && pattern[k] != pattern[i]) {
            k = target[k];
        }  // while

        if (pattern[k] == pattern[i]) {
            k++;
        }

        target[i + 1] = k;
    }
}

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

    if (upload > 0U) {
        n.push_back(upload);
    }
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
