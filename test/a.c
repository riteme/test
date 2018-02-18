int main() {
    register unsigned long long a;
    printf("%d\n", sizeof(a));
    int n;
    scanf("%d", &n);

    while (n--) {
        a *= 123413221ULL;
        a /= 21390ULL;
        a /= 119ULL;
    }

    printf("%lf\n", a);

    return 0;
}
