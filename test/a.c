int tmult_ok(long x, long y, long *dst) {
    unsigned char pred;
    *dst = x * y;
    asm("setae %[b]"
        : [b] "=r" (pred)
    );
    return pred;
}

int tmult_ok0(long x, long y, long *dst) {
    int pred;
    *dst = x * y;
    asm("setae %%bl;"
        "movzbl %%bl, %[val]"
        : [val] "=r" (pred)
        :
        : "%bl"
    );
    return pred;
}

int umult_ok(unsigned long x, unsigned long y, unsigned long *dst) {
    unsigned char pred;

    asm("movq %[x], %%rax;"
        "mulq %[y];"
        "movq %%rax, %[p];"
        "setae %[b]"
        : [p] "=m" (*dst), [b] "=r" (pred)
        : [x] "r" (x), [y] "r" (y)
        : "%rax", "%rdx"
    );

    return pred;
}
