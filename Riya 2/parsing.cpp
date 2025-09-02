#include<bits/stdc++.h>
#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <sstream>
using namespace std;

map<pair<string, string>, string> parsing_table = {
    {{"E", "id"}, "T E'"}, {{"E", "("}, "T E'"},
    {{"E'", "+"}, "+ T E'"}, {{"E'", ")"}, "ε"}, {{"E'", "$"}, "ε"},
    {{"T", "id"}, "F T'"}, {{"T", "("}, "F T'"},
    {{"T'", "+"}, "ε"}, {{"T'", "*"}, "* F T'"}, {{"T'", ")"}, "ε"}, {{"T'", "$"}, "ε"},
    {{"F", "id"}, "id"}, {{"F", "("}, "( E )"}
};

void print_parsing_steps(string input) {
    stack<string> st;
    st.push("$");
    st.push("E");

    vector<string> tokens;
    stringstream ss(input);
    string token;
    while (ss >> token) tokens.push_back(token);
    tokens.push_back("$");

    size_t index = 0;
    int step = 1;
    cout << "Step " << step++ << ": Starting parsing | Lookahead: '" << tokens[index] << "'\n";

    while (!st.empty()) {
        string top = st.top(); st.pop();
        string current_token = tokens[index];

        if (top == current_token) {
            cout << "Step " << step++ << ": Matched '" << current_token << "' | Lookahead: '" << tokens[++index] << "'\n";
        } else if (parsing_table.count({top, current_token})) {
            string production = parsing_table[{top, current_token}];
            cout << "Step " << step++ << ": " << top << " -> " << production << " | Lookahead: '" << current_token << "'\n";
            if (production != "ε") {
                vector<string> rhs;
                stringstream prod_ss(production);
                while (prod_ss >> token) rhs.push_back(token);
                for (auto it = rhs.rbegin(); it != rhs.rend(); ++it) st.push(*it);
            }
        } else {
            cout << "Parsing Failed!" << endl;
            return;
        }
    }
    cout << "Parsing successful!" << endl;
}

int main() {
    print_parsing_steps("id + id * id");
    return 0;
}
