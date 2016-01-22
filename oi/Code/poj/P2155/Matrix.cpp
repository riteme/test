#include <cstdio>

using namespace std;

#define NMAX 1000

static int testcaseCount;
static int n, t;
static bool matrix[NMAX + 10][NMAX + 10];

inline char get_command() {
    char c = getchar();

    while (c != 'Q' and c != 'C') {
        c = getchar();
    }  // while

    return c;
}

inline bool query(int x, int y) {
    bool result = 0;

    for (int i = y; i != 0 and i <= n; i += i & (-i)) {
        if (matrix[x][i]) {
            result = !result;
        }
    }  // for

    for (int i = x; i != 0 and i <= n; i += i & (-i)) {
        if (matrix[i][n]) {
            result = !result;
        }
    }  // for

    return result;
}

inline void insert(int x, int y) {
    for (int i = x; i; i -= i & (-i)) {
        for (int j = y; j; j -= j & (-j)) {
            matrix[i][j] = !matrix[i][j];
        }  // for
    }      // for
}

void print_matrix() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", matrix[i][j]);
        }  // for
        printf("\n");
    }  // for
}

void initialize() {
    scanf("%d %d", &n, &t);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            matrix[i][j] = 0;
        }  // for
    }      // for
}

int main() {
    scanf("%d", &testcaseCount);

    while (testcaseCount > 0) {
        initialize();

        while (t > 0) {
            char command = get_command();

            int x1, y1, x2, y2;
            switch (command) {
                case 'Q':
                    scanf("%d %d", &x1, &y1);
                    printf("%d\n", query(x1, y1));
                    break;
                case 'C':
                    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                    insert(x2, y2);
                    print_matrix();
                    insert(x1 - 1, y2);
                    print_matrix();
                    insert(x2, y1 - 1);
                    print_matrix();
                    insert(x1 - 1, y1 - 1);
                    print_matrix();
                    break;
            }  // switch to command

            t--;
        }  // while

        printf("\n");
        testcaseCount--;
    }  // while

    return 0;
}  // function main
