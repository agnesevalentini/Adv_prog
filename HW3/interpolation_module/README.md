# MODULE 2 - Interpolation module 
#### Marta Invernici marta.invernici@studenti.units.it


## Project organization 
### C++ module 
#### Files
For each of the following a source and a header file:
* AbstractClass: code for the common Interpolation interface;
* LinearInterpolation: linear interpolation method. Author's development, Wikipedia reference https://en.wikipedia.org/wiki/Linear_interpolation.
* LagrangeInterpolation: polynomial interpolation method implementing the Lagrange algorithm. Author's development, wikipedia reference: https://en.wikipedia.org/wiki/Lagrange_polynomial.
* NewtonInterpolation: polynomial interpolation method implementing the Newton algorithm of divided differences. Implemented with GNU GSL gsl-2.8 library imported functions.

#### Design choices
The Interpolation_module has its core in the abstract class Interpolation, which serves as a common interface for various interpolation methods. The class manages the following key data:

* Two ordered vectors of x and y values, which can either be loaded from a CSV file or provided manually.
* The filename of the CSV file, if the data is loaded from one.
* The boundaries of the x-interval (the domain of the data).

Constructors and Methods

The class offers two constructors to instantiate objects: by loading data from a CSV file; by manually passing vectors of data.

Key functionalities include:

* Getter methods to retrieve information about the stored vectors.
* A utility function to print the original data vectors for a visual check.
* A pure virtual method interpolate, which is overridden by derived classes to implement specific interpolation algorithms.
* An overload of the call operator (), allowing computation of interpolated y values for either a single x or a vector of x values.

#### Code overall organization
The code is organized in a modular way to enhance readability and efficiency. Modern C++ features are leveraged, such as: Object-oriented programming (OOP) and inheritance; Standard library containers and iterators; the GNU Scientific Library (GSL) for implementing the Newton interpolation method, avoiding the need for a trivial implementation of a slightly more complex technique.

Although B-spline interpolation could not be implemented due to time constraints, the GSL library provides convenient functions for future development (see "42.10 Interpolation with B-splines" in the GNU reference manual).

### C++ binding 
* pybind11.cpp: Python bindings of the C++ module classes, using pybind11 library

### Python and Test 
* python_test_interp.py: python file to test python-c++ bindings properly works and to demostrate the use of the toolbox in a real-world scenario.  
* PythonFunctions.py: definitions of functions called in python_test_interp.py. 
  * read_data(file_path). Read the data from file and generate a dataframe.
  * int_preprocessing(df=dataframe, x=label of x values column(string), y=label of y values column(string), duplicates_handling='min' or 'max' or 'mean'(handle duplicates keeping the min, mex, the mean of y values)). Creates a preprocessed copy of df. 
  * df_to_array (df=dataframe, column=column index). Turn a pandas dataframe column into a numpy array, to later exploit pybind built-in type conversion between C++ and Python.
  * plot_interpolations(x=original x values vector, y=original y values vector, vector=vector of x values to interpolate, y_interp=vector of interpolated y, title, label, linestyle, marker, markersize). Create a plot with the scatterplot of original values and the interpolated function.
  

### Other files
* README.md
* data.csv: Part of the Hubble_data dataset downloaded from https://www.kaggle.com/datasets/isaacramalho/hubble-data. The two columns saved collect; v= galaxies recession velocities, and  r = proper distances (r). Here serves just as a sample dataset. 
* CMakeLists.txt: CMake file to automate the building of the python Interpolation module.

## How to compile
### Dependencies
* GNU GSL library (https://ftp.gnu.org/gnu/gsl/gsl-latest.tar.gzand). Download, compilation and installation in the defaul paths (Unix: /usr/local). From inside the directory where it has been downloaded use this commands:

```bash
wget https://ftp.gnu.org/gnu/gsl/gsl-latest.tar.gz

tar -xzvf gsl-latest.tar.gz

cd gsl-<version>

cd /path/to/downloadedlibrary

./configure && make && sudo make install
```
* pybind11 
* Dependencies of python_test_interp.py, libraries to be installed:
  * pybind11
  * pandas
  * matplotlib
  * numpy
 
If using Conda:
```bash
conda create --name new_environment
conda activate new_environment
conda install pybind11 pandas matplotlib numpy
```

### Building the Interpolation module and running python_test_interp.py
* Compile the c++ toolbox in a python module using CMake, from the CMakeLists.txt file directory :
```bash
mkdir build && cd build
cmake ..
make
```

* Before running, make sure the python module is discoverable by setting
```bash
export PYTHONPATH=path/to/build/folder:$PYTHONPATH
```

* Run the python_test_interp.py test file 
```bash
python3 python_test_interp.py
```






















