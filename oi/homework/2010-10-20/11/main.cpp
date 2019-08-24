#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

typedef list<int> HateList;

vector<bool> MaxSize(const vector<HateList> &d);
void Max(const vector<HateList> &d, int &max, vector<bool> &marked,
         vector<bool> &solution);
bool IsHated(const vector<HateList> &d, int u, vector<bool> &marked);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<HateList> data(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        data[u - 1].push_back(v - 1);
        data[v - 1].push_back(u - 1);
    }  // for

    auto solution = MaxSize(data);

    cout << std::count(solution.begin(), solution.end(), true) << endl;
    for (auto e : solution) { cout << e; }  // foreach in solution
    cout << endl;

    return 0;
}  // function main

vector<bool> MaxSize(const vector<HateList> &d) {
    vector<bool> marked(d.size());
    vector<bool> result(d.size());
    int max = -1;

    Max(d, max, marked, result);

    return result;
}

void Max(const vector<HateList> &d, int &max, vector<bool> &marked,
         vector<bool> &solution) {
    int i;

    for (i = 0; i < d.size(); i++) {
        if (!marked[i] and !IsHated(d, i, marked)) {
            marked[i] = true;

            Max(d, max, marked, solution);

            marked[i] = false;
        }
    }  // for

    if (i == d.size()) {
        int cnt = std::count(marked.begin(), marked.end(), true);

        if (cnt > max) {
            max = cnt;
            solution = marked;
        }
    }
}

bool IsHated(const vector<HateList> &d, int u, vector<bool> &marked) {
    for (int i = 0; i < d.size(); i++) {
        if (marked[i]) {
            for (auto e : d[i]) {
                if (e == u) { return true; }
            }  // foreach in d[i]
        }
    }  // for

    return false;
}
