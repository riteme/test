#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

typedef vector<vector<int>> MapType;

bool ComputePath(unsigned path, int n, const MapType &map, int m);
void PrintPath(unsigned path, int n, const MapType &map);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n, m;
    MapType data;
    vector<unsigned> paths;
    cin >> n >> m;

    data.resize(n);
    for (int i = 0; i < n; i++) {
        data[i].resize(i + 1);
        for (int j = 0; j <= i; j++) { cin >> data[i][j]; }  // for
    }                                                        // for

    unsigned path;
    unsigned end = 0U;
    for (unsigned i = 0; i < n - 1; i++) { end = (end << 1) + 1U; }  // for
    for (path = 0U; path <= end; path++) { paths.push_back(path); }  // for

    for (auto p : paths) {
        if (ComputePath(p, n, data, m)) {
            PrintPath(p, n, data);
            cout << endl;
        }
    }  // foreach in paths

    return 0;
}  // function main

bool ComputePath(unsigned path, int n, const MapType &map, int m) {
    bitset<32> data(path << 1);

    int sum = 0;
    unsigned pos = 0;
    for (int i = n - 1; i >= 0; i--) {
        sum += map[n - i - 1][pos];
        if (data.test(i)) { pos++; }
    }  // for

    return sum == m;
}

void PrintPath(unsigned path, int n, const MapType &map) {
    bitset<32> data(path << 1);

    unsigned pos = 0;
    for (int i = n - 1; i >= 0; i--) {
        cout << map[n - i - 1][pos] << ' ';
        if (data.test(i)) { pos++; }
    }  // for
}
