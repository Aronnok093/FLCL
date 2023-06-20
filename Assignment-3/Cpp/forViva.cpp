//Fardin Jaman Aranyak
//ID:190204093
//Imagination Better Than Knowledge

#include<bits/stdc++.h>
using namespace std;
// Structure to represent symbol table entry
struct SymbolEntry {
    int slNo;
    string name;
    string idType;
    string dataType;
    string scope;
    string value;
};

// Global variables
vector<SymbolEntry> symbolTable;

// Function declarations
void display();
void lookup();
void freeSymbolTable();
void setAttribute();
void insert();

int main() {
    ifstream file("input.txt");
    string lexemes;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            lexemes += line;
        }
        file.close();
    } else {
        cout << "Failed to open the input file." << endl;
        return 1;
    }

    string copyLexemes;
    for (size_t i = 0; i < lexemes.length(); i++) {
        if (lexemes[i] == '[') {
            copyLexemes += lexemes[i];
            copyLexemes += ' ';
        } else if (lexemes[i] == ']') {
            copyLexemes += ' ';
            copyLexemes += lexemes[i];
        } else {
            copyLexemes += lexemes[i];
        }
    }

    vector<string> lexemesList;
    string token;
    for (size_t i = 0; i < copyLexemes.length(); i++) {
        if (copyLexemes[i] == ' ') {
            if (!token.empty()) {
                lexemesList.push_back(token);
                token.clear();
            }
        } else {
            token += copyLexemes[i];
        }
    }
    cout<<"Input Stream:"<<endl;
    cout<<copyLexemes<<endl;
    vector<string> tokenToBeRemove = {"kw", "op", "num", "sep", "par", "brc"};
    vector<string> dataType = {"double", "int", "float"};
    vector<vector<string>> idNamesWithDataType;
    vector<vector<string>> idNamesWithType;
    vector<vector<string>> idNamesWithValue;

    for (auto it = lexemesList.begin(); it != lexemesList.end(); ) {
    if (find(tokenToBeRemove.begin(), tokenToBeRemove.end(), *it) != tokenToBeRemove.end()) {
        it = lexemesList.erase(it);
    } else {
        ++it;
    }
}
    cout<<"Step 1: "<<endl;
    for(int i =0;i<=lexemesList.size();i++){
        cout<<lexemesList[i]<<" ";
    }
    int scopeFlag = 0;
    string scope;
    for (size_t i = 0; i < lexemesList.size(); i++) {
        if (lexemesList[i] == "id" && lexemesList[i + 4] == "(") {
            scope = lexemesList[i + 1];
            scopeFlag = 1;
        } else if (lexemesList[i] == "id" && lexemesList[i + 1] == "main" && lexemesList[i + 4] == "(") {
            scope = "main";
            scopeFlag = 1;
        } else if (lexemesList[i] == "}") {
            scopeFlag = 0;
        } else if (scopeFlag == 0) {
            scope = "global";
        }
        if (lexemesList[i] == "id" && find(dataType.begin(), dataType.end(), lexemesList[i - 3]) != dataType.end()) {
            if (lexemesList[i + 1] == "main") {
                idNamesWithDataType.push_back({"global", lexemesList[i + 1], lexemesList[i - 3]});
            } else {
                idNamesWithDataType.push_back({scope, lexemesList[i + 1], lexemesList[i - 3]});
            }
            if (lexemesList[i + 4] == "(") {
                idNamesWithType.push_back({scope, lexemesList[i + 1], "func"});
            } else {
                idNamesWithType.push_back({scope, lexemesList[i + 1], "var"});
            }
        }
    }


    scopeFlag = 0;
    for (size_t i = 0; i < lexemesList.size(); i++) {
        if (lexemesList[i] == "id" && lexemesList[i + 4] == "(") {
            scope = lexemesList[i + 1];
            scopeFlag = 1;
        } else if (lexemesList[i] == "id" && lexemesList[i + 1] == "main" && lexemesList[i + 4] == "(") {
            scope = "main";
            scopeFlag = 1;
        } else if (lexemesList[i] == "}") {
            scopeFlag = 0;
        } else if (scopeFlag == 0) {
            scope = "global";
        }
        if (lexemesList[i] == "id") {
            if (lexemesList[i + 4] == "=" && lexemesList[i + 7] != "id") {
                idNamesWithValue.push_back({scope, lexemesList[i + 1], lexemesList[i + 7]});
            }
        }
    }

    int sn = 0;
    for (size_t i = 0; i < idNamesWithDataType.size(); i++) {
        sn++;
        string name = idNamesWithDataType[i][1];
        string idType = idNamesWithType[i][2];
        string dtType = idNamesWithDataType[i][2];
        string scp = idNamesWithDataType[i][0];
        string values = "";
        for (size_t j = 0; j < idNamesWithValue.size(); j++) {
            if (name == idNamesWithValue[j][1] && scp == idNamesWithValue[j][0]) {
                values = idNamesWithValue[j][2];
                break;
            }
        }
        symbolTable.push_back({sn, name, idType, dtType, scp, values});
    }

    // Function implementations

    // Example usage of the functions
     while (true) {
        cout << "\nA. Insert\nB. Set Attribute\nC. Clear\nD. Look Up\nE. Display\n"
                  << "Enter the mode (A, B, C, D, or E): ";

        char mode;
        cin >> mode;

        switch (mode) {
            case 'A':
                insert();
                break;
            case 'B':
                setAttribute();
                break;
            case 'C':
                freeSymbolTable();
                break;
            case 'D':
                lookup();
                break;
            case 'E':
                display();
                break;
            default:
                cout << "Invalid mode selection." << endl;
                break;
        }
     }

    return 0;
}
void display() {
       if (symbolTable.empty()) {
        cout << "Symbol table is empty." << endl;
    } else {
        cout << setw(10) << "Sl. No." << setw(15) << "Name" << setw(10) << "ID Type" << setw(12)
                  << "Data Type" << setw(10) << "Scope" << setw(10) << "Value" << endl;

        for (const auto& entry : symbolTable) {
            cout << setw(10) << entry.slNo << setw(15) << entry.name << setw(10) << entry.idType
                      << setw(12) << entry.dataType << setw(10) << entry.scope << setw(10) << entry.value
                      << endl;
        }
    }
    }

    void lookup() {
        string name;
        cout << "Enter an Identifier's Name: ";
        cin >> name;

        cout << setw(10) << "Sl. No." << setw(15) << "Name" << setw(10) << "ID Type" << setw(12)
                  << "Data Type" << setw(10) << "Scope" << setw(10) << "Value" << endl;
        bool found = false;
        for (const auto& entry : symbolTable) {
            if (name == entry.name) {
                cout << setw(10) << entry.slNo << setw(15) << entry.name << setw(10) << entry.idType
                      << setw(12) << entry.dataType << setw(10) << entry.scope << setw(10) << entry.value
                      << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Identifier not found in the symbol table." << endl;
        }
    }

    void freeSymbolTable() {
        symbolTable.clear();
        cout << "Symbol table has been cleared." << endl;
    }

    void setAttribute() {
        string name;
        cout << "Enter an Identifier's Name: ";
        cin >> name;

        bool found = false;
        for (auto& entry : symbolTable) {
            if (name == entry.name) {
                string attribute;
                cout << "Enter the new attribute: ";
                cin >> attribute;
                entry.idType = attribute;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Identifier not found in the symbol table." << endl;
        }
    }

    void insert() {
        string name;
        cout << "Enter an Identifier's Name: ";
        cin >> name;
        int sn=symbolTable.size()+1;
        bool found = false;
        for (const auto& entry : symbolTable) {
            if (name == entry.name) {
                found = true;
                break;
            }
        }
        if (found) {
            cout << "Identifier already exists in the symbol table." << endl;
        } else {
            string idType, dataType, scope, value;
            cout << "Enter the ID Type: ";
            cin >> idType;
            cout << "Enter the Data Type: ";
            cin >> dataType;
            cout << "Enter the Scope: ";
            cin >> scope;
            cout << "Enter the Value: ";
            cin >> value;
            symbolTable.push_back({++sn, name, idType, dataType, scope, value});
        }
    }

