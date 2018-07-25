#include <iostream>
#include <set>

using namespace std;

set<string> Perm(int n, const string &data);
void Perm(int n, const string &data, int depth, bool *marked,
          set<string> &solution, string &tmp);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n;
    string data;
    cin >> n >> data;

    set<string> result = Perm(n, data);

    for (auto &e : result) { cout << e << '\n'; }  // foreach in result
    cout << result.size() << endl;

    return 0;
}  // function main

set<string> Perm(int n, const string &data) {
    bool marked[n];
    set<string> solution;
    string tmp;

    memset(marked, false, sizeof(bool) * n);

    Perm(n, data, 0, marked, solution, tmp);

    return solution;
}

void Perm(int n, const string &data, int depth, bool *marked,
          set<string> &solution, string &tmp) {
    for (int i = 0; i < n; i++) {
        if (!marked[i]) {
            marked[i] = true;
            tmp += data[i];

            if (depth == n - 1) { solution.insert(tmp); } else {
                Perm(n, data, depth + 1, marked, solution, tmp);
            }

            tmp.pop_back();
            marked[i] = false;
        }
    }  // for
}
