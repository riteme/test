#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n;
    vector<int> data;

    cin >> n;

    int average = 0;
    data.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> data[i];
        average += data[i];
    }  // for
    average /= n;

    std::sort(data.begin(), data.end());

    list<int> weight;
    for (auto i : data) { weight.push_back(i); }  // foreach in data

    int a = 0, b = 0;
    while (!weight.empty()) {
        if (weight.size() == 1) {
            if (abs(a + weight.front() - average) <=
                abs(b + weight.front() - average)) {
                a += weight.front();
            } else { b += weight.front(); }

            break;
        } else if (weight.size() == 2) {
            a += weight.front();
            b += weight.back();

            if (abs(a + weight.back() - average) <=
                abs(b + weight.front() - average)) {
                a = a - weight.front() + weight.back();
                b = b - weight.back() + weight.front();
            } else {
                a = a - weight.back() + weight.front();
                b = b - weight.front() + weight.back();
            }

            break;
        } else {
            auto x = weight.begin();
            auto y = --weight.end();

            for (auto it = y; it != x; it--) {
                if (abs((*x + *it) / 2 - average) <
                    abs((*x + *y) / 2 - average)) {
                    y = it;
                }
            }  // for

            a += *x;
            b += *y;

            std::swap(a, b);

            weight.pop_front();
            weight.erase(y);
        }
    }  // while

    cout << std::min(a, b) << ' ' << std::max(a, b) << endl;

    return 0;
}  // function main
