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
#define STRING_MAX_LENGTH 100

auto GenerateNextArray(const string &pattern) -> vector<int>;
auto KmpSearch(const string &text, const string &pattern) -> int;

int main() {
    random_device rd;
    mt19937 random(rd());

    for (int cnt = 0; cnt < TESTCOUNT; cnt++) {
        string a, b;

        a.resize(random() % (STRING_MAX_LENGTH + 1));
        b.resize(random() % (STRING_MAX_LENGTH + 1));

        for (auto &c : a) c = (random() % 26) + 65;
        for (auto &c : b) c = (random() % 26) + 65;
        a.insert(random() % a.size(), b);

        // cout << "a: " << a << "\nb: " << b << "\n";

        int std =
            distance(a.begin(), search(a.begin(), a.end(), b.begin(), b.end()));
        // cout << "STD OK" << endl;

        int mine = KmpSearch(a, b);
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

auto GenerateNextArray(const string &pattern) -> vector<int> {
    vector<int> next(pattern.size() + 1);

    for (int i = 1; i < pattern.size(); i++) {
        int k = next[i];

        while (k > 0 and pattern[k] != pattern[i]) k = next[k];

        if (pattern[k] == pattern[i]) k++;

        next[i + 1] = k;
    }  // for

    // cout << "Next array generated" << endl;

    return next;
}

auto KmpSearch(const string &text, const string &pattern) -> int {
    auto next = GenerateNextArray(pattern);

    int i = 0, j = 0;
    for (; i < text.size() and j < pattern.size(); i++) {
        if (text[i] == pattern[j])
            j++;
        else
            j = next[j];
    }  // for

    if (j == pattern.size())
        return i - j;
    else
        // return -1;
        return text.size();
}
