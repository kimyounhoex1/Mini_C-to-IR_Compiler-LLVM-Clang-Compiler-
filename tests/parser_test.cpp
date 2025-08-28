#include <iostream>
#include <string>
#include "../src/lexer/lexer.h"
#include "../src/parser/parser.h"

int main() {
  std::string text1 = "(4+5)*(2-1)/3";
  Lexer lex1(text1);
  Parser parser1(lex1);

  try {
    auto ast = parser1.parse();

    std::cout << "== AST ==\n";
    printAst(ast.get());

    std::cout << "== EVAL ==\n";
    std::cout << eval(ast.get()) << "\n"; // 12*(34+56) = 1080
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
   /*
  실행
  g++ -std=c++17 \
  tests/parser_test.cpp \
  src/parser/parser.cpp \
  src/lexer/lexer.cpp \
  -o parser_test
  ./parser_test

  출력
  == AST ==
  Binary(*)
    Number(12)
    Binary(+)
      Number(34)
      Number(56)
  == EVAL ==
  1080
  */


  std::string text2 = "-3";
  Lexer lex2(text2);
  Parser parser2(lex2);

  try {
    auto ast = parser2.parse();

    std::cout << "== AST ==\n";
    printAst(ast.get());

    std::cout << "== EVAL ==\n";
    std::cout << eval(ast.get()) << "\n"; // 12*(34+56) = 1080
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
}