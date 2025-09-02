#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double f(double x, double y) {
    return x - y * y;  // dy/dx = x - y^2
}

int main() {
    const int m = 3;  
    const double h = 0.2;
    
    double x[m+1] = {0.0, 0.2, 0.4, 0.6};
    double y[m+1] = {0.0, 0.02, 0.0795, 0.1762};
    double f_vals[m+1];
    
    for (int i = 0; i <= m; i++) {
        f_vals[i] = f(x[i], y[i]);
    }
    
    // Milne's Predictor
    double y4_p = y[m-3] + (4*h/3) * (2*f_vals[m-2] - f_vals[m-1] + 2*f_vals[m]);
    double x4 = x[m] + h;
    double f4_p = f(x4, y4_p);
    
    // Milne's Corrector
    double y4_c = y[m-1] + (h/3) * (f_vals[m-1] + 4*f_vals[m] + f4_p);
    
    for (int iter = 0; iter < 3; iter++) {
        f4_p = f(x4, y4_c);
        y4_c = y[m-1] + (h/3) * (f_vals[m-1] + 4*f_vals[m] + f4_p);
    }
    
    cout << fixed << setprecision(6);
    cout << "Milne's Method Solution:\n";
    cout << "Predictor (y4_p): " << y4_p << endl;
    cout << "Corrector (y4_c): " << y4_c << endl;
    
    return 0;
}