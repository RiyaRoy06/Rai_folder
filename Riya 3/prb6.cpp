#include<bits/stdc++.h>
#define ll long long int
using namespace std;

enum TokenType {
    KEYWORD, IDENTIFIER, NUMBER,OPERATOR, DELIMITER, COMMENT, UNKNOWN
};

struct Token {
    string     lexeme;
    TokenType  type;
    int        line;
};

struct SymEntry {
    string name;
    string kind;
    int    line;
};

vector<Token>              g_tokenList;
vector<SymEntry>           g_symTable;

unordered_map<string,TokenType> g_keywordMap = {
    {"if",KEYWORD},{"else",KEYWORD},{"while",KEYWORD},{"for",KEYWORD},
    {"int",KEYWORD},{"float",KEYWORD},{"char",KEYWORD},{"return",KEYWORD},
    {"main",KEYWORD},{"void",KEYWORD}
};
unordered_map<string,TokenType> g_operatorMap = {
    {"+",OPERATOR},{"-",OPERATOR},{"*",OPERATOR},{"/",OPERATOR},
    {"=",OPERATOR},{"==",OPERATOR},{"!=",OPERATOR},
    {"<",OPERATOR},{">",OPERATOR},{"<=",OPERATOR},{">=",OPERATOR}
};
unordered_map<string,TokenType> g_delimiterMap = {
    {"(",DELIMITER},{")",DELIMITER},{"{",DELIMITER},{"}",DELIMITER},
    {"[",DELIMITER},{"]",DELIMITER},{";",DELIMITER},{",",DELIMITER}
};

bool   isKeyword   (const string&);
bool   isOperator  (const string&);
bool   isDelimiter (char);
void   tokenize    (const string&,int);
void   printSymTable();
string tokenTypeStr(TokenType);

int main(){
    cout<<"Enter your code (type '#' on a new line to finish):\n";
    string codeLine; int lineNo=1;
    while(getline(cin,codeLine)){
        if(codeLine=="#") break;
        tokenize(codeLine,lineNo++);
    }
    printSymTable();
    return 0;
}

void tokenize(const string& codeLine,int lineNo){
    int idx=0, len=codeLine.length();
    while(idx<len){
        if(isspace(codeLine[idx])){ ++idx; continue; }

        if(codeLine[idx]=='/' && idx+1<len && codeLine[idx+1]=='/'){
            Token tk{codeLine.substr(idx),COMMENT,lineNo};
            g_tokenList.push_back(tk);
            break;
        }
        if(codeLine[idx]=='/' && idx+1<len && codeLine[idx+1]=='*'){
            int jdx=idx+2;
            while(jdx<len && !(codeLine[jdx]=='*' && jdx+1<len && codeLine[jdx+1]=='/')) ++jdx;
            if(jdx<len){
                Token tk{codeLine.substr(idx,jdx-idx+2),COMMENT,lineNo};
                g_tokenList.push_back(tk);
                idx=jdx+2; continue;
            }
        }

        if(isdigit(codeLine[idx])){
            int jdx=idx;
            while(jdx<len && isdigit(codeLine[jdx])) ++jdx;
            string numLex = codeLine.substr(idx,jdx-idx);
            g_tokenList.push_back({numLex,NUMBER,lineNo});
            g_symTable.push_back({numLex,tokenTypeStr(NUMBER),lineNo});
            idx=jdx; continue;
        }

        if(isalpha(codeLine[idx]) || codeLine[idx]=='_'){
            int jdx=idx;
            while(jdx<len && (isalnum(codeLine[jdx])||codeLine[jdx]=='_')) ++jdx;
            string word = codeLine.substr(idx,jdx-idx);
            TokenType tt = isKeyword(word)? KEYWORD : IDENTIFIER;
            g_tokenList.push_back({word,tt,lineNo});
            g_symTable.push_back({word,tokenTypeStr(tt),lineNo});
            idx=jdx; continue;
        }

        string one(1,codeLine[idx]);
        if(idx+1<len){
            string two = one + codeLine[idx+1];
            if(isOperator(two)){
                g_tokenList.push_back({two,OPERATOR,lineNo});
                idx+=2; continue;
            }
        }
        if(isOperator(one)){
            g_tokenList.push_back({one,OPERATOR,lineNo});
            ++idx; continue;
        }

        if(isDelimiter(codeLine[idx])){
            g_tokenList.push_back({one,DELIMITER,lineNo});
            ++idx; continue;
        }

        g_tokenList.push_back({one,UNKNOWN,lineNo});
        ++idx;
    }
}

bool isKeyword(const string& s){ return g_keywordMap.count(s); }
bool isOperator(const string& s){ return g_operatorMap.count(s); }
bool isDelimiter(char c){ return g_delimiterMap.count(string(1,c)); }

string tokenTypeStr(TokenType t){
    switch(t){
        case KEYWORD:   return "KEYWORD";
        case IDENTIFIER:return "IDENTIFIER";
        case NUMBER:    return "NUMBER";
        case OPERATOR:  return "OPERATOR";
        case DELIMITER: return "DELIMITER";
        case COMMENT:   return "COMMENT";
        default:        return "UNKNOWN";
    }
}

void printSymTable(){
    cout<<"\nSymbol Table:\n";
    cout<<"+--------------+---------------+\n";
    cout<<"| Token Type   | Lexeme        |\n";
    cout<<"+--------------+---------------+\n";
    for(const auto& e : g_symTable){
        cout<<"| "<<setw(12)<<left<<e.kind<<" | "
            <<setw(13)<<left<<e.name<<" |\n";
    }
    cout<<"+--------------+---------------+\n";
}
