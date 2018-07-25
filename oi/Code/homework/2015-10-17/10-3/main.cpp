// #include <cstring>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int Recursive(int minN, int maxN, int bound, const vector<int> &w);
void RecursiveImpl(int minN, int maxN, int bound, const vector<int> &w,
                   int current, int &max, bool *marked, int depth);

int main(/*int argc, char *argv[]*/) {
    ios::sync_with_stdio(false);

    int n;
    vector<int> w;

    cin >> n;

    int sum = 0;
    w.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
        sum += w[i];
    }  // for

    int G = sum / 2;
    int minBound = n / 2;
    int maxBound = minBound + (n % 2);

    int maxW = Recursive(minBound, maxBound, G, w);

    cout << maxW << ' ' << sum - maxW << endl;

    return 0;
}  // function main

int Recursive(int minN, int maxN, int bound, const vector<int> &w) {
    int result = 0;
    bool marked[w.size()];

    memset(marked, false, sizeof(bool) * w.size());

    RecursiveImpl(minN, maxN, bound, w, 0, result, marked, 1);

    return result;
}

void RecursiveImpl(int minN, int maxN, int bound, const vector<int> &w,
                   int current, int &max, bool *marked, int depth) {
    for (int i = 0; i < w.size(); i++) {
        if (!marked[i]) {
            marked[i] = true;
            current += w[i];

            if (minN <= depth and abs(bound - current) < abs(bound - max)) {
                max = current;
            }

            if (depth <= maxN) {
                RecursiveImpl(minN, maxN, bound, w, current, max, marked,
                              depth + 1);
            }

            current -= w[i];
            marked[i] = false;
        }
    }  // for
}
