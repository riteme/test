#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int m, n;
    cin >> m >> n;

    vector<int> data(n);
    for (auto &e : data) { cin >> e; }  // foreach in data

    std::sort(data.begin(), data.end());

    int cnt = 0;
    for (int i = 0; i < data.size(); i++) {
        int current = data[i];
        int next = -1;

        while (current + (next == -1 ? 0 : data[next]) <= m) {
            if (next != -1) {
                current += data[next];
                data.erase(data.begin() + next);
            }

            next = -1;
            int min = INT_MAX;
            for (int j = i + 1; j < data.size(); j++) {
                int v = current + data[j];
                if (v <= m && m - v < min) {
                    next = j;
                    min = m - v;
                }
            }  // for

            if (next == -1) { break; }
        }

        cnt++;
    }  // for

    cout << cnt;

    return 0;
}  // function main
