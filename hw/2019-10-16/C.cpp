#include <cstdio>
#include <cstring>

#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        if (!n) break;
        string s;
        unordered_map<string, int> cnt;
        for (int i = 0; i < n; i++) {
            cin >> s;
            cnt[s]++;
        }
        auto mx = cnt.begin();
        for (auto it = next(mx); it != cnt.end(); it++)
            if (it->second > mx->second) mx = it;
        cout << mx->first << endl;
    }
    return 0;
}
