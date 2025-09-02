#include <iostream>
#include <cmath>
using namespace std;
double f(double x) {
return x * x * x * x + 2 * x * x * x - x - 1; // Example: f(x) = x^4 + 2x^3 - x - 1
}
int main() {
double a = 0, b = 1, c;
int maxIter = 100;
double tol = 1e-6;
if (f(a) * f(b) >= 0) {
cout << "Invalid interval!" << endl;
return 0;
}
for (int i = 0; i < maxIter; i++) {
c = (a+b)/2;
if (fabs(f(c)) < tol) break;
if (f(a) * f(c) < 0)
b = c;
else
a = c;
}
cout << "Root: " << c << endl;
return 0;
}