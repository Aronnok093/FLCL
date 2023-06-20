#include<bits/stdc++.h>
using namespace std;

vector<pair<string, string>> symbolTable;

void displaySymbolTable() {
    for (size_t i = 0; i < symbolTable.size(); i++) {
        cout << i + 1 << " " << symbolTable[i].first << " " << symbolTable[i].second << endl;
    }
}

int main() {
    string filename = "symbolTable.txt";
    int sl;
    string id, idType;

    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Failed to open the input file." << endl;
        exit(1);
    }

    while (inputFile >> sl >> id >> idType) {
        symbolTable.push_back(make_pair(id, idType));
    }

    inputFile.close();

    displaySymbolTable();

    cout << "Insert Data: ";
    string newId, newIdType;
    cin >> newId >> newIdType;

    cout << "Insert index: ";
    int index;
    cin >> index;

    if (index < 1 || index > symbolTable.size() + 1) {
        cout << "Invalid index." << endl;
    }

    symbolTable.insert(symbolTable.begin() + index - 1, make_pair(newId, newIdType));
    //numbers.erase(numbers.begin() + 1);
    cout << "The updated Symbol Table:" << endl;
    displaySymbolTable();
    return 0;
}
