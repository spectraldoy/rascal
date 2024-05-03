#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <regex>

enum TokenType {
    NewLine,
    Tab,
    Preface,
    Tcp,
    Services,
    Colon,
    On,
    Identifier,
    Space,
    Unknown,
    EndOfFile,
};

const std::regex IDENTIFIER_RE("[a-zA-Z0-9_\\.\\/\'\"]+");

struct Token {
public:
    Token(TokenType token_type, std::string token_str);
    static Token fromString(std::string token_str);
    TokenType token_type;
    std::string token_str;
};

#endif