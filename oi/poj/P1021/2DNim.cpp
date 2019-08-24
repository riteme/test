#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef vector<bool> BoolVector;
typedef vector<BoolVector> MapType;
typedef vector<int> FigureType;

struct Point {
    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }

    int x, y;
};  // struct Point

static MapType map1;
static MapType map2;
static FigureType figure1;
static FigureType figure2;
static MapType marked;
static int w, h, n;

void ReadData(MapType &map);
void ComputeFigure(const MapType &map, FigureType &output);
bool IsEqual(FigureType &fig1, FigureType &fig2);

void ResetMarked(int width, int height);

int main() {
    ios::sync_with_stdio(false);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> w >> h >> n;

        ReadData(map1);
        ReadData(map2);

        ComputeFigure(map1, figure1);
        ComputeFigure(map2, figure2);

        if (IsEqual(figure1, figure2))
            cout << "YES\n";
        else
            cout << "NO\n";
    }  // for

    return 0;
}  // function main

void ReadData(MapType &map) {
    map.resize(w);
    for (int i = 0; i < w; i++) { map[i].resize(h, false); }  // for

    int x, y;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        map[x][y] = true;
    }  // for
}

void ComputeFigure(const MapType &map, FigureType &output) {
    ResetMarked(w, h);

    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            if (!marked[x][y] and map[x][y]) {
                int cnt = 0;
                queue<Point> q;
                q.push(Point(x, y));

                while (!q.empty()) {
                    Point p = q.front();
                    q.pop();

                    if (0 <= p.x and p.x < w and 0 <= p.y and p.y < h and
                        map[p.x][p.y] and !marked[p.x][p.y]) {
                        cnt++;

                        if (0 <= x - 1 and x - 1 < w and 0 <= y and y < h and
                            !marked[x - 1][y]) {
                            q.push(Point(x - 1, y));
                        }

                        if (0 <= x + 1 and x + 1 < w and 0 <= y and y < h and
                            !marked[x + 1][y]) {
                            q.push(Point(x + 1, y));
                        }

                        if (0 <= x and x < w and 0 <= y - 1 and y - 1 < h and
                            !marked[x][y - 1]) {
                            q.push(Point(x, y - 1));
                        }

                        if (0 <= x and x < w and 0 <= y + 1 and y + 1 < h and
                            !marked[x][y + 1]) {
                            q.push(Point(x, y + 1));
                        }

                        marked[p.x][p.y] = true;
                    }

                }  // while

                output.push_back(cnt);
            }
        }  // for
    }      // for
}

bool IsEqual(FigureType &fig1, FigureType &fig2) {
    std::sort(fig1.begin(), fig1.end());
    std::sort(fig2.begin(), fig2.end());

    return fig1 == fig2;
}

void ResetMarked(int width, int height) {
    marked.resize(width);
    for (int i = 0; i < width; i++) { marked[i].resize(height, false); }  // for
}
