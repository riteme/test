#include <stdio.h>
int main(void) {
    int a, b, c;
    while (scanf("%d%d", &a, &b) != EOF) {
        // printf("%d/%d=",a,b);
        while (a != 1) {
            c = b / a + 1;
            a = a * c - b;
            b = b * c;
            printf("1/%d + ", c);
            // if(a>1)
            // printf("");
            if ((b % a == 0) || (a == 1)) {
                printf("1/%d", b / a);
                a = 1;
            }
        }
        printf("\n");
    }
    return 0;
}
