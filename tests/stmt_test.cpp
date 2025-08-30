#include <iostream>
#include <string>
#include "../include/lexer/lexer.h"
#include "../include/parser/parser.h"

int main() {
  // 샘플 입력 (문장 여러 개)
  std::string text = R"( 
    x = 1 + 2;
    y = x * 3;
    y;
  )";

  Lexer lex(text);
  Parser parser(lex);

  try {
    Program prog = parser.parseProgram();   // ★ 프로그램 단위로 파싱

    std::cout << "== PROGRAM AST ==\n";
    printProgram(prog);                     // ★ AST 출력 함수 (parser.cpp 안에 구현)

  } catch (std::exception &e) {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}