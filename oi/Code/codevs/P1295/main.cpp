#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> VectorType;

int Queen(int n);
void Queen(int n, int depth, vector<VectorType> &marked, int &solution);

void Mark(int value, int to, vector<VectorType> &data, int x, int y);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    cout << Queen(n) << endl;

    return 0;
}  // function main

int Queen(int n) {
    vector<VectorType> marked;
    int solution = 0;

    marked.resize(n);
    for (int i = 0; i < n; i++) {
        marked[i].resize(n);
        for (int j = 0; j < n; j++) { marked[i][j] = -1; }  // for
    }                                                       // for

    // // Mark(true, marked, n - 1, n - 1);
    // Mark(true, marked, 2, 3);

    // for (auto &l : marked) {
    //     for (auto e : l) { cout << e << ' '; }  // foreach in l
    //     cout << endl;
    // }  // foreach in marked

    Queen(n, 0, marked, solution);

    return solution;
}

void Queen(int n, int depth, vector<VectorType> &marked, int &solution) {
    for (int i = 0; i < n; i++) {
        if (marked[depth][i] == -1) {
            Mark(-1, depth, marked, depth, i);
            // solution[depth] = i + 1;

            if (depth == n - 1) { solution++; }

            if (depth < n - 1) { Queen(n, depth + 1, marked, solution); }

            // solution[depth] = 0;
            Mark(depth, -1, marked, depth, i);
        }
    }  // for
}

void Mark(int value, int to, vector<VectorType> &data, int x, int y) {
    // cout << "Mark: " << x + 1 << ", " << y + 1 << endl;

    for (int i = 0; i < data.size(); i++) {
        if (data[x][i] == value) { data[x][i] = to; }
        if (data[i][y] == value) { data[i][y] = to; }
    }  // for

    int dx, dy;

    dx = x;
    dy = y;
    while (0 <= dx && dx < data.size() && 0 <= dy && dy < data.size()) {
        if (data[dx][dy] == value) { data[dx][dy] = to; }
        dx--;
        dy--;
    }  // while

    dx = x;
    dy = y;
    while (0 <= dx && dx < data.size() && 0 <= dy && dy < data.size()) {
        if (data[dx][dy] == value) { data[dx][dy] = to; }
        dx--;
        dy++;
    }  // while

    dx = x;
    dy = y;
    while (0 <= dx && dx < data.size() && 0 <= dy && dy < data.size()) {
        if (data[dx][dy] == value) { data[dx][dy] = to; }
        dx++;
        dy++;
    }  // while

    dx = x;
    dy = y;
    while (0 <= dx && dx < data.size() && 0 <= dy && dy < data.size()) {
        if (data[dx][dy] == value) { data[dx][dy] = to; }
        dx++;
        dy--;
    }  // while

    // for (auto &l : data) {
    //     for (auto e : l) { cout << e << ' '; }  // foreach in l
    //     cout << endl;
    // }  // foreach in data
    // cout << endl;
}
//
