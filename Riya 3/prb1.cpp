#include<bits/stdc++.h>
#define ll long long int
using namespace std;
vector<string> keywords = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if", "int",
    "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while","main"
};

bool isValidIdentifier(const string &str) {
    if (!isalpha(str[0]) && str[0] != '_')
        return false;
    for (int i = 1; i < str.length(); i++) {
        if (!isalnum(str[i]) && str[i] != '_')
            return false;
    }
    return true;
}

bool isKeyword(const string &str) {
    return find(keywords.begin(), keywords.end(), str) != keywords.end();
}

bool isComment(const string &str) {
    return (str.substr(0, 2) == "//" || str.substr(0, 2) == "/*");
}

int main() {
    int choice;
    string input;

    cout << "Select any option:\n";
    cout << "1: To check Identifier\n";
    cout << "2: To check Keyword\n";
    cout << "3: To check Comment\n";
    cout << "Choose your option: ";
    cin >> choice;
    cin.ignore();

    cout << "Please enter any string: ";
    getline(cin, input);

    switch (choice) {
        case 1:
            if (isValidIdentifier(input) && !isKeyword(input))
                cout << "Output: This is a valid Identifier\n";
            else
                cout << "Output: This is not a valid Identifier\n";
            break;
        case 2:
            if (isKeyword(input))
                cout << "Output: This is a Keyword\n";
            else
                cout << "Output: This is not a Keyword\n";
            break;
        case 3:
            if (isComment(input))
                cout << "Output: This is a Comment\n";
            else
                cout << "Output: This is not a Comment\n";
            break;
        default:
            cout << "Invalid choice.\n";
    }

    return 0;
}
