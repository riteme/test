#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int size;
vector<int> weight;
vector<int> values;

void f2(int size, int n, vector<vector<int>> &table) {
    if (n == 0) {
        if (weight[n] <= size && table[n][size] == 0) {
            table[n][size] = values[n];
        }
    } else {
        f2(size, n - 1, table);
        f2(size - weight[n], n - 1, table);

        if (weight[n] <= size && table[n][size] == 0) {
            table[n][size] = std::max(
                table[n - 1][size], table[n - 1][size - weight[n]] + values[n]);
        }
    }
}

// Have problem...
void f(int size, int n, vector<vector<int>> &table) {
    for (int i = 0; i <= n; i++) {
        for (int j = 1; j <= size; j++) {
            if (weight[i] <= j) {
                if (i == 0) { table[i][j] = values[i]; } else {
                    table[i][j] =
                        std::max(table[i - 1][j],
                                 table[i - 1][j - weight[i]] + values[i]);
                }
            } else if (i != 0) { table[i][j] = table[i - 1][j]; }
        }
    }
}

int f() {
    vector<vector<int>> table;

    table.resize(weight.size());
    for (auto &e : table) { e.resize(size + 1); }

    for (auto &line : table) {
        for (auto &i : line) { i = 0; }
    }

    f(size, weight.size() - 1, table);

    // int max = 0;
    for (auto &line : table) {
        for (auto i : line) {
            // if (i > max) max = i;
            cout << i << ", ";
        }
        cout << '\n';
    }

    return table[weight.size() - 1][size];
}

int main() {
    ios::sync_with_stdio(false);

    int n;

    cout << "Enter the number of items: ";
    cin >> n;

    cout << "Enter the size of bag: ";
    cin >> size;

    cout << "Enter each item: weight, value" << endl;
    weight.resize(n);
    values.resize(n);
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ": ";
        cin >> weight[i] >> values[i];
    }

    int result = f();
    cout << result << endl;

    return 0;
}
