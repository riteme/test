#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

static int n;
static vector<string> s;

bool cmp(const string &a, const string &b) {
    bool match = true;
    for (int i = 0; match && i < min(b.size(), a.size()); i++)
        match &= a[i] == b[i];
    return match ? (a + b) < (b + a) : a < b;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) {
        string tmp;
        cin >> tmp;
        s.push_back(move(tmp));
    }
    sort(s.begin(), s.end(), cmp);
    for (int i = 0; i < n; i++)
        cout << s[i];
    cout << endl;
    return 0;
}
