#ifndef MULTIPLY_H  // include guard
#define MULTIPLY_H

#include <vector>
#include <string>


// defining a class to read the file, create two matrices, multiply them, and output the result
class MatrixReader {
public:

    // Static means that the function can be called without an instance of the class
    static bool readMatricesFromFile(const std::string& filename,
                                     std::vector<std::vector<double> >& matrix1,
                                     std::vector<std::vector<double> >& matrix2);


    static std::vector<std::vector<double> > multiplyMatrices(const std::vector<std::vector<double> >& matrix1,
                                                           const std::vector<std::vector<double> >& matrix2);


    static void printMatrix(const std::vector<std::vector<double> > & matrix);

    static std::vector<std::vector<double> > multiplyMatricesFlatten(const std::vector<std::vector<double> > & matrix1,
                                                             const std::vector<std::vector<double> > & matrix2);

    static std::vector<std::vector<double> > multiplyMatricesTranspose(const std::vector<std::vector<double> > & matrix1,
                                                             const std::vector<std::vector<double> > & matrix2);

    static std::vector<std::vector<double> > multiplyMatricesCacheBlocking(const std::vector<std::vector<double> > & matrix1,
                                                             const std::vector<std::vector<double> > & matrix2,
                                                             int blockSize);


};

#endif // MULTIPLY_H
