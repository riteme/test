#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Stick {
    int Length /*= 0*/;
    int Weight /*= 0*/;

    bool operator<(const Stick &lhs) const {
        return (Length < lhs.Length && Weight < lhs.Weight) ||
               (Length < lhs.Length ||
                (Length == lhs.Length ? Weight < lhs.Weight : false));
    }

    bool operator<=(const Stick &lhs) const {
        return Length <= lhs.Length && Weight <= lhs.Weight;
    }
};  // struct Stick

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<Stick> s(n);
    for (int i = 0; i < n; i++) { cin >> s[i].Length >> s[i].Weight; }  // for

    std::sort(s.begin(), s.end());
    // for (auto &e : s) {
    //     cout << e.Length << ' ' << e.Weight << endl;
    // }  // foreach in s

    int d = 0;
    bool marked[n];
    memset(marked, false, sizeof(bool) * n);

    for (int i = n - 1; i >= 0; i--) {
        if (!marked[i]) {
            marked[i] = true;

            int next = i;
            for (int j = i - 1; j >= 0; j--) {
                if (!marked[j] && s[j] <= s[next]) {
                    // cout << j + 1 << " <= " << i + 1 << endl;
                    next = j;
                    marked[j] = true;
                }
            }  // for

            d++;
        }
    }  // for

    // cout << std::count(marked, marked + n, true);
    cout << d;

    return 0;
}  // function main
