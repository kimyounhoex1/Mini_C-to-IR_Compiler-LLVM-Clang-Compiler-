#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>
using namespace std;

enum class TokenType { NUMBER, PLUS, MINUS, MUL, DIV, LPAREN, RPAREN, END };

struct Token {
  TokenType type;
  string value;
};

class Lexer {
  string text;
  size_t pos = 0;

public:
  Lexer(const string& input) {
    text = input;
  }

  bool is_space(char c){
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
  }

  bool is_digit(char c){
    return '0' <= c && c <= '9';
  }
  
  Token getNextToken() {
    while(pos < this->text.size()){
      char c = text.at(pos);
      
      if(is_space(c)){
        pos++;
        continue;
      } 
      if('0'<=c && c<='9'){
        string num = "";
        while( pos < this->text.size() && (is_digit(text.at(pos)))){
          num = num + text.at(pos++);
        }
        return {TokenType::NUMBER, num};
      }

      if(c == '+'){
        pos++;
        return {TokenType::PLUS, "+"};
      }
      if(c == '-'){
        pos++;
        return {TokenType::MINUS, "-"};
      }
      if(c == '*'){
        pos++;
        return {TokenType::MUL, "*"};
      }
      if(c == '/'){
        pos++;
        return {TokenType::DIV, "/"};
      }
      if(c == '('){
        pos++;
        return {TokenType::LPAREN, "("};
      }
      if(c == ')'){
        pos++;
        return {TokenType::RPAREN, ")"};  
      }

      throw runtime_error("Invalid character");
    }

    return {TokenType::END, ""};
  }
};

int main() {
  string text = "12*(34+56)";

  Lexer lexer(text);

  Token t;

  while((t = lexer.getNextToken()).type != TokenType::END) {
    cout << "Token(" << t.value << ")\n";
  }
}


// int main() {
//     string input = "12 + 34 * (5 - 2)";
//     Lexer lexer(input);

//     Token t;
//     while ((t = lexer.getNextToken()).type != TokenType::END) {
//         cout << "Token(" << t.value << ")\n";
//     }
// }