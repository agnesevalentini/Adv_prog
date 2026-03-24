
Agnese Valentini agnese.valentini@studenti.units.it



## Design choices - Statistics module
The implementation of the statistics module is a very basic one and it's done through a class called CSVReader, that reads a CSV file and performs statistical analysis on it.
The data is parsed from a CSV input file into a matrix structure, and then the columns are extracted and statistics is performed depending on the values that they store: for categorical variables, the count of the frequencies; for numerical variables, mean, median, variance, standard deviation and a histogram, leveragin the Boost.histogram third-party library; these are all together outputted to a file called stats.txt. The implementation has been tested on few Kaggle dataset, and we provided the Depression_Student_Dataset.csv as a test dataset, however the module accepts any CSV file of choice.




## CMake

To build the system a CMake file is provided. If there's already a build folder present for the CMake, the commands to run it are

```bash
cmake ..
make
```
and then 

```bash
python3 python_test.py
```

to run the test in Python.


## Additions with Python

To integrate the functionalities and allow the C++ library to be imported into a Python environment, a binding of the statistic_module methods is provided. This is done using pybind11, to allow Python users to deploy the functionalities of such C++ module.
The classification_operations.py file adds functionalities to the C++ statistical module by creating a Python class where a classification analysis is performed on the CSV file "Depression students dataset". Here, pandas is used to create a dataframe and sklearn is used for the random classifier, besides matplotlib is also imported to draw a sample histogram of the variable "Age". It is also possible to visualize the confusion matrix, roc curve and feature importance analysis.
An example of usage is provided in the python_test.py file, where both the methods from the C++ module and the Python ones are inserted.










