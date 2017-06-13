#include "testlib.h"

using namespace std;

#define NMAX 1000

enum BlockType {
    UNKNOWN = 0,
    RIGHT,
    DOWN,
};  // enum BlockType

static int t, n, m, LIMIT;
static int S[NMAX][NMAX], T[NMAX][NMAX];

void read_data(int a[NMAX][NMAX]) {
    string buf;

    memset(a, 0, sizeof(int) * NMAX * NMAX);
    for (int i = 0; i < n;) {
        buf = inf.readLine();

        if (buf.empty() || (buf[0] != '#' && buf[0] != '$'))
            continue;

        for (int j = 0; j < m; j++) {
            if (buf[j] == '$' && (i == 0 || a[i - 1][j] != DOWN))
                a[i][j] = DOWN;
            if (buf[j] == '#' && (j == 0 || a[i][j - 1] != RIGHT))
                a[i][j] = RIGHT;
        }  // for

        i++;
    }  // for
}

inline bool rotatable(int x, int y, int a[NMAX][NMAX]) {
    return !(a[x][y] == UNKNOWN ||
             (a[x][y] == RIGHT && a[x][y] != a[x + 1][y]) ||
             (a[x][y] == DOWN && a[x][y] != a[x][y + 1]));
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    t = inf.readInt();
    n = inf.readInt();
    m = inf.readInt();
    LIMIT = inf.readInt();

    int score = 0;
    read_data(S);
    for (int i = 0; i < t; i++, score++) {
        read_data(T);

        int k = ouf.readInt(0, 1000000000, "k");
        ouf.readEoln();
        for (int j = 0; j < k; j++) {
            if (LIMIT <= 0)
                quitp(score / 10.0, "NAÏVE!!! No opportunities.");
            LIMIT--;

            int x = ouf.readInt(1, n, "x") - 1;
            ouf.readSpace();
            int y = ouf.readInt(1, m, "y") - 1;
            ouf.readEoln();

            if (!rotatable(x, y, S))
                quitp(0.0, "NAÏVE!!! Invalid rotation.");

            if (S[x][y] == RIGHT) {
                S[x][y] = S[x][y + 1] = DOWN;
                S[x + 1][y] = UNKNOWN;
            } else {
                S[x][y] = S[x + 1][y] = RIGHT;
                S[x][y + 1] = UNKNOWN;
            }
        }  // for

        if (memcmp(S, T, sizeof(S)) != 0)
            quitp(score / 10.0, "NAÏVE!!! Wrong answer.");
    }  // for

    if (score == 10)
        quit(_ok, "EXCITED!!!");

    return 0;
}  // function main
