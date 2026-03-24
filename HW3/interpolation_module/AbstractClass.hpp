#ifndef ABSTRACTCLASS_HPP
#define ABSTRACTCLASS_HPP

#include <iostream>
#include <vector>
#include <fstream> 
#include <sstream> 
#include <algorithm>  
#include <string>  
#include <stdexcept>  




class Interpolation {
protected: 
    //vectors sto store data points and filename if data are read from a file
    std::vector<double> x_values;
    std::vector<double> y_values;
    std::string filename; 
    //a and b are the limits of the interval [a,b] where the interpolation is defined, the minumum and maximum values of the x vector
    std::pair<double, double> extremes;    
    
public:
    //Constructor, a vector as input
    Interpolation(std::vector<double> x, std::vector<double> y, std::string filename="");  
        
    //Methods to retrieve information about the vectors and the file name. 
    inline int getDataSize() const { return x_values.size();}
    inline std::string getFilename() const { return filename;}
    inline std::pair<double,double> getExtremes() const { return extremes;}
    inline std::vector<double> getXValues() const { return x_values;}
    inline std::vector<double> getYValues() const { return y_values;}

    //utility method to print and check the x and y vectors (for verification) 
    void printVectors() const;

    //Virtual pure method for interpolation
    virtual double interpolate(double x) const = 0; 

    //Method to overload the operator () for a vector of x values
    std::vector<double> operator()(const std::vector<double> x_vector);
        
    //Virtual destructor
    virtual ~Interpolation() = default;  //the same as virtual ~Interpolation() {}, Since there are no resources that need special cleanup, the body of the destructor would be empty anyway. Opened files close automatically when ifstream goes out of scope. 

};








#endif



