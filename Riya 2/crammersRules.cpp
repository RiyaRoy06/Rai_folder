#include <iostream>
#include <iomanip>
using namespace std;

float determinant(float mat[3][3]) {
    float det = 0;
    
    det = mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2])
        - mat[0][1] * (mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2])
        + mat[0][2] * (mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]);
    
    return det;
}

int main() {
    const int n = 3;
    float coeff[n][n] = {
        {3, 1, 2},
        {2, -3, -1},
        {1, 2, 1}
    };
    float constants[n] = {3, -3, 4};
    
    float detA = determinant(coeff);
    
    if (detA == 0) {
        cout << "The system has no unique solution (determinant is zero)." << endl;
        return 0;
    }
    
    float solutions[n];
    
    
    for (int col = 0; col < n; col++) {
        float temp[n][n];
        
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                temp[i][j] = coeff[i][j];
            }
        }
        
        
        for (int row = 0; row < n; row++) {
            temp[row][col] = constants[row];
        }
        
        float det = determinant(temp);
        
        solutions[col] = det / detA;
    }
    
    cout << "Solutions using Cramer's Rule:\n";
    for (int i = 0; i < n; i++) {
        cout << "x" << i+1 << " = " << solutions[i] << endl;
    }
    
    return 0;
}