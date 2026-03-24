#include "AbstractClass.hpp"
#include "LinearInterpolation.hpp"




//Method to linearly interpolate the values of x
double LinearInterpolation::interpolate(double x) const {

    //adaptation of an old code. We use the x_values and y_values vectors to interpolate the value of x.
    const std::vector<double>& x_used = x_values;
    const std::vector<double>& y_used = y_values;

    // Find the interval where x is located
    auto it = std::lower_bound(x_used.begin(), x_used.end(), x);
    if (it == x_used.end()) {
        return y_used.back();
    }
    if (it == x_used.begin()) {
        return y_used.front();
    }

    // Get the indices of the interval
    size_t idx = std::distance(x_used.begin(), it);
    double x0 = x_used[idx - 1];
    double x1 = x_used[idx];
    double y0 = y_used[idx - 1];
    double y1 = y_used[idx];

    // Linear interpolation
    return y0 + (x - x0) * (y1 - y0) / (x1 - x0);

} 

