#include <cstring>
#include <iostream>
#include <climits>
#include <string>
#include <algorithm>

using namespace std;

static string text;

int main() {
    ios::sync_with_stdio(false);

    int t;
    cin >> t;

    string pats[] = { "output", "puton", "input", "one", "out", "in" };

    for (int i = 0; i < t; i++) {
        cin >> text;

        int p = 0;
        while (p < text.size()) {
            bool flag = false;
            for (auto &s : pats) {
                if (p + s.size() < text.size() &&
                    equal(s.begin(), s.end(), text.begin() + p)) {
                    p += s.size();
                    flag = true;
                    break;
                }
            }  // foreach in

            if (!flag) {
                cout << "NO\n";
                break;
            }
        }  // while

        if (p >= text.size())
            cout << "YES\n";
    }  // for
    return 0;
}  // function main
