#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define DOLLAR 0
#define MARK 1

int main(/*int argc, char *argv[]*/) {
    // ios::sync_with_stdio(false);

    int n;
    cin >> n;

    double data[n];
    for (int i = 0; i < n; i++) { cin >> data[i]; }  // for

    double d[n + 1][2];
    d[0][DOLLAR] = 100.0f;
    d[0][MARK] = 0.0f;

    for (int i = 1; i <= n; i++) {
        d[i][MARK] =
            std::max(d[i - 1][MARK], d[i - 1][DOLLAR] * (data[i - 1] / 100.0f));
        d[i][DOLLAR] =
            std::max(d[i - 1][DOLLAR], d[i - 1][MARK] * (100.0f / data[i - 1]));
    }  // for

    printf("%.2f", d[n][DOLLAR]);

    return 0;
}  // function main
