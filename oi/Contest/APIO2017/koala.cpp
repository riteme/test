#include "koala.h"

#include <cstring>

#include <algorithm>

using namespace std;

static int B[100], R[100], a[100];

int minValue(int N, int W) {
    B[0] = 1;
    playRound(B, R);

    for (int i = 0; i < N; i++) {
        if (B[i] >= R[i])
            return i;
    }
}

int maxValue(int N, int W) {
    return 0;
}

int greaterValue(int N, int W) {
    // TODO: Implement Subtask 3 solution here.
    // You may leave this function unmodified if you are not attempting this
    // subtask.
    return 0;
}

void allValues(int N, int W, int *P) {
    for (int i = 0; i < N; i++) {
        a[i] = i;
    }

    if (W == 2*N) {
        stable_sort(a, a + N, [W](const int a, const int b) {
            memset(B, 0, sizeof(B));
            B[a] = B[b] = W / 2;
            playRound(B, R);

            return R[b] > B[b];
        });
    } else {
        // TODO: Implement Subtask 5 solution here.
        // You may leave this block unmodified if you are not attempting this
        // subtask.
    }

    for (int i = 1; i <= N; i++) {
        P[a[i - 1]] = i;
    }
}
