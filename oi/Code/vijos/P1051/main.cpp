#include <iostream>
#include <list>
#include <queue>

using namespace std;

struct Point {
    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}

    int x;
    int y;
};  // struct Point

typedef list<Point> ListType;
typedef queue<Point, ListType> Queue;

#define DEBUG false

#define NMAX 100
#define UNLIGHT '-'
#define LIGHTED '#'

static int marked[NMAX][NMAX];
static bool map[NMAX][NMAX];
static int n, m;

int Search();
void _PrintMap();
void _PrintMarked();

inline bool Check(const int x, const int y) {
    return marked[x][y] == 0 and map[x][y];
}

inline bool Check(const Point &p) { return Check(p.x, p.y); }

inline bool CheckPlacable(const int x, const int y) {
    return 0 <= x and x < n and 0 <= y and y < m and Check(x, y);
}

inline bool CheckPlacable(const Point &p) { return CheckPlacable(p.x, p.y); };

int main() {
    ios::sync_with_stdio(false);

    cin >> n >> m;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            char c;
            cin >> c;

            if (c == UNLIGHT) { map[x][y] = false; } else {
                map[x][y] = true;
            }

            marked[x][y] = 0;
        }  // for
    }      // for

    cout << Search();

    if (DEBUG) {
        _PrintMap();
        cout << endl;
        _PrintMarked();
    }

    return 0;
}  // function main

int Search() {
#define STATUS_SIZE 12

    const int dx[STATUS_SIZE] = { -2, -1, -1, -1, 0, 0, 0, 0, 1, 1, 1, 2 };
    const int dy[STATUS_SIZE] = { 0, -1, 0, 1, -2, -1, 1, 2, -1, 0, 1, 0 };

    Queue q;
    int id = 1;

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            if (Check(x, y)) {
                q.push(Point(x, y));

                while (!q.empty()) {
                    Point p = q.front();
                    q.pop();

                    if (Check(p)) {
                        marked[p.x][p.y] = id;

                        for (int i = 0; i < STATUS_SIZE; i++) {
                            if (CheckPlacable(p.x + dx[i], p.y + dy[i])) {
                                q.push(Point(p.x + dx[i], p.y + dy[i]));
                            }
                        }  // for
                    }

                }  // while

                id++;
            }
        }  // for
    }      // for

    return id - 1;

#undef STATUS_SIZE
}

void _PrintMap() {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) { cout << map[x][y]; }  // for

        cout << endl;
    }  // for
}

void _PrintMarked() {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) { cout << marked[x][y] << " "; }  // for

        cout << endl;
    }  // for
}
