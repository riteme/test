#include "libexp.h"

using namespace libexp;

Token *libexp::tokenize(const char *buffer) {
    Token *head = NULL;
    Token *last = NULL;
    unsigned pos = 0;

    while (buffer[pos] != '\0') {
        Token *current = new Token;
        char c = buffer[pos++];

        if (!isgraph(c)) {
            continue;  // Ignore blank chars
        } else if (isdigit(c)) {
            // Read a variable token
            current->type = TK_LITERAL_VARIABLE;

            unsigned i, j;
            for (i = pos - 1, j = 0; buffer[i] != '\0' && isdigit(buffer[i]);
                 i++, j++) {
                assert(j < LEXEME_SIZE);  // Make sure the length of lexeme not
                                          // exceeded the limit

                current->lexeme[j] = buffer[i];
            }  // for

            pos = i;
        } else if (c == '+') {
            // "add" token
            current->type = TK_OP_ADD;
        } else if (c == '-') {
            // "sub" token
            current->type = TK_OP_SUB;
        } else if (c == '*') {
            // "mul" token
            current->type = TK_OP_MUL;
        } else if (c == '/') {
            // "div" token
            current->type = TK_OP_DIV;
        } else if (c == '(') {
            // Left parenthesis
            current->type = TK_OP_LPAREN;
        } else if (c == ')') {
            // Right parenthesis
            current->type = TK_OP_RPAREN;
        } else {
            // Unknown token
            current->lexeme[0] = c;
        }

        // Append to the end of list
        if (!last) {
            head = last = current;
        } else {
            last->next = current;
            last = current;
        }
    }  // while

    return head;
}

void pop(stack<int> &ops, stack<ExpNode *> &s) {
    int op = ops.top();
    ops.pop();

    switch (op) {
        case TK_OP_ADD: {
            ExpNode *b = s.top();
            s.pop();
            ExpNode *a = s.top();
            s.pop();
            s.push(new ExpNode(EXP_ADD, NULL, a, b));
            // printf("pop +\n");
        } break;

        case TK_OP_SUB: {
            ExpNode *b = s.top();
            s.pop();
            ExpNode *a = s.top();
            s.pop();
            s.push(new ExpNode(EXP_SUB, NULL, a, b));
            // printf("pop -\n");
        } break;

        case TK_OP_MUL: {
            ExpNode *b = s.top();
            s.pop();
            ExpNode *a = s.top();
            s.pop();
            s.push(new ExpNode(EXP_MUL, NULL, a, b));
            // printf("pop *\n");
        } break;

        case TK_OP_DIV: {
            ExpNode *b = s.top();
            s.pop();
            ExpNode *a = s.top();
            s.pop();
            s.push(new ExpNode(EXP_DIV, NULL, a, b));
            // printf("pop /\n");
        } break;
    }  // switch to op
}

ExpNode *libexp::parse(Token *tokens) {
    stack<int> ops;      // Operators
    stack<ExpNode *> s;  // Subtrees
    Token *x = tokens;   // Current token

    while (x) {
        switch (x->type) {
            case TK_LITERAL_VARIABLE: {
                s.push(new ExpNode(EXP_LITERAL, x));
            } break;

            case TK_OP_ADD: {
                while (!ops.empty())
                    pop(ops, s);

                // printf("push +\n");
                ops.push(TK_OP_ADD);
            } break;

            case TK_OP_SUB: {
                while (!ops.empty())
                    pop(ops, s);

                // printf("push -\n");
                ops.push(TK_OP_SUB);
            } break;

            case TK_OP_MUL: {
                while (!ops.empty() &&
                       (ops.top() == TK_OP_MUL || ops.top() == TK_OP_DIV))
                    pop(ops, s);

                // printf("push *\n");
                ops.push(TK_OP_MUL);
            } break;

            case TK_OP_DIV: {
                while (!ops.empty() &&
                       (ops.top() == TK_OP_MUL || ops.top() == TK_OP_DIV))
                    pop(ops, s);

                // printf("push /\n");
                ops.push(TK_OP_DIV);
            } break;

            case TK_OP_LPAREN: {
                // Recursive to parse the tokens in the parenthesis
                s.push(parse(x->next));

                // Go forward to the next one in order to determine the end
                // of
                // pervious procedure
                x = x->next;
            } break;

            case TK_OP_RPAREN: {
                // Skip the processed tokens
                tokens->next = x->next;

                // Tell the while loop to stop
                x = NULL;
            } break;
        }  // switch to x->type

        if (x) {
            x = x->next;
        }
    }  // while

    // printf("final pop\n");
    while (!ops.empty())
        pop(ops, s);

    return s.top();
}

void libexp::evaluate(ExpNode *x) {
    if (!x)
        return;

    evaluate(x->left);
    evaluate(x->right);

    switch (x->type) {
        case EXP_LITERAL: {
            x->value = atof(x->token->lexeme);
            // printf("%.16lf\n", x->value);
        } break;

        case EXP_ADD: {
            x->value = x->left->value + x->right->value;
            // printf("%.16lf + %.16lf\n", x->left->value, x->right->value);
        } break;

        case EXP_SUB: {
            x->value = x->left->value - x->right->value;
            // printf("%.16lf - %.16lf\n", x->left->value, x->right->value);
        } break;

        case EXP_MUL: {
            x->value = x->left->value * x->right->value;
            // printf("%.16lf * %.16lf\n", x->left->value, x->right->value);
        } break;

        case EXP_DIV: {
            x->value = x->left->value / x->right->value;
            // printf("%.16lf / %.16lf\n", x->left->value, x->right->value);
        } break;
    }  // switch to x->type
}
