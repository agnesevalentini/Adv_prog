#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>
#include <variant>
#include <iterator>
#include <unordered_map>
#include <optional>
#include <ranges>
#include <string>
#include <cmath> // For sqrt
#include <algorithm> // for sort
#include <limits> // For handling invalid numbers
#include <algorithm> 
#include <boost/histogram.hpp> // including the histogram library
#include <boost/histogram/axis.hpp> //for axis options

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>  // For STL conversions
#include <pybind11/stl_bind.h>  // For STL bindings
#include "statistics_module.hpp"


// namespace for binding using pybind1
namespace py = pybind11;


// binding for the statistics module
PYBIND11_MODULE(statistics_module, m) {

    m.doc() = "Python bindings for CSVReader class in statistics_module";

    // bind the class CSVReader
    py::class_<CSVReader>(m, "CSVReader")
        .def(py::init<>())  // default constructor binding

        // binding for parse_arguments
        .def("parse_arguments", [](CSVReader& self, const std::vector<std::string>& args) {
            std::vector<char*> argv;  // vector of char pointers
            argv.reserve(args.size()); // preallocate memory for argv vector
            for (const auto& arg : args) {  
                argv.push_back(const_cast<char*>(arg.c_str())); // push back the char pointer to the vector
            }
            self.parse_arguments(static_cast<int>(args.size()), argv.data()); // call the parse_arguments method with the arguments converted
        }, "Parse command line arguments")

        
        // binding for cell_conversion (conversion of each cell in the CSV file in a std::variant)
        .def("cell_conversion", [](CSVReader& self, const std::string& cell) {
            auto result = self.cell_conversion(cell);
            return std::visit([](auto&& arg) -> py::object {  // std::visit used to handle the variant type
                return py::cast(arg); // Convert the variant type to a Python object
            }, result); 
        }, "Convert a cell string to either double or string")


        // binding for convert_line (conversion of each line of the CSV file in a row of variants)
        .def("convert_line", [](CSVReader& self, const std::vector<std::string>& row_str) {
            auto result = self.convert_line(row_str);
            std::vector<py::object> python_result; // defining a vector of Python objects
            for (const auto& item : result) {
                python_result.push_back(std::visit([](auto&& arg) -> py::object { // using again std::visit to handle the variant type
                    return py::cast(arg); // Convert each variant element to Python
                }, item));
            }
            return python_result;
        }, "Convert a row of strings to a row of variants")

       

        // binding for load_data
        .def("load_data", &CSVReader::load_data, "Load data from the CSV file")

        // binding for  get_data to expose the loaded data
        .def("get_data", [](CSVReader& self) {
            const auto& data = self.get_data(); 
            std::vector<std::vector<py::object>> python_data; // matrix structure to store the data
            for (const auto& row : data) {
                std::vector<py::object> python_row;
                for (const auto& cell : row) {
                    python_row.push_back(std::visit([](auto&& arg) -> py::object { // populating the matrix with the data converted to Python objects
                        return py::cast(arg); // Convert each cell to Python
                    }, cell));
                }
                python_data.push_back(python_row);
            }
            return python_data;
        }, "Get the loaded data matrix")

        // bindings for all the other methods in the class CSVReader (the ones that don't require any conversion)
        .def("split_line", &CSVReader::split_line, "Split a line into cells")

        .def("print_row", &CSVReader::print_row, "Print a specific row")

        .def("print_column", &CSVReader::print_column, "Print a specific column")

        .def("print_data", &CSVReader::print_data, "Print all loaded data")

        .def("extract_numerical_column", &CSVReader::extract_numerical_column, "Extract a column of numerical values")

        .def("extract_string_column", &CSVReader::extract_string_column, "Extract a column of string values")

        .def("calculate_mean", &CSVReader::calculate_mean, "Calculate the mean of a vector of values")

        .def("calculate_median", &CSVReader::calculate_median, "Calculate the median of a vector of values")

        .def("calculate_variance", &CSVReader::calculate_variance, "Calculate the variance of a vector of values")

        .def("calculate_standard_deviation", &CSVReader::calculate_standard_deviation, "Calculate the standard deviation of a vector of values")

        .def("generate_histogram", &CSVReader::generate_histogram, 
            py::arg("values"), py::arg("output_file"), py::arg("bins") = 0,
            "Generate a histogram for numerical values")

        .def("frequency_count", &CSVReader::frequency_count, "Calculate the frequency count of string values")

        .def("write_statistics_to_file", &CSVReader::write_statistics_to_file, "Write statistics to a file")
        .def("to_pandas", &CSVReader::to_pandas, "Convert data to a pandas DataFrame");


}

