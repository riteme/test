#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

void Form(int n);
void Form(int n, int depth, bool *marked, vector<char> &data);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    Form(n);

    return 0;
}  // function main

void Form(int n) {
    bool marked[n + 1];
    vector<char> data;
    memset(marked, false, sizeof(bool) * (n + 1));

    Form(n, 1, marked, data);
}

void Form(int n, int depth, bool *marked, vector<char> &data) {
    for (int i = 1; i <= n; i++) {
        if (!marked[i]) {
            marked[i] = true;
            data.push_back(i + '0');

            if (depth == n) {
                for (int j = 0; j < n; j++) { cout << data[j] << ' '; }  // for
                cout << '\n';
            }

            if (depth < n) { Form(n, depth + 1, marked, data); }

            data.pop_back();
            marked[i] = false;
        }
    }  // for
}
