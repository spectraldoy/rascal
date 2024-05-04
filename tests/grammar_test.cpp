#include "grammar.h"
#include "lexer.h"
#include "result.h"
#include "gtest/gtest.h"

#include <string>

std::vector<Token> parseProgram(std::string program) {
    Lexer lex(program);
    Result res = lex.tokenize();
    EXPECT_TRUE(res.isOk()) << res.getError();
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
    Result res = grammar.check();
    ASSERT_TRUE(res.isOk()) << res.getError();
}

TEST(GrammarTest, NoSepBetweenSections) {
    std::string program =
        "services:\n"
        "\tserve ./static on /test_path\n"
        "\techo on /seventy_two\n"
        "tcp:\n"
        "\tport 8080\n"
        "\n";
    std::vector<Token> parsed_program = parseProgram(program);
    Grammar grammar(parsed_program);
    Result res = grammar.check();
    ASSERT_TRUE(res.isOk()) << res.getError();
}

TEST(GrammarTest, NoTabUnderSection) {
    std::string program =
        "services:\n"
        "\tserve ./static on /test_path\n"
        "echo on /seventy_two\n"
        "tcp:\n"
        "\tport 8080\n"
        "\n";
    std::vector<Token> parsed_program = parseProgram(program);
    Grammar grammar(parsed_program);
    Result res = grammar.check();
    ASSERT_TRUE(res.isError()) << res.getError();
}

TEST(GrammarTest, EmptyFile) {
    std::string program = "";
    std::vector<Token> parsed_program = parseProgram(program);
    Grammar grammar(parsed_program);
    Result res = grammar.check();
    ASSERT_TRUE(res.isOk()) << res.getError();
}

TEST(GrammarTest, EmptySection) {
    std::string program =
        "services:\n"
        "tcp:\n"
        "\tport 8080\n"
        "\n";
    std::vector<Token> parsed_program = parseProgram(program);
    Grammar grammar(parsed_program);
    Result res = grammar.check();
    ASSERT_TRUE(res.isOk()) << res.getError();
}

TEST(GrammarTest, NoTcp) {
    std::string program =
        "services:\n"
        "\techo on /static\n"
        "\tredirect_to www.google.com on /goog\n"
        "\n";
    std::vector<Token> parsed_program = parseProgram(program);
    Grammar grammar(parsed_program);
    Result res = grammar.check();
    ASSERT_TRUE(res.isOk()) << res.getError();
}


TEST(GrammarTest, NoServices) {
    std::string program =
        "tcp:\n"
        "\techo should be 1\n"
        "\tport 100\n"
        "\n";
    std::vector<Token> parsed_program = parseProgram(program);
    Grammar grammar(parsed_program);
    Result res = grammar.check();
    ASSERT_TRUE(res.isOk()) << res.getError();
}

TEST(GrammarTest, MultipleServices) {
     std::string program =
        "services:\n"
        "\tserve ./static on /test_path\n"
        "\techo on /seventy_two\n"
        "tcp:\n"
        "\tport 8080\n"
        "services:\n"
        "\tredirect_to www.google.com on /test_path\n"
        "\tupload_to ./tests/ on /sixty_two\n";
    std::vector<Token> parsed_program = parseProgram(program);
    Grammar grammar(parsed_program);
    Result res = grammar.check();
    ASSERT_TRUE(res.isOk()) << res.getError();
}

TEST(GrammarTest, NoWordInLine) {
    std::string program =
        "services:\n"
        "\tserve ./static on /test_path\n"
        "\t\n"
        "\tredirect_to place on /path\n"
        "tcp:\n"
        "\tport 8080\n"
        "\n";
    std::vector<Token> parsed_program = parseProgram(program);
    Grammar grammar(parsed_program);
    Result res = grammar.check();
    ASSERT_TRUE(res.isError()) << res.getError();
}

TEST(GrammarTest, LineStartsWithSpace) {
    std::string program =
        "services:\n"
        "\tserve ./static on /test_path\n"
        "\t echo on /path\n"
        "\tredirect_to place on /path\n"
        "tcp:\n"
        "\tport 8080\n"
        "\n";
    std::vector<Token> parsed_program = parseProgram(program);
    Grammar grammar(parsed_program);
    Result res = grammar.check();
    ASSERT_TRUE(res.isError()) << res.getError();
}

TEST(GrammarTest, PrefaceWithoutTabs) {
    std::string program =
        "preface:\n"
        "\tauthor Aditya Gomatam\n"
        "project rascal\n"
        "\tversion 0.0.0\n"
        "\n"
        "services:\n"
        "\tserve ./static on /test_path\n"
        "\n"
        "tcp:\n"
        "\tport 8080\n";
    std::vector<Token> parsed_program = parseProgram(program);
    Grammar grammar(parsed_program);
    Result res = grammar.check();
    ASSERT_TRUE(res.isError()) << res.getError();
}
