#include "lexer.h"

Lexer::Lexer(std::string program) : program(program), current_token_str(""), parsed_program() {}

Result<void*, std::string> Lexer::tokenize() {
    this->parsed_program.clear();
    this->current_token_str = "";
    size_t line_number = 1;

    for (size_t i = 0; i < this->program.size(); i++) {
        char current_char = this->program.at(i);

        switch (current_char) {
            case '\n':
                line_number += 1;
            case '\t':
            case ' ':
            case ':': {
                // push the currently collected token
                Result<void*, std::string> res = this->pushCurrentToken(line_number);
                if (res.isError()) {
                    return res;
                }
                std::string next_token_str = "" + current_char;
                Token next_token = Token::fromString(next_token_str);
                this->parsed_program.push_back(next_token);
                break;
            }
            // Ignore comment lines
            case '#': {
                // Push the current token
                Result<void*, std::string> res = this->pushCurrentToken(line_number);
                if (res.isError()) {
                    return res;
                }

                while (i < program.size() && program.at(i) != '\n') {
                    i++;
                }
                // If we actually found a newline, ignore, it's part of the comment
                if (program.at(i) == '\n') {
                    i += 1;
                    line_number += 1;
                }
                break;
            }
            default:
                this->current_token_str.push_back(current_char);
        }
    }

    // This syntax sucks
    return Ok<void*, std::string>(nullptr);
}

std::vector<Token> Lexer::getParsedProgram() const {
    return this->parsed_program;
}

Result<void*, std::string> Lexer::pushCurrentToken(size_t line_number) {
    if (this->current_token_str.size() > 0) {
        Token tok = Token::fromString(this->current_token_str);
        if (tok.token_type == TokenType::Unknown) {
            return Error<void*, std::string>(
                "Cannot parse token \"" + current_token_str + "\" on line " + std::to_string(line_number)
            );
        }

        this->parsed_program.push_back(tok);
        // reset current token_str
        this->current_token_str = "";
    }

    return Ok<void*, std::string>(nullptr);
}
