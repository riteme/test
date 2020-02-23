#include <cstdio>
#include <cstring>

#include <random>
#include <vector>
#include <algorithm>

using namespace std;

int n = 1000000;
int cnt = 0;
vector<bool> a;

void solve(const vector<int> &li) {
    if (li.empty())
        return;
    cnt += li.size() % 3;
    vector<int> nxt;
    for (int i = 0; 3 * i + 2 < li.size(); i++) {
        cnt++;
        int k = a[3*i] + a[3*i + 1] + a[3*i + 2];
        if (k == 1 || k == 2) cnt++;
        if ((k == 1 && a[3*i] == 1) || (k == 2 && a[3*i] == 0)) {
            nxt.push_back(3*i + 1);
        }
    }
    solve(nxt);
}

int main() {
    random_device rd;
    mt19937_64 randi(rd());
    a.resize(n);
    vector<int> seq;
    seq.reserve(n);
    for (int i = 0; i < n; i++) {
        seq.push_back(i);
        a[i] = 0;
    }
    solve(seq);
    printf("%d\n", cnt);
    return 0;
}