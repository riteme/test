#include <iostream>
#include <vector>

using namespace std;

template <typename TRequire>
TRequire RequireInput(const string &message) {
    TRequire value;

    cout << message << ' ';
    cin >> value;

    return value;
}

template <>
string RequireInput(const string &message) {
    string value;

    // cout << message << ' ';
    getline(cin, value);

    return value;
}

template <typename TOutput>
void Output(const TOutput &message) {
    cout << message << endl;
}

enum class ElementType { Safe, Unsafe, Castle, Wall };  // enum class ElementType

typedef vector<vector<ElementType>> MapType;
typedef vector<ElementType> LineType;

constexpr unsigned SIGNAL_EXIT = 0;

constexpr char ElementSafe = '.';
constexpr char ElementUnsafe = '_';
constexpr char ElementWall = 'X';
constexpr char ElementCastle = 'O';

int GetMaxNumberOfCastles(MapType &map, unsigned size);
void CheckAndPlace(MapType &map, int x, int y);
void PrintMap(MapType &map);

int main() {
    while (true) {
        unsigned size;
        vector<string> mapData;

        size = RequireInput<unsigned>(">");
        if (size == SIGNAL_EXIT) { break; }
        cin.ignore();
        for (unsigned i = 0; i != size; i++) { mapData.push_back(RequireInput<string>(">")); }  // for

        MapType map;

        for (unsigned x = 0; x != size; x++) {
            map.push_back(LineType());
            for (unsigned y = 0; y != size; y++) {
                switch (mapData[x][y]) {
                    case ElementSafe: map[x].push_back(ElementType::Safe); break;
                    case ElementWall: map[x].push_back(ElementType::Wall); break;
                }  // switch to mapData[x][y]
            }      // for
        }          // for

        Output(GetMaxNumberOfCastles(map, size));
        // PrintMap(map);
    }

    return 0;
}  // function main

void CheckAndPlace(MapType &map, int x, int y) {
    if (x < 0 || x > map.size() - 1 || y < 0 || y > map.size() - 1) { return; }

    if (map[x][y] == ElementType::Safe) {
        map[x][y] = ElementType::Castle;

        for (int upx = 1; x - upx >= 0 && map[x - upx][y] != ElementType::Wall; upx++) { map[x - upx][y] = ElementType::Unsafe; }  // for

        for (int downx = 1; x + downx < map.size() && map[x + downx][y] != ElementType::Wall; downx++) {
            map[x + downx][y] = ElementType::Unsafe;
        }  // for

        for (int upy = 1; y - upy >= 0 && map[x][y - upy] != ElementType::Wall; upy++) { map[x][y - upy] = ElementType::Unsafe; }  // for

        for (int downy = 1; y + downy < map.size() && map[x][y + downy] != ElementType::Wall; downy++) {
            map[x][y + downy] = ElementType::Unsafe;
        }  // for
    }
}

void PrintMap(MapType &map) {
    for (auto &x : map) {
        for (auto &y : x) {
            switch (y) {
                case ElementType::Safe: cout << ElementSafe; break;
                case ElementType::Unsafe: cout << ElementUnsafe; break;
                case ElementType::Wall: cout << ElementWall; break;
                case ElementType::Castle: cout << ElementCastle; break;
            }  // switch to y
        }      // foreach in x
        cout << endl;
    }  // foreach in map
}

int GetMaxNumberOfCastles(MapType &map, unsigned size) {
    int cnt = 0;

    for (unsigned x = 0; x != size; x++) {
        for (unsigned y = 0; y != size; y++) {
            if (map[x][y] == ElementType::Wall) {
                CheckAndPlace(map, static_cast<int>(x) - 1, static_cast<int>(y));
                CheckAndPlace(map, static_cast<int>(x) + 1, static_cast<int>(y));
                CheckAndPlace(map, static_cast<int>(x), static_cast<int>(y) - 1);
                CheckAndPlace(map, static_cast<int>(x), static_cast<int>(y) + 1);
            }
        }  // for
    }      // for

    for (unsigned x = 0; x != size; x++) {
        for (unsigned y = 0; y != size; y++) {
            if (map[x][y] == ElementType::Safe) { CheckAndPlace(map, static_cast<int>(x), static_cast<int>(y)); }
        }  // for
    }      // for

    for (auto &e : map) {
        for (auto &y : e) {
            if (y == ElementType::Castle) { cnt++; }
        }  // foreach in e
    }      // foreach in map

    return cnt;
}
