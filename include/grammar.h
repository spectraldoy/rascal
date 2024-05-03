#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <vector>
#include "token.h"
#include "result.h"

/**
 * @brief Here is the grammar for rascal: G is the starting symbol
 * Goal := PrefaceSection Body | Body
 * Body := TcpSection Body | ServicesSection Body | eps
 * PrefaceSection := preface:\n U N
 * TcpSection := tcp:\n Q N
 * ServicesSection := services:\n L N
 * U := \t A \n U | eps
 * Q := \t <id> I\n Q | eps
 * L := \t <id> <space> J on <space> <id>\n L | eps
 * A := <anything> A | eps
 * I := <space> <id> I | eps
 * J := <id> <space> J | eps
 * N := \n N | eps
 */
class Grammar {
public:
    Grammar(std::vector<Token> parsed_program);
    Result check();

private:
    Token currentToken() const;
    Result consumeToken();
    Result match(TokenType expected);

    Result Goal();
    Result Body();
    Result PrefaceSection();
    Result TcpSection();
    Result ServicesSection();
    Result U();
    Result Q();
    Result L();
    Result A();
    Result I();
    Result J();
    Result N();

    std::string dbgLineNumber() const;

    std::vector<Token> parsed_program;
    size_t token_idx;
    size_t line_number;
};

#endif