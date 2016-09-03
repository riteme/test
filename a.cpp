#include <cstdio>

int main () {
    int n;
    scanf("%d", &n);

    int array[n];
    for (int i = 0; i < n; i++) {
	array[i] = i;
    }

    int sum = 0;
    for (int i = 0; i < n; i++) {
	sum += array[i];
    }

    printf("%d", sum);

    return 0;
}
