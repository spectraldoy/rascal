#include "lexer.h"
#include "gtest/gtest.h"

TEST(LexerTest, IgnoreComment) {
    std::string program =
        "# this is a comment\n"
        "preface:\n"
        "\tauthor Aditya Gomatam\n"
        "\tname rascal\n"
        "\n";
    Lexer lex(program);
    bool res = lex.tokenize();
    ASSERT_TRUE(res);

    std::vector<TokenType> expected;
    expected.push_back(Preface);
    expected.push_back(Colon);
    expected.push_back(NewLine);
    expected.push_back(Tab);
    expected.push_back(Identifier);
    expected.push_back(Space);
    expected.push_back(Identifier);
    expected.push_back(Space);
    expected.push_back(Identifier);
    expected.push_back(NewLine);
    expected.push_back(Tab);
    expected.push_back(Identifier);
    expected.push_back(Space);
    expected.push_back(Identifier);
    expected.push_back(NewLine);
    expected.push_back(NewLine);
    expected.push_back(EndOfFile);

    std::vector<Token> parsed_program = lex.getParsedProgram();
    EXPECT_EQ(parsed_program.size(), expected.size());
    for (int i = 0; i < parsed_program.size(); i++) {
        EXPECT_EQ(parsed_program[i].token_type, expected[i]);
    }
}

TEST(LexerTest, GetsServices) {
    std::string program =
        "# this is a comment\n"
        "preface:\n"
        "\tauthor Aditya Gomatam\n"
        "\tname rascal\n"
        "\n"
        "services:\n"
        "\tserve ./taillow/ on /tests/static\n"
        "\n";
    Lexer lex(program);
    bool res = lex.tokenize();
    ASSERT_TRUE(res);

    std::vector<TokenType> expected;
    expected.push_back(Preface);
    expected.push_back(Colon);
    expected.push_back(NewLine);
    expected.push_back(Tab);
    expected.push_back(Identifier);
    expected.push_back(Space);
    expected.push_back(Identifier);
    expected.push_back(Space);
    expected.push_back(Identifier);
    expected.push_back(NewLine);
    expected.push_back(Tab);
    expected.push_back(Identifier);
    expected.push_back(Space);
    expected.push_back(Identifier);
    expected.push_back(NewLine);
    expected.push_back(NewLine);
    expected.push_back(Services);
    expected.push_back(Colon);
    expected.push_back(NewLine);
    expected.push_back(Tab);
    expected.push_back(Identifier);
    expected.push_back(Space);
    expected.push_back(Identifier);
    expected.push_back(Space);
    expected.push_back(On);
    expected.push_back(Space);
    expected.push_back(Identifier);
    expected.push_back(NewLine);
    expected.push_back(NewLine);
    expected.push_back(EndOfFile);

    std::vector<Token> parsed_program = lex.getParsedProgram();
    EXPECT_EQ(parsed_program.size(), expected.size());
    for (int i = 0; i < parsed_program.size(); i++) {
        EXPECT_EQ(parsed_program[i].token_type, expected[i]);
    }
}