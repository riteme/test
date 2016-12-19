#include <cstdio>
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(0));
    printf("%d\n", rand()%2);

    for (int i = 0; i < 200000000; i++) {
	double a = 2314.32142*(4213213.321/32186.321);
    }

    return 0;
}
