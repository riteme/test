// 奶牛浴场

#include <cstring>
#include <climits>
#include <cstdio>
#include <algorithm>

using namespace std;

#define SIZEMAX 30000

void initialize();
void quit();

static int l, w;
static int answer;
static int x[SIZEMAX + 10][SIZEMAX + 10];
static int y[SIZEMAX + 10][SIZEMAX + 10];

inline int size(int i, int j, int x0, int y0) { return (i - x0) * (j - y0); }

int main() {
    initialize();

    for (int i = 0; i < l; i++) {
        for (int j = 0; j < w; j++) {
            x[i][j] = i;
            y[i][j] = j;

            if (size(i, j, x[i][j - 1], y[i][j - 1]) >
                size(i, j, x[i][j], y[i][j])) {
                x[i][j] = x[i][j - 1];
                y[i][j] = y[i][j - 1];
            }

            if (i != 0) {
                if (size(i, j, x[i - 1][j - 1], y[i - 1][j - 1]) >
                    size(i, j, x[i][j], y[i][j])) {
                    x[i][j] = x[i - 1][j - 1];
                    y[i][j] = y[i - 1][j - 1];
                }

                if (size(i, j, x[i - 1][j], y[i - 1][j]) >
                    size(i, j, x[i][j], y[i][j])) {
                    x[i][j] = x[i - 1][j];
                    y[i][j] = y[i - 1][j];
                }
            }

            answer = max(answer, size(i, j, x[i][j], y[i][j]));
        }  // for
    }      // for

    quit();
    return 0;
}  // function main

void initialize() {
    int n;
    scanf("%d %d %d", &l, &w, &n);

    for (int i = 0; i < n; i++) {
        int x0, y0;
        scanf("%d %d", &x0, &y0);

        x[x0][y0] = y[x0][y0] = SIZEMAX + 100;
    }  // for

    answer = 0;
}

void quit() { printf("%d", answer); }
