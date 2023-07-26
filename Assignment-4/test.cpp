#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <stack>
#include<bits/stdc++.h>
using namespace std;

// Function to tokenize the input code segment into individual tokens
vector<string> tokenizeCode(const string& code) {
    vector<string> tokens;
    string token;
    bool inMultiLineComment = false;

    for (int i = 0; i < code.size(); i++) {
        if (inMultiLineComment) {
            if (code[i] == '*' && i + 1 < code.size() && code[i + 1] == '/') {
                inMultiLineComment = false;
                i++; // Skip the '/'
            }
        } else {
            if (code[i] == '/' && i + 1 < code.size()) {
                if (code[i + 1] == '*') {
                    inMultiLineComment = true;
                    i++; // Skip the '*'
                } else if (code[i + 1] == '/') {
                    // Skip the rest of the line (including the newline character)
                    while (i < code.size() && code[i] != '\n') {
                        i++;
                    }
                }
            } else if (code[i] == ' ') {
                if (!token.empty()) {
                    tokens.push_back(token);
                    token.clear();
                }
            } else if (code[i] == '\n') {
                if (!token.empty()) {
                    tokens.push_back(token);
                    token.clear();
                }
                tokens.push_back("\n");
            }
             else {
                token += code[i];
            }
        }
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}



// Function to detect syntax errors in the given tokenized code
void detectSyntaxErrors(const vector<string>& tokens) {
    unordered_map<string, int> symbolTable;
    stack<string> stack;
    int line = 1;

    for (const string& token : tokens) {
        if (token == "{" || token == "(") {
            stack.push(token);
        } else if (token == "}" || token == ")") {
            if (stack.empty() || (token == "}" && stack.top() != "{") || (token == ")" && stack.top() != "(")) {
                cout << "Misplaced '" << token << "' at line " << line << endl;
            } else {
                stack.pop();
            }
        } else if (token == "else") {
            if (stack.empty() || stack.top() != "if") {
                cout << "Unmatched 'else' at line " << line << endl;
            }
        } else if (token == ";") {
            // Additional check for duplicate semicolons in 'for' construct
            if (!stack.empty() && stack.top() == "for") {
                cout << "Duplicate ';' in 'for' construct at line " << line<< endl;
            }
        }

        // Update the symbol table for identifier declarations
        if (token == "int" || token == "float" || token == "double" || token == "char") {
            if (tokens.size() > 1 && symbolTable.find(tokens[1]) != symbolTable.end()) {
                cout << "Duplicate identifier declaration at line " << line<< endl;
            }
            symbolTable[tokens[1]] = line;
        }

        if (token.back() == ';') {
            // Remove semicolon from tokens like 'x1;' for proper checking
            string identifier = token.substr(0, token.length() - 1);
            if (symbolTable.find(identifier) != symbolTable.end()) {
                cout << "Duplicate token at line " << line<< endl;
            }
        }

        // Update line number
        if (token.find('\n') != string::npos) {
            line++;
        }
    }
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error: Cannot open input file." << endl;
        return 1;
    }

    string code;
    string line;
    while (getline(inputFile, line)) {
        code += line + "\n";
    }

    inputFile.close();
    vector<string> tokens = tokenizeCode(code);
    detectSyntaxErrors(tokens);
    int cnt=1;
    cout<<" "<<cnt++<<" ";
    for (const string& token : tokens) {
        cout << token << " ";
        if(token=="\n")
        cout<<cnt++<<" ";
    }
    cout << endl;

    return 0;
}
