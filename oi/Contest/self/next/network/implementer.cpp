#include <cstdio>

#include "network.h"

int main() {
    int n, q;
    scanf("%d%d", &n, &q);

    initialize(n, q);

    for (int i = 0; i < q; i++) {
        int u, v, t;
        scanf("%d%d%d", &u, &v, &t);

        add_connection(u, v, t);
        int answer = query();
        printf("%d\n", answer);
    }

    finalize();

    return 0;
}
