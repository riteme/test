#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <stack>
#include <sstream>
#include <fstream>

using std::stack;
using std::stringstream;
using std::ofstream;

typedef long long longint;

#define BUFFER_MAXSIZE 2048
#define LEXEME_SIZE 4
#define MOD 1000000007

enum Tokens {
    TK_UNKNOWN = 0,

    TK_OP_BEGIN = 1,
    TK_OP_NOT = 2,
    TK_OP_AND = 3,
    TK_OP_OR = 4,
    TK_OP_XOR = 5,
    TK_OP_LPAREN = 6,
    TK_OP_RPAREN = 7,
    TK_OP_END = 8,

    TK_LITERAL_BEGIN = 100,
    TK_LITERAL_VARIABLE = 101,
    TK_LITERAL_END = 102
};  // enum Tk

struct Token {
    Token() : type(TK_UNKNOWN), next(NULL) {
        memset(lexeme, 0, sizeof(lexeme));
    }

    Tokens type;
    char lexeme[LEXEME_SIZE];

    Token *next;
};  // struct Token

Token *tokenize(const char *buffer);

enum Expression {
    EXP_UNKNOWN = 0,

    EXP_LITERAL = 1,
    EXP_NOT = 2,
    EXP_AND = 3,
    EXP_OR = 4,
    EXP_XOR = 5
};  // enum Expression

struct ExpNode {
    ExpNode(Expression _type, Token *_token, ExpNode *_left = NULL,
            ExpNode *_right = NULL)
            : type(_type), token(_token), left(_left), right(_right) {}

    Expression type;
    Token *token;
    ExpNode *left, *right;
    longint true_count, false_count;
};  // struct ExpNode

ExpNode *parse(Token *tokens);

void dp(ExpNode *x);

void write_to(const ExpNode *tree, stringstream &buffer);
void show(const ExpNode *tree);

