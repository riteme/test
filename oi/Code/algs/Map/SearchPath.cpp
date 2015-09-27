#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename TElement>
class Map {
 public:
    Map(int width, int height, TElement defaultValue = TElement()) {
        Resize(width, height, defaultValue);
    }
    ~Map() = default;

    vector<TElement> &operator[](const int lineIndex) { return m_map[lineIndex]; }
    vector<TElement> operator[](const int lineIndex) const { return m_map[lineIndex]; }

    int Width() const { return m_map[0].size() - 1; }
    int Height() const { return m_map.size() - 1; }

    void Resize(int width, int height, TElement defaultValue = TElement()) {
        m_map.resize(height + 1);

        for (auto &line : m_map) {
            line.resize(width + 1);
            for (auto &e : line) { e = defaultValue; }  // foreach in line
        }                                               // foreach in m_map
    }

 private:
    vector<vector<TElement>> m_map;
};  // class Map

constexpr char ELEMENT_GROUND = '.';
constexpr char ELEMENT_WALL = 'X';
constexpr char ELEMENT_A = 'A';
constexpr char ELEMENT_B = 'B';

enum class ElementType { Ground, Wall, A, B, Unknown };  // enum class ElementType

template <typename TMapElement>
void ReadMap(Map<TMapElement> &targetMap);

template <typename TMapElement>
void PrintMap(const Map<TMapElement> &map);

template <typename TTo, typename TFrom>
TTo ConvertTo(const TFrom &object);

template <typename T>
string ToString(const T &object);

void UpdateDistanceMap(const Map<ElementType> &map, Map<int> &distanceMap);
void ComputeDistanceMap(const Map<ElementType> &map, Map<int> &distanceMap);

template <typename TTarget>
void GetPosition(const Map<ElementType> &map, TTarget target, int &x, int &y);

int main(/*int argc, char *argv[]*/) {
    cout.sync_with_stdio(false);

    int mapWidth, mapHeight;
    cin >> mapWidth >> mapHeight;

    Map<ElementType> map(mapWidth, mapHeight);
    Map<int> distanceMap(mapWidth, mapHeight, -1);

    ReadMap(map);
    UpdateDistanceMap(map, distanceMap);
    ComputeDistanceMap(map, distanceMap);

    cout << endl;
    PrintMap(map);
    cout << endl;
    PrintMap(distanceMap);

    return 0;
}  // function main

void UpdateDistanceMap(const Map<ElementType> &map, Map<int> &distanceMap) {
    for (int i = 1; i <= map.Height(); i++) {
        for (int j = 1; j <= map.Width(); j++) {
            switch (map[i][j]) {
                case ElementType::Ground:
                case ElementType::A:
                case ElementType::B: distanceMap[i][j] = 0; break;
                case ElementType::Wall:
                case ElementType::Unknown: distanceMap[i][j] = -1; break;
            }  // switch to map[i][j]
        }      // for
    }          // for
}

void ComputeDistanceMap(const Map<ElementType> &map, Map<int> &distanceMap) {
    int aX, aY, bX, bY;
    GetPosition(map, ElementType::A, aX, aY);
    GetPosition(map, ElementType::B, bX, bY);
}

template <typename TTarget>
void GetPosition(const Map<ElementType> &map, TTarget target, int &x, int &y) {
    for (int i = 1; i <= map.Height(); i++) {
        for (int j = 1; j <= map.Width(); j++) {
            if (map[i][j] == target) {
                x = i;
                y = j;
                return;
            }  // if
        }      // for
    }          // for
}

template <typename TMapElement>
void ReadMap(Map<TMapElement> &targetMap) {
    for (int i = 1; i <= targetMap.Height(); i++) {
        for (int j = 1; j <= targetMap.Width(); j++) {
            char tmp;
            cin >> tmp;
            targetMap[i][j] = ConvertTo<ElementType>(tmp);
        }  // for
    }      // for
}

template <typename TMapElement>
void PrintMap(const Map<TMapElement> &map) {
    for (int i = 1; i <= map.Height(); i++) {
        for (int j = 1; j <= map.Width(); j++) { cout << ToString(map[i][j]); }  // for
        cout << endl;
    }  // for
}

template <>
ElementType ConvertTo(const char &object) {
    switch (object) {
        case ELEMENT_GROUND: return ElementType::Ground;
        case ELEMENT_WALL: return ElementType::Wall;
        case ELEMENT_A: return ElementType::A;
        case ELEMENT_B: return ElementType::B;
    }  // switch to object

    return ElementType::Unknown;
}

template <typename T>
string ToString(const T &object) {
    return std::to_string(object);
}

template <>
string ToString(const ElementType &object) {
    switch (object) {
        case ElementType::Ground: return string(".");
        case ElementType::Wall: return string("X");
        case ElementType::A: return string("A");
        case ElementType::B: return string("B");
        case ElementType::Unknown: return string("?");
    }  // switch to object

    return string("?");
}
