#include <iostream>
#include <string>
#include <vector>

using namespace std;

void generate_next(const string pat, vector<int> &next) {
    for (int i = 1; i < pat.size(); i++) {
        int k = next[i - 1];

        while (k > 0 and pat[k] != pat[i]) { k = next[k - 1]; }  // while

        if (pat[k] == pat[i])
            next[i] = k + 1;
        else
            next[i] = 0;
    }  // for
}

int main() {
    ios::sync_with_stdio(false);

    vector<int> next;
    string pat;

    cin >> pat;
    next.resize(pat.size(), 0);

    generate_next(pat, next);

    for (auto i : next) { cout << i << " "; }  // foreach in next
    cout << endl;

    return 0;
}  // function main
