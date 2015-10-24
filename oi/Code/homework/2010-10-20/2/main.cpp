#include <cstring>
#include <iostream>

using namespace std;

void Compages(int n, int r);
void Compages(int n, int r, int m, int depth, bool *marked, string &data);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n, r;
    cin >> n >> r;

    Compages(n, r);

    return 0;
}  // function main

void Compages(int n, int r) {
    bool marked[n + 1];
    string data;
    memset(marked, false, sizeof(bool) * (n + 1));

    Compages(n, r, 1, 1, marked, data);
}
void Compages(int n, int r, int m, int depth, bool *marked, string &data) {
    for (int i = m; i <= n; i++) {
        if (!marked[i]) {
            marked[i] = true;
            data += i + '0';

            if (depth == r) { cout << data << endl; }

            if (depth < r) { Compages(n, r, i + 1, depth + 1, marked, data); }

            data.pop_back();
            marked[i] = false;
        }
    }  // for
}
