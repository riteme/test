#include <cstring>
#include <iostream>
#include <stack>
#include <list>
#include <vector>

using namespace std;

typedef stack<int> Solution;
typedef list<Solution> SolutionList;

SolutionList FindSolutions(const vector<int> &data, int m);
void Find(const vector<int> &data, int m, int depth, int pos, bool *marked,
          SolutionList &result, Solution &current, int currentSum);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<int> S(n);
    for (int i = 0; i < n; i++) { cin >> S[i]; }  // for

    SolutionList li = FindSolutions(S, m);

    if (li.empty()) { cout << "No solution." << endl; } else {
        cout << "All solutions: " << endl;

        for (auto &e : li) {
            while (!e.empty()) {
                cout << e.top() << ' ';
                e.pop();
            }  // while
            cout << endl;
        }  // foreach in li
    }

    return 0;
}  // function main

SolutionList FindSolutions(const vector<int> &data, int m) {
    bool marked[data.size()];
    memset(marked, false, sizeof(bool) * data.size());
    SolutionList result;
    Solution tmp;

    Find(data, m, 0, 0, marked, result, tmp, 0);

    return result;
}

void Find(const vector<int> &data, int m, int depth, int pos, bool *marked,
          SolutionList &result, Solution &current, int currentSum) {
    for (int i = pos; i < data.size(); i++) {
        if (!marked[i]) {
            if (currentSum + data[i] <= m) {
                marked[i] = true;
                current.push(data[i]);
                currentSum += data[i];

                if (currentSum == m) { result.push_back(current); } else {
                    if (depth < data.size()) {
                        Find(data, m, depth + 1, i + 1, marked, result, current,
                             currentSum);
                    }
                }

                currentSum -= data[i];
                current.pop();
                marked[i] = false;
            } else { continue; }
        }
    }  // for
}
