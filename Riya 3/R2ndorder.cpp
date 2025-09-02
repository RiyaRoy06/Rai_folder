#include <iostream>
#include <cmath>
using namespace std;
double f(double x, double y) {
return x * x + y; // Example: dy/dx = x^2 + y
}
int main() {
double x0 = 0, y0 = 1, x = 0.1;
double y1, y2;
int iteration = 4;
for (int i = 0; i < iteration; i++) {
y1 = y0 + x * (f(x0, y0)); // 1st iteration
y2 = y0 + x * (f(x0, y0) + f(x, y1)) / 2.0; // Improved
y0 = y2;
}
cout << " x = " << x << " is " << y0 <<
endl;
return 0;
}