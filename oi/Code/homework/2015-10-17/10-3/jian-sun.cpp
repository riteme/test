#include <iostream>
#include <algorithm>
using namespace std;
int k[100];
struct ms {
    int Sum, People;
};
int n;
ms A, B;
int main() {
    cin >> n;
    for (int a = 0; a <= n - 1; a++) cin >> k[a];
    sort(k, k + n);
    A.Sum = 0;
    A.People = 0;
    B.People = 0;
    B.Sum = 0;

    for (int a = n - 1; a >= 0; a--) {
        if (A.People >= n / 2 + 1) {
            for (int b = a; b >= 0; b--) {
                B.Sum += k[a];
                B.People++;
            }
            break;
        }
        if (B.People >= n / 2 + 1) {
            for (int b = a; b >= 0; b--) {
                A.Sum += k[a];
                A.People++;
            }
        }
        if (A.Sum == B.Sum) {
            if (A.People <= B.People) {
                A.Sum = A.Sum + k[a];
                A.People++;
            } else {
                B.People++;
                B.Sum = B.Sum + k[a];
            }
        } else {
            if (A.Sum < B.Sum) {
                A.Sum += k[a];
                A.People++;
            } else {
                B.Sum += k[a];
                B.People++;
            }
        }
    }
    int min, max;
    if (A.Sum <= B.Sum) {
        min = A.Sum;
        max = B.Sum;
    } else {
        min = B.Sum;
        max = A.Sum;
    }
    cout << min << " " << max;
}
