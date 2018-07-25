// 单词的划分

#include <climits>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

#define MAX_SIZE 100
#define INFINALITY 1000000

static int r;
static int n;
static int f[MAX_SIZE + 10];
static vector<int> list[MAX_SIZE + 1];

void initialize();
void output();

int main() {
    ios::sync_with_stdio(false);
    initialize();

    for (int i = 1; i <= r; i++) {
        for (auto l : list[i]) {
            f[i] = min(f[i], f[i - l] + 1);
        }  // foreach in list[i]
    }      // for

    output();
    return 0;
}  // function main

void initialize() {
    string s, pat;
    fill(begin(f), end(f), INFINALITY);

    cin >> s >> n;
    r = s.size();
    f[0] = 0;

    for (int i = 0; i < n; i++) {
        cin >> pat;

        auto len = pat.size();
        auto iter = search(s.begin(), s.end(), pat.begin(), pat.end());

        while (iter != s.end()) {
            auto j = distance(s.begin(), iter) + len;

            list[j].push_back(len);

            iter = search(next(iter), s.end(), pat.begin(), pat.end());
        }  // while
    }      // for
}

void output() {
    // for (auto i : f) { cout << i << " "; }  // foreach in f
    // cout << endl;

    cout << f[r];
}
