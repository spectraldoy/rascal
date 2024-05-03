#include "grammar.h"

Grammar::Grammar(std::vector<Token> parsed_program)
 : parsed_program(parsed_program), current_token_idx(0), next_token_idx(1), current_token(Token(TokenType::Unknown, ""))
{}

bool Grammar::consumeToken() {
    // Last token should be EOF
    if (this->next_token_idx < this->parsed_program.size() - 1) {
        this->next_token_idx += 1;
        this->current_token_idx += 1;
        return true;
    } else {
        return this->parsed_program[this->next_token_idx].token_type == TokenType::EndOfFile;
    }
}

bool Grammar::match(TokenType expected) {
    
}