// #define NDEBUG

#include <cstdio>

#include "interface.h"

// 结果输出的默认设置：
#define TRUE_OUTPUT "YES"
#define FALSE_OUTPUT "NO"

// 推荐设置：
// #define TRUE_OUTPUT "HJWJBSR"
// #define FALSE_OUTPUT "HJWJSSB"

int main() {
    // 如果需要打开文件输入输出，请注释下面两行：
    // freopen("airstrike.in", "r", stdin);
    // freopen("airstrike.out", "w", stdout);

    size_t n;
    int id;
    scanf("%zu%d", &n, &id);

    double *ax = new double[n];
    double *ay = new double[n];
    for (size_t i = 0; i < n; i++) {
        scanf("%lf%lf", ax + i, ay + i);
    }  // for

    initialize(ax, ay, n, id);

    double x, y;
    while (scanf("%lf%lf", &x, &y) != EOF) {
        puts(query(x, y) ? TRUE_OUTPUT : FALSE_OUTPUT);
    }  // while

    finalize();
    delete[] ax;
    delete[] ay;

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
