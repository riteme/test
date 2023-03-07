#include <algorithm>
#include <cstdio>
#include <map>

using namespace std;

int n;
char s[300000];

int main() {
    scanf("%d%s", &n, s);
    map<pair<int, int>, int> cnt;
    int x = 0, y = 0;
    cnt[{x, y}]++;
    for (int i = 0; i < n; i++) {
        switch (s[i]) {
            case 'L': x--; break;
            case 'R': x++; break;
            case 'U': y++; break;
            case 'D': y--; break;
        }
        cnt[{x, y}]++;
    }
    puts(any_of(cnt.begin(), cnt.end(), [](auto &e) { return e.second > 1; }) ? "Yes" : "No");
    return 0;
}
