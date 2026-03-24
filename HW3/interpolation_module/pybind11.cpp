#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <gsl/gsl_poly.h>

#include "AbstractClass.hpp"
#include "LinearInterpolation.hpp"
#include "LagrangeInterpolation.hpp"
#include "NewtonInterpolation.hpp"

#include <iostream>
#include <vector>


namespace py = pybind11;


PYBIND11_MODULE(Interpolation, m) {
    m.doc() = "Interpolation module";

    py::class_<Interpolation>(m, "Interpolation")
        //constructor: 
        //n C++, non è possibile creare un'istanza di una classe astratta direttamente. Una classe è considerata astratta se ha almeno un metodo virtuale puro (un metodo dichiarato con = 0). Devi esporre una classe concreta (non astratta) che deriva dalla classe astratta Interpolation.Esposizione con Pybind11: Esponi la classe astratta Interpolation per permettere l'uso dei suoi metodi e attributi. Esponi la classe concreta LinearInterpolation per permettere la creazione di istanze e l'uso del metodo interpolate. 
        // .def(py::init <const std::vector<double>, const std::vector<double>, const std::string>())

        //Quando costruisci un oggetto di una classe C++ in Python utilizzando Pybind11, i valori dei parametri passati al costruttore vengono automaticamente assegnati agli attributi della classe C++ se il costruttore è esposto correttamente. Tuttavia, per accedere e modificare gli attributi della classe C++ dal codice Python dopo la creazione dell'oggetto, è necessario esporre questi attributi utilizzando Pybind11.

        //getters and other methods
        .def_property_readonly("getDataSize", &Interpolation::getDataSize)
        .def_property_readonly("getFilename", &Interpolation::getFilename)
        .def_property_readonly("getExtremes", &Interpolation::getExtremes)
        .def_property_readonly("getXValues", &Interpolation::getXValues)
        .def_property_readonly("getYValues", &Interpolation::getYValues)
        .def("__call__", &Interpolation::operator()) //magic method __call__ to use the object as a function
        .def("printVectors", &Interpolation::printVectors); 



    //derived class: linear interpolation
    py::class_<LinearInterpolation, Interpolation> (m,"LinearInterpolation")
    //constructor
        .def(py::init <std::vector<double>, std::vector<double>, std::string>()) //serve il costruttore se è uguale a quello della classe astratta?
        .def("interpolate", &LinearInterpolation::interpolate);


    //derived class: lagrange interpolation
    py::class_<LagrangeInterp , Interpolation> (m,"LagrangeInterpolation")
    //constructor
        .def(py::init <std::vector<double>, std::vector<double>, std::string>()) //serve il costruttore se è uguale a quello della classe astratta?
        .def("interpolate", &LagrangeInterp::interpolate);

    //derived class: newton interpolation
    py::class_<NewtonInterpolation, Interpolation> (m,"NewtonInterpolation")
    //constructor
        .def(py::init <std::vector<double>, std::vector<double>, std::string>()) //serve il costruttore se è uguale a quello della classe astratta?
        .def("interpolate", &NewtonInterpolation::interpolate);







    //abbiamo saltato nella Abtract Class: il primo costructor che voglio eliminare; il metodo chooseNodes e clearNodes;
}


















