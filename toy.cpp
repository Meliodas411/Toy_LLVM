#include <string>
// no use namespace

enum Token_Type {
  EOF_TOKEN = 0,    // EOF
  NUMERIC_TOKEN,    // NUM
  IDENTIFIER_TOKEN, // id
  PARAN_TOKEN,      // {}
  DEF_TOKEN         // def func
};

// ===========define
static int Numeric_Val;
static std::string Identifier_string;
static FILE *file;
// ===========end of define

static int get_token() {
  static int LastChar = ' ';
  while (isspace(LastChar))
    LastChar = fgetc(file);
  if (isalpha(LastChar)) {
    Identifier_string = LastChar;
    while (isalnum((LastChar = fgetc(file))))
      Identifier_string += LastChar;
    if (Identifier_string == "def")
      return DEF_TOKEN;
    return IDENTIFIER_TOKEN;
  }
  if (isdigit(LastChar)) {
    std::string NumStr;
    do {
      NumStr += LastChar;
      LastChar = fgetc(file);
    } while (isdigit(LastChar));
    Numeric_Val = strtod(NumStr.c_str(), 0);
    return NUMERIC_TOKEN;
  }
  if (LastChar == '#') {
    do
      LastChar = fgetc(file);
    while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');
    if (LastChar != EOF)
      return get_token();
  }
  if (LastChar == EOF)
    return EOF_TOKEN;
  int ThisChar = LastChar;
  LastChar = fgetc(file);
  return ThisChar;
}

// ===========AST tree

// base ast
class BaseAST {
public:
  virtual ~BaseAST();
};

// 变量表达式的 AST 类定义
class VariableAST : public BaseAST {};
// 数值表达式的 AST 类定义
class NumericAST : public BaseAST {};
// 二元运算组成的表达式
class BinaryAST : public BaseAST {};
// 用于函数声明的 AST 类定义
class FunctionDeclAST {};
// 用于函数定义的 AST 类
class FunctionDefnAST {};
// 用于函数调用
class FunctionCallAST : public BaseAST {};
