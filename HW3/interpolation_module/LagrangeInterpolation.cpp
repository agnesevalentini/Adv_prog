#include "AbstractClass.hpp"
#include "LagrangeInterpolation.hpp"



//Lagrange interpolation method
double LagrangeInterp::interpolate(double x) const {

    //adaptation of an old code. We use the x_values and y_values vectors to interpolate the value of x.
    const std::vector<double>& x_used = x_values;
    const std::vector<double>& y_used = y_values;

    
    //we initialize the vector for the basis polynomials. We are not creating this vector as a data member because it changes whenever we ask for the interpolated value of a different x value
    std::vector<double> basis_polynomials(x_used.size(), 0.0);

        
    //NUMERATOR AND DENOMINATOR of Lagrange basis polynomial and basis polynomial VECTOR UPDATING. 
    for (size_t i = 0; i < x_used.size(); ++i) {
        double diff_xi = 1.0; //for numerator
        double diff_iJ = 1.0; //for denominator
        for (size_t j = 0; j < x_used.size(); ++j) {
            if (i != j) {
                diff_xi = diff_xi * (x - x_used[j]);
                diff_iJ = diff_iJ * (x_used[i] - x_used[j]);
            }
        }

        // Check and handle division by zero (whenever diff_ij is too small, means you have two x values that are either the same or too close to each other. to avoid division by zero, we set the basis polynomial to zero) 
        if (abs(diff_iJ) == 0) {
            basis_polynomials[i] = 0.0;
        } else {
            double basis_pol_scalar = diff_xi / diff_iJ;
            basis_polynomials[i] = basis_pol_scalar;
        }
    }

        //linear combination of the y values and the basis polynomials
        double y = 0.0;
        for (size_t i = 0; i < y_used.size(); ++i) {
            y += y_used[i] * basis_polynomials[i];
        }
        return y;
};    
    
