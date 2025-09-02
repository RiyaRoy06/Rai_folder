#include <iostream>
using namespace std;
double f(double x, double y) {
return x + y; // Example: dy/dx = x + y
}
int main() {
double x0 = 0, y0 = 1, h = 0.1;
double xn = 0.5;
while (x0 < xn) {
y0 = y0 + h * f(x0, y0);
x0 = x0 + h;
}
cout << "Approximate solution at x = " << xn << " is " << y0 <<
endl;
return 0;
}
