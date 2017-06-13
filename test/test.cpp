#include <iostream>
#include <algorithm>

using namespace std;

static int n;

void print(int *a) {
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main() {
    cin >> n;

    int a[n];
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }

    print(a);
    while (next_permutation(a, a + n))
        print(a);

    return 0;
}
