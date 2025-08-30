#include "../src/symbol/symbol_table.h"
#include <iostream>
using namespace std;

int main() {
  SymbolTable table;
  cout << "\n====== 전역 스코프 =======" << endl;
  if(table.declare("x", {"int", 1, 1})) {
    cout << "x 선언 성공 (int)" << endl;
  }

  if(!table.declare("x", {"float", 2, 5})) {
    cout << "x 중복 선언, 실패" << endl;
  }

  auto xInfo = table.lookup("x");
  if(xInfo) {
    cout << "lookup(x): type=" << xInfo->type << endl;
  }

  cout << "\n====== 스코프 진입 =======" << endl;
  table.enterScope();
  
  if(table.declare("y", {"float", 3, 2})) {
    cout << "y 선언 성공 (float)" << endl;
  }

  auto yInfo = table.lookup("y");

  if(yInfo) {
    cout << "lookup(y): type=" << xInfo->type << endl;
  }

  xInfo = table.lookup("x");
  if (xInfo) {
    cout << "lookup(x) from inner scope: type=" << xInfo->type << endl;
  }
  
  cout << "\n===== 스코프 종료 =====" << endl;
  table.exitScope();

  // y는 더 이상 없음
  yInfo = table.lookup("y");
  if (!yInfo) {
      cout << "y는 스코프 종료로 접근 불가" << endl;
  }

  // x는 여전히 존재
  xInfo = table.lookup("x");
  if (xInfo) {
      cout << "lookup(x) after scope exit: type=" << xInfo->type << endl;
  }

  return 0;
}