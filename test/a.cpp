#include <typeinfo>
#include <cstdio>

static char str[] = "abcdefg";

int main() {
    printf("str: %s\n", typeid(str).name());
    printf("str + 0: %s\n", typeid(str + 0).name());
    printf("&str: %s\n", typeid(&str).name());
    printf("%s\n", str);
    return 0;
}
