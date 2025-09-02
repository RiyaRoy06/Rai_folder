#include<bits/stdc++.h>
#define ll long long int
using namespace std;

enum State {
    Q0, Q1, Q2, Q3 
};

bool isDivisibleBy4(string str) {
    State current = Q0;
    
    for (char c : str) {
        switch (current) {
            case Q0:
                if (c == '0') current = Q0;
                else if (c == '1') current = Q1;
                else return false; 
                break;
            case Q1:
                if (c == '0') current = Q2;
                else if (c == '1') current = Q3;
                else return false;
                break;
            case Q2:
                if (c == '0') current = Q0;
                else if (c == '1') current = Q1;
                else return false;
                break;
            case Q3:
                if (c == '0') current = Q2;
                else if (c == '1') current = Q3;
                else return false;
                break;
        }
    }
    
    return (current == Q0);
}

int main() {
    string input;
    
    cout << "Enter a binary string (0's and 1's): ";
    cin >> input;

    for (char c : input) {
        if (c != '0' && c != '1') {
            cout << "Invalid input! Only 0's and 1's are allowed\n";
            return 1;
        }
    }
    
    if (input.empty()) {
        cout << "Empty string is considered 0 (divisible by 4)\n";
        return 0;
    }
    
    if (isDivisibleBy4(input)) {
        cout << "String is ACCEPTED (divisible by 4)\n";
    } else {
        cout << "String is REJECTED (not divisible by 4)\n";
    }
    
    return 0;
}