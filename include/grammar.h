#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <vector>
#include "token.h"

/**
 * @brief Here is the grammar for rascal: G is the starting symbol
 * G := R B | B
 * B := T B | S B | eps
 * R := preface:\n Q \n
 * T := tcp:\n Q \n
 * S := services:\n L \n
 * Q := \t <id> I\n Q | eps
 * L := \t <id> <space> J on <space> <id>\n L | eps
 * I := <space> <id> I | eps
 * J := <id> <space> J | eps
 */
class Grammar {
public:
    Grammar(std::vector<Token> parsed_program);
    bool check();

private:
    Token currentToken() const;
    bool consumeToken();
    bool match(TokenType expected);

    bool G();
    bool B();
    bool R();
    bool T();
    bool S();
    bool Q();
    bool L();
    bool I();
    bool J();

    std::vector<Token> parsed_program;
    size_t token_idx;
};

#endif