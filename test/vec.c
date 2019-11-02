int dot(int *a, int *b, int n) {
    int r = 0, i;
    for (i = 0; i < n; i++)
        r += a[i] * b[i];
    return r;
}

int sum(int *a, int n) {
    int r = 0, i;
    for (i = 0; i < n; i++)
        r += a[i];
    return r;
}