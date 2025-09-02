#include <iostream>
#include <cmath>
using namespace std;
double f(double x) {
return x * x - 2; // Example: f(x) = x^2 - 2
}
double df(double x) {
return 2 * x; // Derivative: f'(x) = 2x
}
int main() {
double x = 1.0;
int maxIter = 100;
double tol = 1e-6;
for (int i = 0; i < maxIter; i++) {
double x_next = x - f(x) / df(x);
if (fabs(x_next - x) < tol) break;
x = x_next;
}
cout << "Root: " << x << endl;
return 0;
}