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
#include "statistics_module.hpp"




int main(int argc, char* argv[]) {
    
    CSVReader reader;
    reader.parse_arguments(argc, argv);
    reader.load_data();
    reader.print_column(1);
    reader.print_row(2);
    //reader.print_data(); uncomment to see the csv data parsed
    reader.write_statistics_to_file("stats.txt");
    std::cout << "Statistics and histogram written to: stats.txt" << std::endl;


return 0;

}