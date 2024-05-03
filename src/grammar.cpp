#include "grammar.h"

Grammar::Grammar(std::vector<Token> parsed_program)
 : parsed_program(parsed_program), token_idx(0)
{}

bool Grammar::check() {
    this->token_idx = 0;
    return G();
}

Token Grammar::currentToken() const {
    return parsed_program[token_idx];
}

bool Grammar::consumeToken() {
    // Last token should be EOF
    if (token_idx < parsed_program.size() - 1) {
        token_idx += 1;
        return true;
    } else {
        return currentToken().token_type == TokenType::EndOfFile;
    }
}

bool Grammar::match(TokenType expected) {
    if (currentToken().token_type == expected) {
        return consumeToken();
    } else {
        return false;
    }
}

bool Grammar::G() {
    switch (currentToken().token_type) {
        // G -> R B | B
        case Preface:
            return R() && B() && match(EndOfFile);
        case Tcp:
        case Services:
            return B() && match(EndOfFile);
        case EndOfFile:
            return true;
        default:
            return false;
    }
}

bool Grammar::B() {
    switch (currentToken().token_type) {
        case Tcp:
            return T() && B();
        case Services:
            return S() && B();
        case EndOfFile:
            return true;
        default:
            return false;
    }
}

bool Grammar::R() {
    return match(Preface) && match(Colon) && match(NewLine) && Q() && match(NewLine);
}

bool Grammar::T() {
    return match(Tcp) && match(Colon) && match(NewLine) && Q() && match(NewLine);
}

bool Grammar::S() {
    return match(Services) && match(Colon) && match(NewLine) && L() && match(NewLine);
}

bool Grammar::Q() {
    switch (this->currentToken().token_type) {
        case Tab:
            return match(Tab) && match(Identifier) && I() && match(NewLine) && Q();
        case NewLine:
            return true;
        default:
            return false;
    }
}

bool Grammar::L() {
    switch (this->currentToken().token_type) {
        case Tab:
            return match(Tab) && match(Identifier) && match(Space) && J() && match(On) && match(Space) && match(Identifier) && match(NewLine) && L();
        case NewLine:
            return true;
        default:
            return false;
    }
}

bool Grammar::I() {
    switch (this->currentToken().token_type) {
        case Space:
            return match(Space) && match(Identifier) && I();
        case NewLine:
            return true;
        default:
            return false;
    }
}

bool Grammar::J() {
    switch (this->currentToken().token_type) {
        case Identifier:
            return match(Identifier) && match(Space) && J();
        case On:
            return true;
        default:
            return false;
    }
}

