#include <climits>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<vector<int>> DataType;

int SelectSolution(const DataType &data);
void Select(const DataType &d, int depth, bool *marked, bool *used, int current,
            int &min);
int MinIndex(const DataType &data, int workID, bool *used);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    DataType data(n);
    for (int x = 0; x < n; x++) {
        data[x].resize(n);
        for (int y = 0; y < n; y++) { cin >> data[x][y]; }  // for
    }                                                       // for

    cout << SelectSolution(data) << endl;

    return 0;
}  // function main

int SelectSolution(const DataType &data) {
    int min = INT_MAX;
    bool marked[data.size()];
    bool used[data.size()];

    memset(marked, false, sizeof(bool) * data.size());
    memset(used, false, sizeof(bool) * data.size());

    Select(data, 0, marked, used, 0, min);

    return min;
}

void Select(const DataType &d, int depth, bool *marked, bool *used, int current,
            int &min) {
    if (depth == d.size()) {
        if (current < min) {
            min = current;
            return;
        }
    }

    for (int i = 0; i < d.size(); i++) {
        if (!marked[i]) {
            int m = MinIndex(d, i, used);

            marked[i] = true;
            used[m] = true;

            Select(d, depth + 1, marked, used, current + d[m][i], min);

            used[m] = false;
            marked[i] = false;
        }
    }  // for
}

int MinIndex(const DataType &data, int workID, bool *used) {
    int minPos = 0, minValue = INT_MAX;

    for (int i = 0; i < data.size(); i++) {
        if (!used[i] and data[i][workID] < minValue) {
            minPos = i;
            minValue = data[i][workID];
        }
    }  // for

    return minPos;
}
