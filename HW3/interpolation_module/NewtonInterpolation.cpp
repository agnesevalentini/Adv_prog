#include "AbstractClass.hpp"
#include "NewtonInterpolation.hpp"
#include <iostream>
#include <vector>
#include <gsl/gsl_poly.h>


//Newton interpolation method
double NewtonInterpolation::interpolate(double x) const {

    //adaptation of an old code. We use the x_values and y_values vectors to interpolate the value of x.
    const std::vector<double>& x_used = x_values;
    const std::vector<double>& y_used = y_values;

    //we initialize the vector for the divided differences. 
    int size = x_used.size();     
    std::vector<double> dd(size); 
    
    //GLS imported method to calculate the divided differences 
    gsl_poly_dd_init(dd.data(), x_used.data(), y_used.data(), size);    //gsl_poly_dd_init(double dd[], const double x[], const double y[], size_t size). This notation dd[] refers to an array. data is a method for std:.vector that returns a pointer to the first element of the array used to store the vector elements.

    //GLS imported method to evaluate the polynomial at the point x
    double y = gsl_poly_dd_eval(dd.data(), x_used.data(), size, x);
    return y;       
    
}













