#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "result.h"
#include <vector>
#include <string>

class Lexer {
public:
    Lexer(std::string program);
    Result tokenize();
    std::vector<Token> getParsedProgram() const;

private:
    Result pushCurrentToken(size_t line_number);

    std::string program;
    std::string current_token_str;
    std::vector<Token> parsed_program;
};

#endif
