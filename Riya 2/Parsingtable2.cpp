#include<bits/stdc++.h>
#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

// Grammar rules:
// E → E + T | T
// T → T * F | F
// F → id

vector<string> inputTokens = {"id", "+", "id", "*", "id", "$"};  // Input string split into tokens

bool isOperator(const string &s) {
    return s == "+" || s == "*";
}

bool isId(const string &s) {
    return s == "id";
}

bool reduce(stack<string> &st) {
    if (st.size() >= 3) {
        vector<string> top3;
        for (int i = 0; i < 3; i++) {
            top3.push_back(st.top());
            st.pop();
        }
        reverse(top3.begin(), top3.end());

        // Apply reduction rules
        if (top3[0] == "E" && top3[1] == "+" && top3[2] == "T") {
            st.push("E");
            return true;
        }
        if (top3[0] == "T" && top3[1] == "*" && top3[2] == "F") {
            st.push("T");
            return true;
        }

        // If no reduction happens, restore stack
        for (int i = 2; i >= 0; i--) {
            st.push(top3[i]);
        }
    }

    if (st.size() >= 1) {
        string top = st.top();
        if (top == "id") {
            st.pop();
            st.push("F");  // id → F
            return true;
        }
        if (top == "F") {
            st.pop();
            st.push("T");  // F → T
            return true;
        }
        if (top == "T") {
            st.pop();
            st.push("E");  // T → E
            return true;
        }
    }

    return false;  // No reduction possible
}

bool parse() {
    stack<string> st;
    int i = 0;

    while (i < inputTokens.size() || !st.empty()) {
        if (i < inputTokens.size()) {
            // Shift
            st.push(inputTokens[i]);
            cout << "Shift: " << inputTokens[i] << endl;
            i++;
        }

        // Reduce as much as possible
        while (reduce(st)) {
            cout << "Reduction performed" << endl;
        }

        // Check if stack contains only "E" and "$"
        if (st.size() == 2 && st.top() == "E") {
            st.pop();
            if (st.top() == "$") {
                return true;  // Parsing successful
            }
        }
    }

    return false;  // Parsing failed
}

int main() {
    if (parse()) {
        cout << "String is accepted by the parser!" << endl;
    } else {
        cout << "String is rejected by the parser!" << endl;
    }

    return 0;
}