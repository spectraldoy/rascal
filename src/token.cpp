#include "token.h"

Token::Token(TokenType token_type, std::string token_str)
 : token_type(token_type), token_str(token_str)
{}

Token Token::fromString(std::string token_str) {
    TokenType token_type = TokenType::Unknown;

    if (token_str == "\n") {
        token_type = TokenType::NewLine;
    } else if (token_str == "\t") {
        token_type = TokenType::Tab;
    } else if (token_str == "preface") {
        token_type = TokenType::Preface;
    } else if (token_str == "tcp") {
        token_type = TokenType::Tcp;
    } else if (token_str == "services") {
        token_type = TokenType::Services;
    } else if (token_str == ":") {
        token_type = TokenType::Colon;
    } else if (token_str == "on") {
        token_type = TokenType::On;
    } else if (std::regex_match(token_str, IDENTIFIER_RE)) {
        token_type = TokenType::Identifier;
    } else if (token_str == " ") {
        token_type = TokenType::Space;
    }
    return Token(token_type, token_str);
}