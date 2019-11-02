#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *__real_malloc(size_t);

void *__wrap_malloc(size_t n) {
    void *r = __real_malloc(n);
    printf("%x\n", (unsigned) r);
    return r;
}