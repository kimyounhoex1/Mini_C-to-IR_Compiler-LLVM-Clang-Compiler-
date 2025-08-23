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