#include "grammar.h"

Grammar::Grammar(std::vector<Token> parsed_program)
 : parsed_program(parsed_program), token_idx(0), line_number(1)
{}

Result Grammar::check() {
    this->token_idx = 0;
    this->line_number = 1;
    return Goal();
}

Token Grammar::currentToken() const {
    return parsed_program[token_idx];
}

Result Grammar::consumeToken() {
    // Last token should be EOF
    if (token_idx < parsed_program.size() - 1) {
        if (currentToken().token_type == NewLine) {
            line_number += 1;
        }
        token_idx += 1;
        return Result::Ok();
    } else {
        if (currentToken().token_type == TokenType::EndOfFile) {
            return Result::Ok();
        } else {
            return Result::Error("Last token is not EOF, but is " + currentToken().toString());
        }
    }
}

Result Grammar::match(TokenType expected) {
    if (currentToken().token_type == expected) {
        return consumeToken();
    } else {
        return Result::Error(
            "Expected " + tokenTypeToString(expected) + " but got "
            + currentToken().toString() + dbgLineNumber()
        );
    }
}

Result Grammar::Goal() {
    switch (currentToken().token_type) {
        case Preface:
            return PrefaceSection() && Body() && match(EndOfFile);
        case Tcp:
        case Services:
            return Body() && match(EndOfFile);
        case EndOfFile:
            return Result::Ok();
        default:
            return Result::Error(
                currentToken().toString() + dbgLineNumber() + " does not match Goal"
            );
    }
}

Result Grammar::Body() {
    switch (currentToken().token_type) {
        case Tcp:
            return TcpSection() && Body();
        case Services:
            return ServicesSection() && Body();
        case EndOfFile:
            return Result::Ok();
        default:
            return Result::Error(
                currentToken().toString() + dbgLineNumber() + " does not match Body"
            );;
    }
}

Result Grammar::PrefaceSection() {
    return match(Preface) && match(Colon) && match(NewLine) && U() && N();
}

Result Grammar::TcpSection() {
    return match(Tcp) && match(Colon) && match(NewLine) && Q() && N();
}

Result Grammar::ServicesSection() {
    return match(Services) && match(Colon) && match(NewLine) && L() && N();
}

Result Grammar::U() {
    // Within preface, we match everything
    switch (this->currentToken().token_type) {
        case Tab:
            return match(Tab) && A() && match(NewLine) && U();
        case NewLine:
        case Services:
        case Tcp:
        case EndOfFile:
            return Result::Ok();
        default:
            return Result::Error(
                currentToken().toString() + dbgLineNumber() + " does not match U"
            );
    }
}

Result Grammar::Q() {
    switch (this->currentToken().token_type) {
        case Tab:
            return match(Tab) && match(Identifier) && I() && match(NewLine) && Q();
        case NewLine:
        case Services:
        case Tcp:
        case EndOfFile:
            return Result::Ok();
        default:
            return Result::Error(
                currentToken().toString() + dbgLineNumber() + " does not match Q"
            );
    }
}

Result Grammar::L() {
    switch (this->currentToken().token_type) {
        case Tab:
            return match(Tab) && match(Identifier) && match(Space) && J() && match(On) && match(Space) && match(Identifier) && match(NewLine) && L();
        case NewLine:
        case Tcp:
        case Services:
        case EndOfFile:
            return Result::Ok();
        default:
            return Result::Error(
                currentToken().toString() + dbgLineNumber() + " does not match L"
            );
    }
}

Result Grammar::A() {
    // Match anything until a newline
    switch (this->currentToken().token_type) {
        case NewLine:
            return Result::Ok();
        case Unknown:
        case EndOfFile:
            return Result::Error(
                "Invalid token " + currentToken().toString() + dbgLineNumber() +
                " while matching A"
            );
        default:
            return match(this->currentToken().token_type) && A();
    }
}

Result Grammar::I() {
    switch (this->currentToken().token_type) {
        case Space:
            return match(Space) && match(Identifier) && I();
        case NewLine:
            return Result::Ok();
        default:
            return Result::Error(
                currentToken().toString() + dbgLineNumber() + " does not match I"
            );
    }
}

Result Grammar::J() {
    switch (this->currentToken().token_type) {
        case Identifier:
            return match(Identifier) && match(Space) && J();
        case On:
            return Result::Ok();
        default:
            return Result::Error(
                currentToken().toString() + dbgLineNumber() + " does not match J"
            );
    }
}

Result Grammar::N() {
    switch (this->currentToken().token_type) {
        case NewLine:
            return match(NewLine) && N();
        case Tab:
        case Services:
        case Tcp:
        case EndOfFile:
            return Result::Ok();
        default:
            return Result::Error(
                currentToken().toString() + dbgLineNumber() + " does not match N"
            );;
    }
}

std::string Grammar::dbgLineNumber() const {
    return " on line " + std::to_string(line_number);
}