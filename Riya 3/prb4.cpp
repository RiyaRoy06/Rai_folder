/*#include<bits/stdc++.h>
#define ll long long int
using namespace std;

enum State {
    Q0, Q1, Q2, Q3 
};

bool isAccepted(string str) {
    State current = Q0;
    
    for (char c : str) {
        switch (current) {
            case Q0:
                if (c == '0') current = Q1;
                else if (c == '1') current = Q2;
                else return false;
                break;
            case Q1:
                if (c == '0') current = Q0;
                else if (c == '1') current = Q3;
                else return false;
                break;
            case Q2:
                if (c == '0') current = Q3;
                else if (c == '1') current = Q0;
                else return false;
                break;
            case Q3:
                if (c == '0') current = Q2;
                else if (c == '1') current = Q1;
                else return false;
                break;
        }
    }
    
    return (current == Q0);
}

int main() {
    string input;
    
    cout << "Enter a string : ";
    cin >> input;
    for (char c : input) {
        if (c != '0' && c != '1') {
            cout << "Invalid input! Only 0's and 1's are allowed." << endl;
            return 1;
        }
    }
    
    if (isAccepted(input)) {
        cout << "String is ACCEPTED (has even number of 0's and even number of 1's)" << endl;
    } else {
        cout << "String is REJECTED" << endl;
    }
    
    return 0;
}*/
#include<bits/stdc++.h>
#define ll long long int
using namespace std;
int main()
{
   int t;
   cin>>t;
   while(t--)
   {
    string s;
    cin>>s;
    sort(s.begin(),s.end());
    cout<<s[0]<<endl;
   }
}