#include <climits>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

void Shrink(list<int> &target);
bool Combine(list<int> &target);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int m, n;
    cin >> m >> n;

    vector<int> s(n, INT_MIN);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int tmp;
            cin >> tmp;

            if (tmp > s[j]) { s[j] = tmp; }
        }  // for
    }      // for

    list<int> data;
    for (int i = 0; i < s.size(); i++) { data.push_back(s[i]); }  // for

    do { Shrink(data); } while (!Combine(data));  // do ... while

    int sum = 0;
    for (list<int>::iterator beg = data.begin(); beg != data.end(); beg++) {
        sum += *beg;
    }  // for

    cout << sum;

    return 0;
}  // function main

void Shrink(list<int> &target) {
    while (target.size() > 0 && target.front() <= 0) {
        target.pop_front();
    }  // while

    while (target.size() > 0 && target.back() <= 0) {
        target.pop_back();
    }  // while
}

bool Combine(list<int> &target) {
    bool status = true;

    for (list<int>::iterator beg = target.begin(); beg != target.end(); beg++) {
        if (*beg <= 0) {
            int v = *beg;
            beg = target.erase(beg);
            *beg += v;

            status = false;
        }
    }  // for

    return status;
}
