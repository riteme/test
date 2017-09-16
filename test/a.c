inline int func(int n) __attribute__((always_inline));
int func(int n) {
    return n + 5;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", func(n));
    return 0;
}
