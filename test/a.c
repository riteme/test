int a[] = {1, 2, 3};
int b[100]={1};
int c = 100;

int sum(int i) {
    if (i < 0)
        return 0;
    return a[i] + sum(i - 1);
}
