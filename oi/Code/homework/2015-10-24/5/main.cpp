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

    // DP comes first
    // Greedy?
    double mark = 0.0;
    double dollar = 100.0;
    for (int i = 1; i <= n; i++) {
        mark = std::max(mark, dollar * (data[i - 1] / 100.0));
        dollar = std::max(dollar, mark * (100.0 / data[i - 1]));
    }  // for

    printf("%.2f", dollar);

    return 0;
}  // function main
