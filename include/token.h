#ifndef TOKEN_H
#define TOKEN_H

#include <string>

constexpr enum TokenType {
    NewLine,
    Tab,
    Preface,
    Tcp,
    Services,
    On,
    PathString,
    Identifier,
    Space,
    Comment,
    Unknown,
    EndOfFile,
};

struct Token {
public:
    Token(TokenType token_type, std::string token_str);
    TokenType token_type;
    std::string token_str;
};

#endif