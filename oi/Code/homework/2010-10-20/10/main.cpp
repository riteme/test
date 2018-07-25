#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> MapType;

int DFS(const MapType &map);
void DFSImpl(const MapType &map, int cx, int cy, int ex, int ey, int &cnt,
             MapType &marked);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    MapType map;
    map.resize(n);
    for (auto &e : map) { e.resize(n); }  // foreach in map

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            char c;
            cin >> c;
            map[x][y] = c - '0';
        }  // for
    }      // for

    cout << DFS(map) << endl;

    return 0;
}  // function main

int DFS(const MapType &map) {
    if (map.size() == 1 && map[0][0] == 1) { return 0; }

    MapType marked;
    int count = 0;

    marked.resize(map.size());
    for (auto &l : marked) {
        l.resize(map.size());

        for (auto &e : l) { e = false; }  // foreach in l
    }                                     // foreach in marked

    DFSImpl(map, 0, 0, 0, map.size() - 1, count, marked);

    return count;
}

void DFSImpl(const MapType &map, int cx, int cy, int ex, int ey, int &cnt,
             MapType &marked) {
    constexpr int dx[] = { 0, 1, -1 };
    constexpr int dy[] = { 0, 1, -1 };

    if (cx == ex and cy == ey) {
        cnt++;
        return;
    }

    marked[cx][cy] = true;

    for (auto i : dx) {
        for (auto j : dy) {
            int nx = cx + i;
            int ny = cy + j;

            if (0 <= nx and nx < map.size() and 0 <= ny and ny < map.size() and
                !marked[nx][ny] and map[nx][ny] != 1) {
                DFSImpl(map, nx, ny, ex, ey, cnt, marked);
            }
        }  // foreach in dy
    }      // foreach in dx

    marked[cx][cy] = false;
}
