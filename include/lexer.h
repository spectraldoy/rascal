#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include <vector>
#include <string>
#include <iostream>

class Lexer {
public:
    Lexer(std::string program);
    bool tokenize();
    std::vector<Token> getParsedProgram() const;

private:
    bool pushCurrentToken(size_t line_number);

    std::string program;
    std::string current_token_str;
    std::vector<Token> parsed_program;
    bool errored;
};

#endif
