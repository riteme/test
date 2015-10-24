#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

int KmpSearch(const string &txt, const string &pat) {
    int N = txt.size(), M = pat.size();
    vector<vector<int>> dfa(256);
    for (auto &e : dfa) { e.resize(M); }

    dfa[pat[0]][0] = 1;
    for (int x = 0, j = 1; j < M; j++) {
        for (int c = 0; c < 256; c++) { dfa[c][j] = dfa[c][x]; }

        dfa[pat[j]][j] = j + 1;
        x = dfa[pat[j]][x];
    }

    int i = 0, j = 0;
    for (; i < N and j < M; i++) { j = dfa[txt[i]][j]; }

    if (j == M)
        return i - M;
    else
        return -1;  // Missmatch.
}

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    while (true) {
        string a, b;
        cin >> a >> b;
        cout << KmpSearch(a, b) << endl;
    }  // while

    return 0;
}  // function main
