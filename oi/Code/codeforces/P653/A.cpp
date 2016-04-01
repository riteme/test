#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

static int n;
static int num[100];
static int size;
static int a[100];

static void initialize() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", num + i);
    }  // for

    sort(num, num + n);

    int last = -1;
    size = 0;
    for (int i = 0; i < n; i++) {
        if (num[i] != last) {
            a[size++] = num[i];
            last = num[i];
        }
    }  // for
}

int main() {
    initialize();

    bool flag = false;

    for (int i = 0; i < n - 1 && !flag; i++) {
        int p1 = a[i], p2 = a[i + 1], p3 = a[i + 2];

        if ((p1 != p2 && p2 != p3 && p3 != p1) && (p1 + 2 == p3))
            flag = true;
    }  // for

    if (flag)
        printf("YES");
    else
        printf("NO");

    return 0;
}  // function main
