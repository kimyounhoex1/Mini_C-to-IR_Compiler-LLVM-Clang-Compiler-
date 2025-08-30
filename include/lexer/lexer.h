#pragma once
#include <string>

enum class TokenType { NUMBER, PLUS, MINUS, MUL, DIV, LPAREN, RPAREN, 
  IDENT, ASSIGN, SEMI, // 변수, 할당(=), ;
  END };

struct Token {
  TokenType type;
  std::string value;
  int line;
  int col;
};

class Lexer {
  std::string text;
  std::size_t pos = 0;
  int line = 1;
  int col = 1;
public:
  explicit Lexer(const std::string& input);
  Token getNextToken();
private:
  char advance();
};