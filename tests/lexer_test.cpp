#include "lexer.h"
#include "result.h"
#include "gtest/gtest.h"

TEST(LexerTest, IgnoreComment) {
    std::string program =
        "# this is a comment\n"
        "preface:\n"
        "\tauthor Aditya Gomatam\n"
        "\tname rascal\n"
        "\n";
    Lexer lex(program);
    Result<void*, std::string> res = lex.tokenize();
    ASSERT_TRUE(res.isOk());
}