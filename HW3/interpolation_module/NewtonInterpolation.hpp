#ifndef NEWTONINTERPOLATION_HPP
#define NEWTONINTERPOLATION_HPP



class NewtonInterpolation : public Interpolation {
public: 
    //constructor
    using Interpolation::Interpolation;   

    //Newton interpolation method
    double interpolate(double x) const override;
};





#endif



 
