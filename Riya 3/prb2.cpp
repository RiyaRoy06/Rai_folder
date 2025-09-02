#include <bits/stdc++.h>
#define ll long long int
using namespace std;

unordered_set<char> riya_operators = {'+', '-', '*', '/', '=', '<', '>', '!'};
bool Operator(char ch) {
    return riya_operators.find(ch) != riya_operators.end();
}

unordered_set<char> riya_symbol = {'(', ')', '{', '}', '[', ']', ',', ';', ':'};
bool symbol(char ch) {
    return riya_symbol.find(ch) != riya_symbol.end();
}

unordered_set<string> riya_key = {"int", "float", "double", "ll", "char", "string", "if", "else", "while", "return", "void", "main"};
                                 
bool Key(const string &s) {
    return riya_key.find(s) != riya_key.end();
}

bool ValidIdentifier(const string &s) {
    if(s.empty() || (!isalpha(s[0]) && s[0] != '_')) return false;
    return all_of(s.begin(), s.end(), [](char c) { return isalnum(c) || c == '_'; });
}

bool NumericLiteral(const string &s) {
    if(s.empty()) return false;
    size_t i = 0;
    if(s[0] == '-') i = 1; 
    for(; i < s.size(); i++) {
        if(!isdigit(s[i]) && s[i] != '.') return false;
    }
    return true;
}

bool isStringLiteral(const string &s) {
    return s.size() >= 2 && s.front() == '"' && s.back() == '"';
}

bool isOperatorToken(const string &s) {
    if(s.size() == 1) return Operator(s[0]);
    if(s.size() == 2) {
        return (s == "==" || s == "!=" || s == "<=" || s == ">=" || s == "++" || s == "--");
    }
    return false;
}

bool ValidExpression(const vector<string>& tokens, size_t start, size_t end) {
    if(start >= end) return false;
    
    for(size_t i = start; i <= end; i++) {
        const string& token = tokens[i];
        
        if(isOperatorToken(token)) {
            if(i == start || i == end) return false;
            
            if(!(ValidIdentifier(tokens[i-1]) || NumericLiteral(tokens[i-1]) || 
               tokens[i-1] == ")" || isStringLiteral(tokens[i-1]))) {
                return false;
            }
            if(!(ValidIdentifier(tokens[i+1]) || NumericLiteral(tokens[i+1]) ||
               tokens[i+1] == "(" || isStringLiteral(tokens[i+1]))) {
                return false;
            }
        }
        else if(token == "(") {
            
            int balance = 1;
            size_t j = i + 1;
            while(j <= end && balance > 0) {
                if(tokens[j] == "(") balance++;
                else if(tokens[j] == ")") balance--;
                j++;
            }
            if(balance != 0) return false;
            if(!ValidExpression(tokens, i+1, j-2)) return false;
            i = j-1;
        }
        else if(!ValidIdentifier(token) && !NumericLiteral(token) && 
                !isStringLiteral(token) && token != ")") {
            return false;
        }
    }
    return true;
}

bool ValidSequence(const vector<string> &tokens) {
    bool hasSemicolon = false;
    bool inControlStructure = false;
    bool expectBlockOrStatement = false;
    size_t controlStart = 0;
    
    for(size_t i = 0; i < tokens.size(); i++) {
        const string &token = tokens[i];
        
        if(Key(token) && (token == "if" || token == "while")) {
            if(i + 1 >= tokens.size() || tokens[i+1] != "(") {
                return false;
            }
            inControlStructure = true;
            expectBlockOrStatement = true;
            controlStart = i;
        }
        else if(token == "(" && inControlStructure) {
            int balance = 1;
            size_t j = i + 1;
            while(j < tokens.size() && balance > 0) {
                if(tokens[j] == "(") balance++;
                else if(tokens[j] == ")") balance--;
                j++;
            }
            if(balance != 0) return false;
            
            if(!ValidExpression(tokens, i+1, j-2)) {
                return false;
            }
            
            i = j-1;
            inControlStructure = false;
            
            if(i + 1 < tokens.size()) {
                if(tokens[i+1] == "{") {
                    continue;
                } else if(tokens[i+1] == ";") {
                    
                    i++;
                    expectBlockOrStatement = false;
                } else {

                    expectBlockOrStatement = true;
                }
            }
        }
        else if(token == ";") {
            hasSemicolon = true;
            if(expectBlockOrStatement) {
                expectBlockOrStatement = false;
                continue;
            }
            if(i == 0 || isOperatorToken(tokens[i-1])) {
                return false;
            }
        }
        else if(expectBlockOrStatement) {
            
            expectBlockOrStatement = false;
            
            
            if(!ValidExpression(tokens, i, tokens.size()-1)) {
                return false;
            }
            
            if(tokens.back() != ";") {
                return false;
            }
            break;
        }
        else if(token == "{") {
            
            int balance = 1;
            size_t j = i + 1;
            while(j < tokens.size() && balance > 0) {
                if(tokens[j] == "{") balance++;
                else if(tokens[j] == "}") balance--;
                j++;
            }
            if(balance != 0) return false;
            i = j-1;
        }
    }
    
    
    if(!expectBlockOrStatement && !hasSemicolon) {
        
        if(tokens.empty() || (tokens.back() != "}" && tokens.back() != "{")) {
            return false;
        }
    }
    
    return true;
}

void lexicalAnalysis(const string &line) {
    vector<string> tokens;
    string token;

    for(size_t i = 0; i < line.size();) {
        char ch = line[i];

        if(isspace(ch)) {
            if(!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            i++;
            continue;
        }

        if(Operator(ch) || symbol(ch)) {
            if(!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            
            
            if(i + 1 < line.size() && Operator(ch) && Operator(line[i+1])) {
                string op;
                op += ch;
                op += line[i+1];
                if(isOperatorToken(op)) {
                    tokens.push_back(op);
                    i += 2;
                    continue;
                }
            }
            
            tokens.push_back(string(1, ch));
            i++;
            continue;
        }

        token += ch;
        i++;
    }

    if(!token.empty()) {
        tokens.push_back(token);
    }

    if(!ValidSequence(tokens)) {
        cout << "Invalid input: Syntax error.\n\n";
        return;
    }

    vector<string> keywords;
    set<string> identifiers, constants;
    set<string> symbols;
    set<string> operators;

    for(const string &t : tokens) {
        if(symbol(t[0]) && t.size() == 1) {
            symbols.insert(t);
        }
        else if(Key(t)) {
            keywords.push_back(t);
        }
        else if(ValidIdentifier(t)) {
            identifiers.insert(t);
        }
        else if(NumericLiteral(t) || isStringLiteral(t)) {
            constants.insert(t);
        }
        else if(isOperatorToken(t)) {
            operators.insert(t);
        }
        else {
            cout << "Invalid token: " << t << "\n\n";
            return;
        }
    }

    cout << "Keywords: ";
    for(const string &kw : keywords) cout << kw << " ";
    cout << "\n";

    cout << "Operators: ";
    for(const string &op : operators) cout << op << " ";
    cout << "\n";

    cout << "Symbols: ";
    for(const string &sym : symbols) cout << sym << " ";
    cout << "\n";

    cout << "Identifiers: ";
    for(const string &id : identifiers) cout << id << " ";
    cout << "\n";

    cout << "Constants: ";
    for(const string &cnst : constants) cout << cnst << " ";
    cout << "\n\n";
}

int main() {
        string line;
        cout << "Enter a line: ";
        getline(cin, line);

        cout << "\nTokens:\n";
        lexicalAnalysis(line);
}