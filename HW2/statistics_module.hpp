#ifndef STATISTICS_HPP__
#define STATISTICS_HPP__


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <variant>
#include <optional>
#include <unordered_map>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>  // For STL conversions
#include <pybind11/stl_bind.h>  // For STL bindings

namespace py = pybind11;


class CSVReader {



private:
    std::string input_file;
    std::string output_file;
    std::vector<std::vector<std::variant<double, std::string>>> data; // store data into a matrix
    std::vector<std::string> headers;
    
public:
    CSVReader() = default; // default constructor
    // std::string get_input_file() const { return input_file; } //getter method as an inline function 
    void parse_arguments(int argc, char* argv[]);
    void load_data();

    //helper functions to load data
    std::vector<std::string> split_line(const std::string& line);
    std::variant<double, std::string> cell_conversion(const std::string& field);
    std::vector<std::variant<double, std::string>> convert_line(const std::vector<std::string>& fields);

    //iterators for data traversal
    void print_row(size_t row_index) const;
    void print_column(size_t column_index) const;

    const std::vector<std::vector<std::variant<double, std::string>>>& get_data() const { return data; } // getter method to get data
    void print_data() const; //for debugging purposes

    std::vector<std::string> extract_string_column(size_t column_index) const;
    std::vector<double> extract_numerical_column(size_t column_index) const;

    // Statistical functions
    double calculate_mean(const std::vector<double>& values) const;
    double calculate_median(std::vector<double>& values) const;
    double calculate_variance(const std::vector<double>& values) const;
    double calculate_standard_deviation(const std::vector<double>& values) const;
    void generate_histogram(const std::vector<double>& values, const std::string& output_file, size_t bins) const;
    std::unordered_map<std::string, unsigned int> frequency_count(const std::vector<std::string>& values) const;

    void write_statistics_to_file(const std::string& output_file) const;

    py::object to_pandas() const;
};






#endif