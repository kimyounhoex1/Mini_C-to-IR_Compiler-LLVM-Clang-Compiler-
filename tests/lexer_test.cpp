#include <string>
#include <iostream>
#include "../src/lexer/lexer.h"
using namespace std;

int main() {
  string text = "12*(34+56)";
  Lexer lexer(text);
  Token t;
  while((t = lexer.getNextToken()).type != TokenType::END) {
    cout << "Token(" << t.value << ")\n";
  }
}
/*
입력
 g++ -std=c++17 tests/lexer_test.cpp src/lexer/lexer.cpp -o lexer_test
 ./lexer_test

출력
Token(12)
Token(*)
Token(()
Token(34)
Token(+)
Token(56)
Token())
 *
 * 
*/