#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    int x1, x2, x3;
    scanf("%d%d%d", &x1, &x2, &x3);

    int answer = 1000000000;
    for (int mid = 1; mid <= 100; mid++) {
        int dist = abs(x1 - mid) + abs(x2 - mid) + abs(x3 - mid);
        answer = min(answer, dist);
    }  // for
    printf("%d\n", answer);

    return 0;
}  // function main
