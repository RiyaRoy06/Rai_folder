#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double f(double x, double y) {
    return x + y*y;  // Example: dy/dx = x + y²
}

double picard_iteration(double x0, double y0, double x, int iterations) {
    double y = y0;  
    
    for (int i = 0; i < iterations; ++i) {
        int n = 100;  // Number of integration steps
        double h = (x - x0)/n;
        double sum = 0.0;
        
        for (int j = 0; j <= n; ++j) {
            double xi = x0 + j*h;
            double term = f(xi, y);

            if (j == 0 || j == n) {
                sum += 0.5 * term;
            } else {
                sum += term;
            }
        }
        
        y = y0 + h * sum;  
    }
    
    return y;
}

int main() {
    double x0 = 0.0, y0 = 0.0;  // Initial condition
    double x = 0.5;              
    int iterations = 5;           
    
    cout << fixed << setprecision(6);
    cout << "Solving dy/dx = x - y^2, y(0) = 0 using Picard's method:\n";
    
    for (int i = 1; i <= iterations; ++i) {
        double y = picard_iteration(x0, y0, x, i);
        cout << "Iteration " << i << ": y(" << x << ") = " << y << endl;
    }
    
    return 0;
}