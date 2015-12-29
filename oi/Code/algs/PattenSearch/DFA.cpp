//
// Copyright 2015 riteme
//

// Accepted

#include <cassert>
#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

#define TESTCOUNT 100
#define STRING_MAX_LENGTH 50000
#define PATTERN_MAX_LENGTH 100

auto GenerateDFA(const string &pattern) -> vector<vector<int>>;
auto DFAMatch(const string &text, const string &pattern) -> int;

int main() {
    random_device rd;
    mt19937 random(rd());

    for (int cnt = 0; cnt < TESTCOUNT; cnt++) {
        string a, b;

        a.resize(random() % (STRING_MAX_LENGTH + 1));
        b.resize(random() % (PATTERN_MAX_LENGTH + 1));

        for (auto &c : a) c = (random() % 26) + 65;
        for (auto &c : b) c = (random() % 26) + 65;
        a.insert(random() % a.size(), b);

        // cout << "a: " << a << "\nb: " << b << "\n";

        int std =
            distance(a.begin(), search(a.begin(), a.end(), b.begin(), b.end()));
        // cout << "STD OK" << endl;

        int mine = DFAMatch(a, b);
        // cout << "KMP OK" << endl;

        if (std == a.size()) std = -1;
        if (mine == a.size()) mine = -1;

        if (std != mine) {
            cout << "a: " << a << "\nb: " << b << "\n";
            cout << "(error) std: " << std << ", mine: " << mine << endl;
        }
    }  // for

    return 0;
}  // function main

auto GenerateDFA(const string &pattern) -> vector<vector<int>> {
    vector<vector<int>> dfa(pattern.size());

    for (auto &l : dfa) l.resize(256);

    int x = 0, i = 1;
    dfa[0][pattern.front()] = 1;
    for (; i < pattern.size(); i++) {
        for (int j = 0; j < 256; j++) { dfa[i][j] = dfa[x][j]; }  // for

        dfa[i][pattern[i]] = i + 1;
        x = dfa[x][pattern[i]];
    }  // for

    return dfa;
}

auto DFAMatch(const string &text, const string &pattern) -> int {
    auto dfa = GenerateDFA(pattern);

    int i = 0, j = 0;
    for (; i < text.size() and j < pattern.size(); i++) {
        j = dfa[j][text[i]];
    }  // for

    if (j == pattern.size())
        return i - j;
    else
        // return -1;
        return text.size();
}
