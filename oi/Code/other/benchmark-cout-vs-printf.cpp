#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

#define N 100000

void testCout() {
    ios::sync_with_stdio(false);

    for (int i = 0; i < N; i++) {
        cout << "array[" << i << "] = " << i << " * " << i << ";\n";
    }  // for
}

void testPrintf() {
    for (int i = 0; i < N; i++) {
        printf("array[%d] = %d * %d;\n", i, i, i);
    }  // for
}

int main(int argc, char *argv[]) {
    if (argc < 2) { return -1; }

    if (strcmp(argv[1], "cout") == 0) {
        testCout();
    } else if (strcmp(argv[1], "printf") == 0) { testPrintf(); }

    return 0;
}  // function main