int main() {
    // freopen("expression.in", "r", stdin);
    // freopen("expression.out", "w", stdout);
    static char buffer[BUFFER_MAXSIZE];

    while (scanf("%s", buffer) != EOF) {
        Token *tokens = tokenize(buffer);
        ExpNode *tree = parse(tokens);
        // show(tree);
        dp(tree);
        printf("%lld\n", tree->true_count);
    }  // while

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main

void dp(ExpNode *x) {
    if (!x)
        return;

    dp(x->left);
    dp(x->right);

    switch (x->type) {
        case EXP_LITERAL: x->true_count = x->false_count = 1; break;
        case EXP_NOT:
            x->true_count = x->left->false_count;
            x->false_count = x->left->true_count;
            break;
        case EXP_AND:
            x->true_count = x->left->true_count * x->right->true_count;
            x->false_count = x->left->true_count * x->right->false_count +
                             x->left->false_count * x->right->true_count +
                             x->left->false_count * x->right->false_count;
            break;
        case EXP_OR:
            x->true_count = x->left->true_count * x->right->false_count +
                            x->left->false_count * x->right->true_count +
                            x->left->true_count * x->right->true_count;
            x->false_count = x->left->false_count * x->right->false_count;
            break;
        case EXP_XOR:
            x->true_count = x->left->true_count * x->right->true_count +
                            x->left->false_count * x->right->false_count;
            x->false_count = x->left->true_count * x->right->false_count +
                             x->left->false_count * x->right->true_count;
            break;
    }  // switch to x->type

    x->true_count %= MOD;
    x->false_count %= MOD;
}

Token *tokenize(const char *buffer) {
    Token *head = NULL;
    Token *last = NULL;
    unsigned pos = 0;

    while (buffer[pos] != '\0') {
        Token *current = new Token;
        char c = buffer[pos++];

        if (!isgraph(c)) {
            continue;  // Ignore blank chars
        } else if (isalpha(c)) {
            // Read a variable token
            current->type = TK_LITERAL_VARIABLE;

            unsigned i, j;
            for (i = pos - 1, j = 0; buffer[i] != '\0' && isalpha(buffer[i]);
                 i++, j++) {
                assert(j < LEXEME_SIZE);  // Make sure the length of lexeme not
                                          // exceeded the limit

                current->lexeme[j] = buffer[i];
            }  // for

            pos = i;
        } else if (c == '!') {
            // "not" token
            current->type = TK_OP_NOT;
        } else if (c == '&') {
            // "and" token
            current->type = TK_OP_AND;
        } else if (c == '|') {
            // "or" token
            current->type = TK_OP_OR;
        } else if (c == '^') {
            // "xor" token
            current->type = TK_OP_XOR;
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

ExpNode *parse(Token *tokens) {
    stack<int> ops;        // Operators
    stack<ExpNode *> s;    // Subtrees
    Token *x = tokens;     // Current token
    size_t last_size = 0;  // History value of the number of subtrees

    while (x) {
        switch (x->type) {
            case TK_LITERAL_VARIABLE: {
                s.push(new ExpNode(EXP_LITERAL, x));
            } break;

            case TK_OP_NOT: {
                ops.push(TK_OP_NOT);
            } break;

            case TK_OP_AND: {
                ops.push(TK_OP_AND);
            } break;

            case TK_OP_OR: {
                ops.push(TK_OP_OR);
            } break;

            case TK_OP_XOR: {
                ops.push(TK_OP_XOR);
            } break;

            case TK_OP_LPAREN: {
                // Recursive to parse the tokens in the parenthesis
                s.push(parse(x->next));

                // Go forward to the next one in order to determine the end of
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

        // If new subtrees added, it's time to combine them with the operators
        if (last_size < s.size()) {
            // Indicate that the process needs to be stopped
            bool exited = false;

            while (!ops.empty() && !exited) {
                int op = ops.top();

                switch (op) {
                    case TK_OP_NOT: {
                        if (s.size() < 1)
                            exited = true;
                        else {
                            ExpNode *a = s.top();
                            s.pop();
                            s.push(new ExpNode(EXP_NOT, x, a));
                        }
                    } break;

                    case TK_OP_AND: {
                        if (s.size() < 2)
                            exited = true;
                        else {
                            ExpNode *b = s.top();
                            s.pop();
                            ExpNode *a = s.top();
                            s.pop();
                            s.push(new ExpNode(EXP_AND, x, a, b));
                        }
                    } break;

                    case TK_OP_OR: {
                        if (s.size() < 2)
                            exited = true;
                        else {
                            ExpNode *b = s.top();
                            s.pop();
                            ExpNode *a = s.top();
                            s.pop();
                            s.push(new ExpNode(EXP_OR, x, a, b));
                        }
                    } break;

                    case TK_OP_XOR: {
                        if (s.size() < 2)
                            exited = true;
                        else {
                            ExpNode *b = s.top();
                            s.pop();
                            ExpNode *a = s.top();
                            s.pop();
                            s.push(new ExpNode(EXP_XOR, x, a, b));
                        }
                    } break;
                }  // switch to op

                // If no "exited" flag is set, the operator has been used
                if (!exited) {
                    ops.pop();
                }
            }  // while

            // Update the history number
            last_size = s.size();
        }

        if (x) {
            x = x->next;
        }
    }  // while

    return s.top();
}

void write_to(const ExpNode *x, stringstream &buffer) {
    if (!x)
        return;

    write_to(x->left, buffer);
    write_to(x->right, buffer);

    long id = reinterpret_cast<long>(x);
    buffer << id << "[";
    switch (x->type) {
        case EXP_LITERAL:
            buffer << "label=\"" << x->token->lexeme << "\"";
            break;
        case EXP_NOT: buffer << "label=\"!\""; break;
        case EXP_AND: buffer << "label=\"&\""; break;
        case EXP_OR: buffer << "label=\"|\""; break;
        case EXP_XOR: buffer << "label=\"^\""; break;
    }  // switch to x->type
    buffer << "];\n";

    if (x->left) {
        buffer << id << ":sw->" << reinterpret_cast<long>(x->left) << ";\n";
    }

    if (x->right) {
        buffer << id << ":se->" << reinterpret_cast<long>(x->right) << ";\n";
    }
}

void show(const ExpNode *tree) {
    stringstream buffer;
    buffer << "digraph {\nnode[shape=circle];\n";
    write_to(tree, buffer);
    buffer << "}";

    // printf("%s\n", buffer.str().c_str());
    ofstream file("/tmp/interpreter.tmp.dot");
    file << buffer.str();
    file.close();

    system("showdot /tmp/interpreter.tmp.dot");
}
