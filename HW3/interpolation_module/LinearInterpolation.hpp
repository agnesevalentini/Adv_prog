#ifndef LINEARINTERPOLATION_HPP
#define LINEARINTERPOLATION_HPP


class LinearInterpolation: public Interpolation{
public:
    //Constructor defined in the AbstractClass.hpp
    using Interpolation::Interpolation;

    //Method to linearly interpolate the values of x
    double interpolate(double x) const override;
};



#endif