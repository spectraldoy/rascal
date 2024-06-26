#include "lexer.h"
#include "grammar.h"
#include "result.h"
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: build/bin/rascal <file>" << std::endl;
        exit(1);
    }

    std::string filename(argv[1]);
    fs::path file_path(filename);
    std::ifstream file(file_path);
    if (!file.good() || !file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        exit(1);
    }

    std::string program = "";
    char c;
    while (file.get(c)) {
        program += c;
    }

    Lexer lex(program);
    Result res = lex.tokenize();
    if (res.isError()) {
        std::cout << res.getError() << std::endl;
        exit(1);
    }

    std::vector<Token> parsed_program = lex.getParsedProgram();
    Grammar checker(parsed_program);
    res = checker.check();
    if (res.isError()) {
        std::cout << res.getError() << std::endl;
        exit(1);
    }

    std::cout << "Parsed successfully" << std::endl;

    return 0;
}