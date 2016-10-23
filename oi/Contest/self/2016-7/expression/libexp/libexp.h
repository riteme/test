#ifndef EXP_H_
#define EXP_H_

#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <stack>

using std::stack;

#define LEXEME_SIZE 64

namespace libexp {

enum Tokens {
    TK_UNKNOWN = 0,

    TK_OP_BEGIN = 1,
    TK_OP_ADD = 2,
    TK_OP_SUB = 3,
    TK_OP_MUL = 4,
    TK_OP_DIV = 5,
    TK_OP_LPAREN = 6,
    TK_OP_RPAREN = 7,
    TK_OP_END = 8,

    TK_LITERAL_BEGIN = 100,
    TK_LITERAL_VARIABLE = 101,
    TK_LITERAL_END = 102
};  // enum Tokens

enum Expression {
    EXP_UNKNOWN = 0,

    EXP_LITERAL = 1,
    EXP_ADD = 2,
    EXP_SUB = 3,
    EXP_MUL = 4,
    EXP_DIV = 5
};  // enum Expression

struct Token {
    Token() : type(TK_UNKNOWN), next(NULL) {
        memset(lexeme, 0, sizeof(lexeme));
    }

    Tokens type;
    char lexeme[LEXEME_SIZE];

    Token *next;
};  // struct Token

struct ExpNode {
    ExpNode(Expression _type, Token *_token, ExpNode *_left = NULL,
            ExpNode *_right = NULL)
            : type(_type), token(_token), left(_left), right(_right) {}

    Expression type;
    Token *token;
    ExpNode *left, *right;
    double value;
};  // struct ExpNode

Token *tokenize(const char *buffer);
ExpNode *parse(Token *tokens);
void evaluate(ExpNode *x);

}  // namespace libexp

#endif  // EXP_H_
