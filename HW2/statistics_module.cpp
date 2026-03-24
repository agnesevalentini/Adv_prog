#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>
#include <variant>
#include <stdexcept>
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

namespace py = pybind11;

// CSVReader::CSVReader(const std::string& input_file) : input_file(input_file) {}

// getter method for the input file is an inline function in the header

    // function to parse input as command line argument
    void CSVReader::parse_arguments(int argc, char* argv[]) {
        if (argc != 2) { // check if the number of arguments is correct
            std::cerr << "Usage: " << argv[0] << " <input_csv_file>" << std::endl; // sends the error message to the std error stream
            exit(EXIT_FAILURE); // exit if the arguments are invalid
        }
        input_file = argv[1]; //the input file is the second element passed 
    }

  
    std::vector<std::string> CSVReader::split_line(const std::string& line) {
        std::vector<std::string> row_str;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            // the following code to remove trailing and leading spaces is adapted from
            // https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
            // this command erases all characters that are spaces at the beginning of the cell: it erases from cell.begin() to the iterator pointing to the first element that is not a space, founded by find_if
            cell.erase(cell.begin(), std::find_if(cell.begin(), cell.end(), [](unsigned char c) { return !std::isspace(c); }));
            // this command erases all characters that are spaces at the end of the cell: it erases from an iterator pointing to the last element that is not a space, finded by find_if, to cell.end()
            // reverse iterators are used to traverse the cell in reverse, starting from the end and then finding the corresponding normal iterators using the .base() function
            cell.erase(std::find_if(cell.rbegin(), cell.rend(), [](unsigned char c) { return !std::isspace(c); }).base(), cell.end());
            row_str.push_back(cell);
        }
        return row_str;
    }

    // helper function to convert a string into a double
    std::variant<double, std::string> CSVReader::cell_conversion(const std::string& cell) {
    try { // We try to convert the string to a double, but if the string is not completely processed we return the string itself
        std::size_t pos;
        double value = std::stod(cell, &pos); // Get the position of the first non-numeric character
        if (pos != cell.length()) {
            // Not the entire string was processed, treat it as a string
            return cell;
        }
        return value; // Entire string was processed as a valid double
    } catch (...) {
        // Handle any exception by treating it as a string
        return cell;
        }
    }

    // helper function to convert the whole row_str into a row of variant
    std::vector<std::variant<double, std::string>> CSVReader::convert_line(const std::vector<std::string>& row_str) {
        std::vector<std::variant<double, std::string>> row; 
        for (const auto& cell : row_str) { 
            row.push_back(cell_conversion(cell));
        }
        return row;
    }



    // function that populates the data matrix
    void CSVReader::load_data() {
        std::ifstream file(input_file); // Open the input file
        if (!file.is_open()) { //checks if the file is open
            std::cerr << "Error opening file: " << input_file << std::endl;
            return;
        }
        // Read lines from the file
        std::string line;

        if (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string cell;
            while (std::getline(ss, cell, ',')) {
                headers.push_back(cell);
            }
        }

        while (std::getline(file, line)) { // get the line from the file

            std::vector<std::string> row_str = split_line(line); // parse the line into row_str
            std::vector<std::variant<double, std::string>> row = convert_line(row_str); //convert row_str to a row of variants
            data.push_back(row);  // add the row to the data matrix
        }

        file.close(); // at the end of the loading, close the file
    }


    //iterators for data traversal
    //function to print a single row
    void CSVReader::print_row(size_t row_index) const {
        if (row_index >= data.size()) {  // check if the index is in range
            std::cerr << "Row index out of bounds." << std::endl;
            return;
        }
        const auto& row = data[row_index];
        for (const auto& cell : row) {
            std::visit([](auto&& value) { std::cout << value << " "; }, cell);
        }
        std::cout << std::endl;
    }

    //function to print a single column
    void CSVReader::print_column(size_t column_index) const {
        for (const auto& row : data) {
            if (column_index < row.size()) {
                std::visit([](auto&& value) { std::cout << value << " "; }, row[column_index]);
            } else {
                std::cout << "N/A "; // If the column doesn't exist in the row
            }
        }
        std::cout << std::endl;
    }





    // a print function for debugging purposes:
    void CSVReader::print_data() const {
        for (const auto& row : data) {
            for (const auto& cell : row) {
                std::visit([](auto&& value) { std::cout << value << " "; }, cell);  //using std::visit to print a variant variable
            }
            std::cout << std::endl;
        }
    }


    //a function that extracts the numerical data to perform statistical operations on the column
    std::vector<double> CSVReader::extract_numerical_column(size_t column_index) const {
        std::vector<double> column;
        // the following syntax for the for cycle skipping the first element is from
        //  https://stackoverflow.com/questions/25652505/how-can-i-skip-the-first-iteration-of-range-based-for-loops
        for (const auto& row : data | std::views::drop(1)) { // iterator on the row elements, skipping the first line
            if (column_index < row.size()) { 
                std::visit([&column](auto&& value) {
                    if constexpr (std::is_same_v<std::decay_t<decltype(value)>, double>) { // compile-time check if the value is a double, compile with -std=c++17
                        column.push_back(value); // Add only numeric values
                    }
                }, row[column_index]);
            }
        }
        /*column print function for debugging purposes
        std::cout << "Extracted column: ";
        for (const auto& value : column) {
            std::cout << value << " "; 
        }
        std::cout << std::endl; */
        return column;

        

    }

    // function to extract a column of strings to perform frequency analysis, similar code as previous function
    std::vector<std::string> CSVReader::extract_string_column(size_t column_index) const {
        std::vector<std::string> column;
        // the following syntax for the for cycle skipping the first element is from
        //  https://stackoverflow.com/questions/25652505/how-can-i-skip-the-first-iteration-of-range-based-for-loops
        for (auto& row : data | std::views::drop(1)) { // iterator on the row elements, skipping the first line
            if (column_index < row.size()) { 
                std::visit([&column](auto&& value) {
                    if constexpr (std::is_same_v<std::decay_t<decltype(value)>, std::string>) { // compile-time check if the value is a string, compile with -std=c++17
                        column.push_back(value); // Add only string values
                    }
                }, row[column_index]);
            }
        }

        /* column print function for debugging purposes
        std::cout << "Extracted column: ";
        for (const auto& value : column) std::cout << value << " "; 
            std::cout << std::endl; */
        return column; 
    
    }





        
    /// Statistical functions: focus on numerical data only
    //mean
    double CSVReader::calculate_mean(const std::vector<double>& values) const {
        if (values.empty()) return 0.0; // Handle empty case
        double sum = std::accumulate(values.begin(), values.end(), 0.0); //using accumulate to calculate the sum
        return sum / values.size();
    }

    //median
    double CSVReader::calculate_median(std::vector<double>& values) const {
        if (values.empty()) return 0.0; // Handle empty case

        std::sort(values.begin(), values.end()); //using iterators with sort

        //in this case, we didn't use the version with iterators because 
        //it's more verbose and less straightforward than just using indices in std::vector
        size_t size = values.size();
        if (size % 2 == 0) {
            return (values[size / 2 - 1] + values[size / 2]) / 2.0; // if the number of values is odd, perform the mean between the two values in the middle
        } else {
            return values[size / 2];
        }
    }
    
    //variance
    double CSVReader::calculate_variance(const std::vector<double>& values) const {
        if (values.size() <= 1) return 0.0; // Handle cases with 0 or 1 value

        double mean = calculate_mean(values);
        double sum = 0.0;

        // Using iterators to loop through the vector of values
        for(const auto& it : values) {
            sum += (it - mean) * (it - mean); 
        }

        return sum / (values.size()); // Sample variance

    }
    
    // standard deviation
    double CSVReader::calculate_standard_deviation(const std::vector<double>& values) const {
        return std::sqrt(calculate_variance(values));

    }

    
    // function to generate the histogram for numerical variables
    void CSVReader::generate_histogram(const std::vector<double>& values, const std::string& output_file, size_t bins = 0) const {
        

        // Determine number of bins dynamically if not provided
        if (bins == 0) {
            bins = std::max(static_cast<size_t>(std::sqrt(values.size())), 4UL); // At least 4 bins
        }

        // Define histogram with bins and range (added an epsilon to ensure that the maximum value is included in the last bin, since Boost uses half-open intervals)
        auto hist = boost::histogram::make_histogram(boost::histogram::axis::regular<>(bins, *std::min_element(values.begin(), values.end()), *std::max_element(values.begin(), values.end())+0.1));
        
        // Fill the histogram with data
        for (const auto& value : values) {
            hist(value);
        }

        // Write histogram data to file
        std::ofstream output(output_file, std::ios::app); // Append mode
        if (!output.is_open()) {
            std::cerr << "Error opening histogram file: " << output_file << std::endl;
            return;
        }

        //this is to print the histogram
        output << "Histogram of numerical variables (bins and frequencies):" << std::endl;
        for (auto&& bin : indexed(hist)) {
            output << "Bin " << bin.index() << ": Range [" 
                << bin.bin().lower() << ", " << bin.bin().upper() 
                << "] - Count: " << *bin << std::endl;
        }
        output.close();
        // std::cout << "Histogram written to: " << output_file << std::endl;   for debugging purposes

        /* for debugging purposes: to check bin ranges
        std::cout << "Bin Ranges:" << std::endl;
        for (auto&& bin : boost::histogram::indexed(hist)) {
            std::cout << "Range [" << bin.bin().lower() << ", " << bin.bin().upper() << "]" << std::endl;
        } */
    
    }

    // Function that computes the frequency count for the string columns
    std::unordered_map<std::string, unsigned int> CSVReader::frequency_count(const std::vector<std::string>& values) const {
        
        std::unordered_map<std::string, unsigned int> frequency_map;
        for (auto value : values) { //populate the frequency map
            frequency_map[value]++;
        }
        return frequency_map;

    }
    
    
    void CSVReader::write_statistics_to_file(const std::string& output_file) const {
        // creates an output file stream and opens the file;
        // If the file doesn't exist, it will be created; if it exists, it will be overwritten
        std::ofstream output;
        output.open(output_file, std::ios::out); // Open the file in out mode to overwrite what is written
        if (!output.is_open()) { // check if the file is open
                std::cerr << "Error opening output file: " << output_file << std::endl;
                return;
            }
        output << "Statistical analysis for the CSV file" << std::endl << "--------------------" << std::endl;
        output.close();

        size_t number_of_columns = headers.size();
        for(size_t column_index = 0; column_index < number_of_columns; column_index++) {

            output.open(output_file, std::ios::app); // append to the file the analysis for the new column
            if (!output.is_open()) { // check if the file is open
                std::cerr << "Error opening output file: " << output_file << std::endl;
                return;
            
            }            

            try { // try-catch to access the data in a type safe way
                if (std::holds_alternative<std::string>(data[1][column_index])) { // compile-time check if the value is a string, compile with -std=c++17
                    // code to perform stat analysis on all the string columns
                    output << "Frequency analysis of the " << headers[column_index] << " column" << std::endl; // print the name of the column in the stats.txt file 
                    std::vector<std::string> string_data = extract_string_column(column_index);

                    for (auto i : frequency_count(string_data)) {
                        output << i.first << ": " << i.second << std::endl; // i.first is the key, i.second is the counter
                    }

                    //Write the line between the analysis of different columns
                    output << "----------------------" << std::endl;
                    output.close();

                } else if (std::holds_alternative<double>(data[1][column_index])) { // compile-time check if the value is a double, compile with -std=c++17
                    // code to perform stat analysis on all the string columns
                    // Extract numerical column data (adjust column_index as needed)
                    output << "Statistical analysis of the ";
                        std::visit([&output](auto&& value) { // lambda function needed to print the name of the column in the stats.txt file
                                        output <<  value; 
                                    }, data[0][column_index]); // The name of the column is always the 0th row of a CSV file
                        output << " column " << std::endl;
                    
                    std::vector<double> numerical_data = extract_numerical_column(column_index); // extract the numerical column if the column is actually numerical

                    // Write the statistics to the file
                    output << "Mean: " << calculate_mean(numerical_data) << std::endl;                                                                                 
                    output << "Median: " << calculate_median(numerical_data) << std::endl;
                    output << "Variance: " << calculate_variance(numerical_data) << std::endl;
                    output << "Standard Deviation: " << calculate_standard_deviation(numerical_data) << std::endl << std::endl;
                    output.close();

                    // Generate histogram and append to the same file
                    generate_histogram(numerical_data, output_file);
                    
                    // Write the line between the analysis of different columns
                    output.open(output_file, std::ios::app);
                    output << "-----------------------" << std::endl;
                    output.close();


                } else {
                    std::cout << "Unknown type!" << std::endl;
                }

            } catch (const std::bad_variant_access& e){
                std::cerr << "Error: " << e.what() << std::endl; 
            }
            
        
        
        }


    }

    // Function to convert the data to a pandas DataFrame
    py::object CSVReader::to_pandas() const {
        py::object pd = py::module::import("pandas");
        py::dict dict;
        
        // For each column
        for (size_t i = 0; i < headers.size(); ++i) {
            std::vector<std::string> column;
            // Extract column data
            for (const auto& row : data) {
                if (i < row.size()) {
                    if (std::holds_alternative<std::string>(row[i])) {
                        column.push_back(std::get<std::string>(row[i]));
                    } else if (std::holds_alternative<double>(row[i])) {
                        column.push_back(std::to_string(std::get<double>(row[i])));
                    }
                } else {
                    column.push_back("");  // Handle missing data
                }
            }
            dict[py::str(headers[i])] = column;
        }

        return pd.attr("DataFrame")(dict);
    }
