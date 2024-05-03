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
    EndOfFile,
    Unknown,
};

const std::regex IDENTIFIER_RE("[a-zA-Z0-9_\\.\\/\'\"]+");

struct Token {
public:
    Token(TokenType token_type, std::string token_str);
    static Token fromString(std::string token_str);
    std::string toString() const;
    TokenType token_type;
    std::string token_str;
};

std::string tokenTypeToString(TokenType token_type);

#endif