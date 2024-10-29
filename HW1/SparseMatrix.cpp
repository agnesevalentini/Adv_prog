#include <iostream>
#include <vector>
#include <stdexcept>

// Abstract base class for sparse matrices
class SparseMatrix {
public:
    virtual int get_num_rows() const = 0;
    virtual int get_num_cols() const = 0;
    virtual int get_nnz() const = 0; //get number of nonzero elements
    virtual double operator()(const unsigned int row, const unsigned int col) const = 0; // Const overload for read access
    virtual double& operator()(const unsigned int row, const unsigned int col, const double value) = 0;      // Non-const overload for write access
    virtual std::vector<double> operator*(const std::vector<double> &vec) const = 0;
    virtual void print() const = 0;
    virtual ~SparseMatrix() = default;
};

// Derived class for COO format
class SparseMatrixCOO : public SparseMatrix {
private:
    std::vector<double> values; // Non-zero values
    std::vector<int> rows;      // Row indices for non-zero values
    std::vector<int> cols;      // Column indices for non-zero values
    int num_rows, num_cols;

public:
    SparseMatrixCOO(const int rows, const int cols) : num_rows(rows), num_cols(cols) {} //COO class constructor

    int get_num_rows() const override { return num_rows; }
    int get_num_cols() const override { return num_cols; }
    int get_nnz() const override { return values.size(); }

    // Const overload for operator() to access matrix entries without modifying
    double operator()(const unsigned int row, const unsigned int col) const override {
        for (int i = 0; i < values.size(); ++i) {
            if (rows[i] == row && cols[i] == col) {
                return values[i];
            }
        }
        throw std::out_of_range("Element not found in sparse matrix.");
        
    }

    // Non-const overload for operator() to modify matrix entries
    double& operator()(const unsigned int row, const unsigned int col, const double value) override {
        if(row > num_rows || col > num_cols ) {
            throw std::out_of_range("Position out of range");
        }
        // se esistono gli indici NON devo aggiungere

        rows.push_back(row); // add element in the last position of the vector (method of vector class)
        cols.push_back(col);
        values.push_back(value);

        for (int i = rows.size()-2; rows[i]<row; i--)
        {
            if(rows[i]>row){
               rows[i+1]=rows[i];
            }
        }
        
    }

    // Overloading operator* for matrix-vector multiplication
    std::vector<double> operator*(const std::vector<double>& vec) const override {
        if (vec.size() != num_cols) {
            throw std::invalid_argument("Vector size does not match matrix dimensions.");
        }

        std::vector<double> result(num_rows, 0.0);
        for (size_t i = 0; i < values.size(); ++i) {
            result[rows[i]] += values[i] * vec[cols[i]];
        }
        return result;
    }

    // Print matrix in readable format
    void print() const override {
        for (size_t i = 0; i < values.size(); ++i) {
            std::cout << "Row: " << rows[i] << ", Col: " << cols[i] << ", Value: " << values[i] << std::endl;
        }
    }

    // Additional functions for adding or setting values could go here
};

// Derived class for CSR format - similar structure to SparseMatrixCOO with different data handling
class SparseMatrixCSR : public SparseMatrix {
private:
    std::vector<double> values;
    std::vector<int> columns;
    std::vector<int> row_idx;
    int num_rows, num_cols;

public:
    SparseMatrixCSR(int rows, int cols) : num_rows(rows), num_cols(cols) {}

    // Implementations for all virtual functions following CSR logic
    

};
