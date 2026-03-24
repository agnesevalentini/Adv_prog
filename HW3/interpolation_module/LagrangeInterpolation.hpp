#ifndef LAGRANGEINTERPOLATION_HPP
#define LAGRANGEINTERPOLATION_HPP



class LagrangeInterp: public Interpolation{
public:
    //constructor
    using Interpolation::Interpolation;

    //interpolation method
    double interpolate(double x) const override;
};



#endif