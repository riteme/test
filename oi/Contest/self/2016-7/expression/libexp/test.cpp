#include <cstdio>

#include "libexp.h"

using namespace libexp;

int main() {
    char buffer[65536];
    scanf("%s", buffer);

    Token *tokens = tokenize(buffer);
    ExpNode *expression = parse(tokens);
    evaluate(expression);

    printf("%.16lf\n", expression->value);

    return 0;
}  // function main
