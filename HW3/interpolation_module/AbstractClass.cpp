#include "AbstractClass.hpp"
#include "LinearInterpolation.hpp"
#include "LagrangeInterpolation.hpp"
#include "NewtonInterpolation.hpp"

#include <iostream>
#include <vector>
#include <fstream> 
#include <sstream> 
#include <algorithm>  
#include <string>  
#include <stdexcept> 



//Constructor, a vector as input
Interpolation::Interpolation(std::vector<double> x, std::vector<double> y, std::string filename) : x_values(x), y_values(y), filename(filename) {
    //ordering the vectors to allow interpolation afterwards
    for (size_t i = 0; i < x_values.size(); ++i) {
        for (size_t j = 0; j < x_values.size(); ++j) {
            try{
            if (x_values[i] < x_values[j]) {
                std::swap(x_values[i], x_values[j]);  //swap is a method of std::vector container
                std::swap(y_values[i], y_values[j]);
            } else if (x_values[i]==x_values[j] && i!=j) {
                throw std::runtime_error("Duplicated values in the x column of the dataset. The program cannot handle this situation. Please preprocess the data.");
            }
            } catch (std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        } 
    }

    //check the vectors are not empty
    try{
    if (x_values.empty() || y_values.empty()) {
        throw std::runtime_error("No data. Impossible to perform interpolation");
    }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    //set the extremes of the interval [a,b] where the interpolation is defined
    extremes.first = x_values.front();
    extremes.second = x_values.back();

}



//utility method to print and check the x and y vectors (for verification)
void Interpolation::printVectors () const {
    std::cout << "x values: ";
    for (const auto& val : x_values) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "y values: ";
    for (const auto& val : y_values) {
        std::cout << val << " ";
    }
    std::cout << std::endl;  
}



//Method to overload the operator () for a vector of x values
std::vector<double> Interpolation::operator()(const std::vector<double> x_vector) {
    std::vector<double> Interp_y_vector;
    for (size_t i = 0; i < x_vector.size(); ++i) {
        double value = interpolate(x_vector[i]);
        Interp_y_vector.push_back(value);
    }
    return Interp_y_vector;
}









    
