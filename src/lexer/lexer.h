#pragma once
#include <string>

enum class TokenType { NUMBER, PLUS, MINUS, MUL, DIV, LPAREN, RPAREN, END };

struct Token {
  TokenType type;
  std::string value;
};

class Lexer {
  std::string text;
  std::size_t pos = 0;
public:
  explicit Lexer(const std::string& input);
  Token getNextToken();
};