#include "grammar.h"
#include "lexer.h"
#include "gtest/gtest.h"

#include <string>

std::vector<Token> parseProgram(std::string program) {
    Lexer lex(program);
    bool res = lex.tokenize();
    EXPECT_TRUE(res);
    return lex.getParsedProgram();
}

TEST(GrammarTest, SimpleValidFile) {
    std::string program =
        "preface:\n"
        "\tauthor Aditya Gomatam\n"
        "\tproject rascal\n"
        "\tversion 0.0.0\n"
        "\n"
        "services:\n"
        "\tserve ./static on /test_path\n"
        "\techo on /seventy_two\n"
        "\n"
        "tcp:\n"
        "\tport 8080\n"
        "\n";
    std::vector<Token> parsed_program = parseProgram(program);
    Grammar grammar(parsed_program);
    bool res = grammar.check();
    ASSERT_TRUE(res);
}