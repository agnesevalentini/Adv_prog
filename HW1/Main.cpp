#include <iostream>
#include "SparseMatrix.cpp"

int main(int argc, char const *argv[])
{
    SparseMatrixCOO matrix1 = SparseMatrixCOO{3,2};  // per mettere i parametri guarda quelli del costruttore, in questo caso numero di righe e di colonne
    try
    {
    std::cout << matrix1(2,2);
        
    }
    catch(const std::exception& e)
    {
        std::cout << "ops";
        //std::cerr << e.what() << '\n';
    }
    
    return 0;
}
