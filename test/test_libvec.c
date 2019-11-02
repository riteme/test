#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

int main() {
    int (*dot)(int*, int*, int);
    int (*sum)(int*, int);

    void *handle = dlopen("./vec.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return EXIT_FAILURE;
    }

    dot = dlsym(handle, "dot");
    if (!dot) {
        fprintf(stderr, "%s\n", dlerror());
        return EXIT_FAILURE;
    }

    sum = dlsym(handle, "sum");
    if (!sum) {
        fprintf(stderr, "%s\n", dlerror());
        return EXIT_FAILURE;
    }

    int a[] = {1, 2, 3};
    int b[] = {6, 5, 4};
    printf("%d\n%d\n%d\n", dot(a, b, 3), sum(a, 3), sum(b, 3));

    if (dlclose(handle)) {
        fprintf(stderr, "%s\n", dlerror());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}