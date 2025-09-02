#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    const int n = 3;
    const int max_iterations = 50;
    const float tolerance = 1e-6;
    
    float a[n][n+1] = {
        {28, 4, -1, 32},    
        {2, 17, 4, 35},    
        {1, 3, 10, 24}     
    };
    
    float x[n] = {0};      
    float x_new[n];        
    int iteration = 0;
    float error;
    
    cout << "Gauss-Seidal Method Solution\n";
    cout << "Iteration\tx\t\ty\t\tz\t\tError\n";
    cout << fixed << setprecision(6);
    
    do {
        error = 0;
        
        
        x_new[0] = (a[0][3] - a[0][1]*x[1] - a[0][2]*x[2]) / a[0][0];
        x_new[1] = (a[1][3] - a[1][0]*x[0] - a[1][2]*x[2]) / a[1][1];
        x_new[2] = (a[2][3] - a[2][0]*x[0] - a[2][1]*x[1]) / a[2][2];
        
        
        for (int i = 0; i < n; i++) {
            error = max(error, fabs(x_new[i] - x[i]));
            x[i] = x_new[i]; 
        }
        
        cout << iteration << "\t\t" << x[0] << "\t" << x[1] << "\t" << x[2] << "\t" << error << endl;
        
        iteration++;
        
    } while (error > tolerance && iteration < max_iterations);
    
    cout << "\nFinal Solutions:\n";
    cout << "x = " << x[0] << endl;
    cout << "y = " << x[1] << endl;
    cout << "z = " << x[2] << endl;
    
    return 0;
}