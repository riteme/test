// 16/40 TLE

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<unsigned> VectorType;
typedef vector<VectorType> DFA;
typedef VectorType BigNumber;

void GenerateDFA(const string &patten, DFA &target);
void Increase(BigNumber &n);
inline unsigned ToNumber(const char c);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    string pat;
    cin >> pat;

    DFA d;
    GenerateDFA(pat, d);

    unsigned i = 1U, j = 0U;
    BigNumber n;
    n.push_back(1U);
    n.reserve(200U);

    while (j < pat.size()) {
        for (VectorType::reverse_iterator beg = n.rbegin();
             beg != n.rend() && j < pat.size();
             beg++) {
            j = d[*beg][j];
            i++;
        }  // for

        Increase(n);
    }  // while

    cout << i - pat.size() << endl;

    return 0;
}  // function main

void GenerateDFA(const string &patten, DFA &target) {
    target.resize(10);
    for (DFA::iterator e = target.begin(); e != target.end(); e++) {
        e->resize(patten.size());
    }  // foreach in target

    target[ToNumber(patten[0])][0] = 1U;
    for (unsigned x = 0U, j = 1U; j < patten.size(); j++) {
        for (unsigned c = 0U; c < 10U; c++) {
            target[c][j] = target[c][x];
        }  // for

        target[ToNumber(patten[j])][j] = j + 1;
        x = target[ToNumber(patten[j])][x];
    }  // for
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

    if (upload > 0U) { n.push_back(upload); }
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
