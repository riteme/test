#include "network.h"

static int n;

void initialize(int n, int q) { ::n = n; }
void add_connection(int u, int v, int t) {}
int query() { return n; }
void finalize() {}
