#include <cmath>
#include <iostream>
#include <string>

using namespace std;

int Find(const string &pat, int n);
int ComputeEnd(int n);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n;
    string pat;
    cin >> n >> pat;
    cout << Find(pat, n) << endl;

    return 0;
}  // function main

int ComputeEnd(int n) {
    int result = 0;

    for (int i = 0; i < n; i++) { result += pow(2, i); }  // for

    return result;
}

int Find(const string &pat, int n) {
    int pos = 0;
    int i = 0;
    int end = ComputeEnd(n);

    for (char c = 'A', cnt = 1; i < pat.size() /* && pos <= end*/; c++, cnt++) {
        if (pat[i] != c) {
            pos = pos + pow(2, n - cnt);
            end = pos + pow(2, n - cnt - 1);
        } else {
            end = pos + pow(2, n - cnt);
            pos++;
            i++;
        }
    }  // for

    return pos;
}
