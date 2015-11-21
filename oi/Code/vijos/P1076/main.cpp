#include <cstring>
#include <iostream>
#include <queue>
#include <list>

using namespace std;

#define DEBUG true

#define SHIP '#'
#define WATER '.'

#define RMAX 1000
#define CMAX 1000

#define IDENTIFY 0

struct Point {
    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}

    int x;
    int y;
};  // struct Point

typedef list<Point> PointList;
typedef queue<Point, PointList> PointQueue;

static char map[RMAX + 5][CMAX + 5];
static int marked[RMAX + 5][CMAX + 5];
static int r, c;

int Search();
bool Check(int x, int y);
bool CheckPlacable(int x, int y);
bool CheckIndependence(int x1, int y1, int x2, int y2);

bool Check(const Point &p);
bool CheckPlacable(const Point &p);
bool CheckIndependence(const Point &p1, const Point &p2);

bool FillLine(int left, int right, int d, int id);

int main() {
    ios::sync_with_stdio(false);

    cin >> r >> c;

    memset(map, WATER, sizeof(map));
    memset(marked, IDENTIFY, sizeof(marked));
    for (int x = 1; x <= r; x++) {
        for (int y = 1; y <= c; y++) { cin >> map[x][y]; }  // for
    }                                                       // for

    int s = Search();

    if (s == -1)
        cout << "Bad placement.";
    else
        cout << "There are " << s << " ships.";

    return 0;
}  // function main

int Search() {
    PointQueue q;
    int id = 1;

    for (int x = 1; x <= r; x++) {
        for (int y = 1; y <= c; y++) {
            if (Check(x, y)) {
                int d;

                for (d = y; CheckPlacable(x, d); d++) {}
                d -= 1;

                // cout << "x: " << x << ", y: " << y << ", d: " << d << endl;

                int v;
                for (v = x; v <= r and CheckPlacable(v, y); v++) {
                    if (!FillLine(y, d, v, id)) return -1;
                }
                v -= 1;

                // cout << "v: " << v << endl;

                if (!CheckIndependence(x, y, v, d)) return -1;

                id++;
            }
        }  // for
    }      // for

    return id - 1;
}

bool FillLine(int left, int right, int d, int id) {
    for (int i = left; i <= right; i++) {
        if (CheckPlacable(d, i))
            marked[d][i] = id;
        else
            return false;
    }

    return true;
}

bool Check(int x, int y) {
    return marked[x][y] == IDENTIFY and map[x][y] == SHIP;
}

bool CheckPlacable(int x, int y) {
    return 1 <= x and x <= r and 1 <= y and y <= c and
           marked[x][y] == IDENTIFY and map[x][y] == SHIP;
}

bool CheckIndependence(int x1, int y1, int x2, int y2) {
    bool status = true;

    for (int x = x1; x <= x2 and status; x++) {
        status = marked[x][y1 - 1] == IDENTIFY;
        status = marked[x][y2 + 1] == IDENTIFY;
    }  // for

    for (int y = y1; y <= y2 and status; y++) {
        status = marked[x1 - 1][y] == IDENTIFY;
        status = marked[x2 + 1][y] == IDENTIFY;
    }  // for

    return status;
}

bool Check(const Point &p) { return Check(p.x, p.y); }

bool CheckPlacable(const Point &p) { return CheckPlacable(p.x, p.y); }

bool CheckIndependence(const Point &p1, const Point &p2) {
    return CheckIndependence(p1.x, p1.y, p2.x, p2.y);
}
