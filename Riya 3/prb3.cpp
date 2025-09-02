#include<bits/stdc++.h>
#define ll long long int
using namespace std;
map<char, int> opPrecedence = {
    {'$', 0},{'+', 1},{'-', 1},{'*', 2},{'/', 2}
};

int compute(int x, int y, char operation) {
    switch(operation) {
        case '+': return x + y;
        case '-': return x - y;
        case '*': return x * y;
        case '/': return x / y;
        default: return 0;
    }
}

void displayStack(stack<char> s) {
    cout << "$";
    stack<char> tempStack;
    while (!s.empty()) {
        if (s.top() != '$') {
            tempStack.push(s.top());
        }
        s.pop();
    }
    while (!tempStack.empty()) {
        cout << "<" << tempStack.top() << ">";
        tempStack.pop();
    }
    cout << "$" << endl;
}

int calculate(string expression) {
    stack<int> numbers;
    stack<char> operators;
    
    operators.push('$');
    
    cout << "$";
    for (char ch : expression) {
        if (isdigit(ch)) {
            cout << "<" << ch << ">";
        } else {
            cout << ch;
        }
    }
    cout << "$" << endl;
    
    int pos = 0;
    while (pos < expression.length()) {
        char current = expression[pos];
        
        if (current == ' ') {
            pos++;
            continue;
        }
        
        if (isdigit(current)) {
            numbers.push(current - '0');
            pos++;
        } else {
            while (!operators.empty() && opPrecedence[operators.top()] >= opPrecedence[current]) {
                displayStack(operators);
                
                char op = operators.top();
                operators.pop();
                
                int num2 = numbers.top();
                numbers.pop();
                int num1 = numbers.top();
                numbers.pop();
                
                numbers.push(compute(num1, num2, op));
            }
            operators.push(current);
            pos++;
        }
    }
    
    if (operators.size() > 1) {
        displayStack(operators);
    }
    
    while (operators.top() != '$') {
        char op = operators.top();
        operators.pop();
        
        int num2 = numbers.top();
        numbers.pop();
        int num1 = numbers.top();
        numbers.pop();
        
        numbers.push(compute(num1, num2, op));
        
        if (operators.top() != '$') {
            displayStack(operators);
        }
    }
    
    return numbers.top();
}

int main() {
    string inputExpr;
    cout << "Enter the expression: ";
    getline(cin, inputExpr);
    
    int output = calculate(inputExpr);
    cout << "Value = " << output << endl;
    
    return 0;
}