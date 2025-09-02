#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <string>

using namespace std;

// Parsing table
map<string, map<string, string>> parsingTable = {
    {"E", {{"id", "T E'"}}},
    {"E'", {{"+", "+ T E'"}, {"$", "ε"}}},
    {"T", {{"id", "F T'"}}},
    {"T'", {{"+", "ε"}, {"", " F T'"}, {"$", "ε"}}},
    {"F", {{"id", "id"}}},
};

// Function to check if a symbol is a terminal
bool isTerminal(const string &symbol) {
    return symbol == "id" || symbol == "+" || symbol == "*" || symbol == "(" || symbol == ")" || symbol == "$";
}

// Function to simulate the predictive parser
bool predictiveParser(const vector<string> &input) {
    stack<string> parserStack;
    parserStack.push("$");
    parserStack.push("E"); // Start symbol

    int index = 0;

    while (!parserStack.empty()) {
        string top = parserStack.top();
        string currentInput = input[index];

        if (isTerminal(top)) {
            // Terminal symbol handling
            if (top == currentInput) {
                parserStack.pop();
                index++;
            } else {
                cout << "Error: Mismatch at " << currentInput << endl;
                return false;
            }
        } else if (parsingTable[top][currentInput] != "") {
            // Non-terminal symbol handling
            string production = parsingTable[top][currentInput];
            parserStack.pop();

            if (production != "ε") {
                vector<string> symbols;
                size_t pos = 0;
                while ((pos = production.find(' ')) != string::npos) {
                    symbols.push_back(production.substr(0, pos));
                    production.erase(0, pos + 1);
                }
                symbols.push_back(production);

                for (auto it = symbols.rbegin(); it != symbols.rend(); ++it) {
                    parserStack.push(*it);
                }
            }
        } else {
            cout << "Error: Invalid input at " << currentInput << endl;
            return false;
        }
    }

    return index == input.size();
}

int main() {
    vector<string> input = {"id", "+", "id", "*", "id", "$"}; // Input string tokenized

    cout << "Parsing input: ";
    for (const string &token : input) {
        cout << token << " ";
    }
    cout << endl;

    if (predictiveParser(input)) {
        cout << "Input string is successfully parsed!" << endl;
    } else {
        cout << "Failed to parse the input string." << endl;
    }

    return 0;
}