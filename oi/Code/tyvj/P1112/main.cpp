#include <iostream>

using namespace std;

int main(/*int argc, char *argv[]*/) {
    int n, k;
    int m = 0;

    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        int tmp;
        int cnt = 0;

        while (true) {
            cin >> tmp;

            if (tmp == i) { continue; }

            if (tmp == 0) {
                if (cnt >= k) { m++; }
                break;
            }

            cnt++;
        }  // while
    }      // for

    cout << m << endl;

    return 0;
}  // function main
