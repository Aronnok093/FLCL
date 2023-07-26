#include <iostream>
#include <vector>


#include<bits/stdc++.h>
using namespace std;

enum TokenType {
  TOKEN_DUPLICATE,
  TOKEN_MISPLACED_BRACE,
  TOKEN_UNMATCHED_ELSE,
  TOKEN_UNDECLARED_IDENTIFIER,
  TOKEN_DUPLICATE_IDENTIFIER,
};

struct Token {
  TokenType type;
  int line;
  string value;
};

vector<Token> tokenize(const string& code) {
  vector<Token> tokens;
  for (int i = 0; i < code.length(); i++) {
    char c = code[i];
    if (c == ';') {
      tokens.push_back({TOKEN_DUPLICATE, i});
    } else if (c == '}') {
      tokens.push_back({TOKEN_MISPLACED_BRACE, i});
    } else if (c == '}') {
      tokens.push_back({TOKEN_UNMATCHED_ELSE, i});
    } else if (!isalnum(c)) {
      tokens.push_back({TOKEN_UNDECLARED_IDENTIFIER, i});
    } else {
      tokens.push_back({TOKEN_DUPLICATE_IDENTIFIER, i});
    }
  }
  return tokens;
}

vector<string> build_symbol_table(const vector<Token>& tokens) {
  vector<string> symbol_table;
  for (const Token& token : tokens) {
    if (token.type == TOKEN_UNDECLARED_IDENTIFIER) {
      symbol_table.push_back(token.value);
    }
  }
  return symbol_table;
}

vector<string> detect_syntax_errors(const vector<Token>& tokens) {
  vector<string> errors;
  for (const Token& token : tokens) {
    switch (token.type) {
      case TOKEN_DUPLICATE:
        errors.push_back("Duplicate token at line {}".format(token.line));
        break;
      case TOKEN_MISPLACED_BRACE:
        errors.push_back(fmt::format("Misplaced `}` at line {}", token.line));
        break;
      case TOKEN_UNMATCHED_ELSE:
        errors.push_back("Unmatched `else` at line {}".format(token.line));
        break;
      case TOKEN_UNDECLARED_IDENTIFIER:
        errors.push_back("Undeclared identifier `{}` at line {}".format(token.value, token.line));
        break;
      case TOKEN_DUPLICATE_IDENTIFIER:
        errors.push_back("Duplicate identifier declaration for `{}` at line {}".format(token.value, token.line));
        break;
    }
  }
  return errors;
}
int main() {
  string code = "float x1 = 3.125;;;\n\ndouble f1(float a, int int x)\n{\nif(x<x1)\ndouble z;;\nelse z = 0.01;}}else return z;\n}\nint main(void)\n{{{{int n1; double z;\nn1=25; z=f1(n1);}}";
  vector<Token> tokens = tokenize(code);
  vector<string> errors = detect_syntax_errors(tokens);
  for (const string& error : errors) {
    cout << error << endl;
  }
  return 0;
}
