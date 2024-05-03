#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <vector>
#include "token.h"

/**
 * @brief Here is the grammar for rascal: G is the starting symbol
 * G := R B | B
 * B := T B | S B | eps
 * R := preface: Q \n
 * T := tcp: Q \n
 * S := services: L \n
 * Q := \t I <id> Q \n | eps
 * I := <id> <space> I | eps
 * L := \t I on <space> <id>\n L | eps
 */
class Grammar {
public:
    Grammar(std::vector<Token> parsed_program);
    bool check();

private:
    bool consumeToken();
    bool match(TokenType expected);

    bool G();
    bool B();
    bool R();
    bool T();
    bool S();
    bool Q();
    bool I();
    bool L();

    std::vector<Token> parsed_program;
    size_t current_token_idx;
    size_t next_token_idx;
    Token current_token;
};

#endif