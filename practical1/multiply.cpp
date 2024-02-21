// Contains functions to:
// read input from a file
// multiply two matrices
// ouput a result matrix


#include "multiply.h"
#include <iostream> // for input and output
#include <fstream> // for file handling
#include <sstream> // for string stream handling



// defining a function to read the file and create a matrix

bool MatrixReader::readMatricesFromFile(const std::string& filename,
                                        std::vector<std::vector<double> > & matrix1,
                                        std::vector<std::vector<double> > & matrix2){


    std::ifstream file(filename);  //open the file
    if (!file.is_open()) {

        std::cout << "Error: file could not be opened" << std::endl;
        return false;
    }

    int rows, cols;

    // Read the dimensions and elements of the first matrix
    file >> rows >> cols;
    matrix1.resize(rows, std::vector<double>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> matrix1[i][j];
        }
    }

    // Read the dimensions and elements of the second matrix
    file >> rows >> cols;
    matrix2.resize(rows, std::vector<double>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> matrix2[i][j];
        }
    }

    file.close();
    return true;
}

// defining a function to multiply two matrices

std::vector<std::vector<double> > MatrixReader::multiplyMatrices(const std::vector<std::vector<double> > & matrix1,
                                                             const std::vector<std::vector<double> > & matrix2){



    int rows1 = matrix1.size();  // number of rows in the first matrix
    int cols1 = matrix1[0].size();  // number of columns in the first matrix
    int rows2 = matrix2.size();  // number of rows in the second matrix
    int cols2 = matrix2[0].size();  // number of columns in the second matrix

    if (cols1 != rows2) {
        // include a check for the dimensionality of the two matricies
        std::cerr << "Error: the number of columns in the first matrix must be equal to the number of rows in the second matrix" << std::endl;
        return std::vector<std::vector<double> >();
    }

    std::vector<std::vector<double> > result(rows1, std::vector<double>(cols2, 0));  // initialize the result matrix
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            for (int k = 0; k < cols1; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}


// Define a matrix multiplication function that uses flatten matrices to improve cache performance

std::vector<std::vector<double> > MatrixReader::multiplyMatricesFlatten(const std::vector<std::vector<double> > & matrix1,
                                                             const std::vector<std::vector<double> > & matrix2){
    int rows1 = matrix1.size();  // number of rows in the first matrix
    int cols1 = matrix1[0].size();  // number of columns in the first matrix
    int rows2 = matrix2.size();  // number of rows in the second matrix
    int cols2 = matrix2[0].size();  // number of columns in the second matrix

    if (cols1 != rows2) {
        // include a check for the dimensionality of the two matricies
        std::cerr << "Error: the number of columns in the first matrix must be equal to the number of rows in the second matrix" << std::endl;
        return std::vector<std::vector<double> >();
    }

    std::vector<std::vector<double> > result(rows1, std::vector<double>(cols2, 0));  // initialize the result matrix
    std::vector<double> matrix1Flatten(rows1 * cols1);  // flatten the first matrix
    std::vector<double> matrix2Flatten(rows2 * cols2);  // flatten the second matrix
    std::vector<double> resultFlatten(rows1 * cols2, 0);  // flatten the result matrix and initialize it to zero
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols1; ++j) {
            matrix1Flatten[i * cols1 + j] = matrix1[i][j];
        }
    }
    for (int i = 0; i < rows2; ++i) {
        for (int j = 0; j < cols2; ++j) {
            matrix2Flatten[i * cols2 + j] = matrix2[i][j];
        }
    }
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            for (int k = 0; k < cols1; ++k) {
                resultFlatten[i * cols2 + j] += matrix1Flatten[i * cols1 + k] * matrix2Flatten[k * cols2 + j];
            }
        }
    }
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            result[i][j] = resultFlatten[i * cols2 + j];
        }
    }
    return result;
}


// Define a matrix multiplication function that uses transpose matrices to improve cache locality
std::vector<std::vector<double> > MatrixReader::multiplyMatricesTranspose(const std::vector<std::vector<double> > & matrix1,
                                                             const std::vector<std::vector<double> > & matrix2){
    int rows1 = matrix1.size();  // number of rows in the first matrix
    int cols1 = matrix1[0].size();  // number of columns in the first matrix
    int rows2 = matrix2.size();  // number of rows in the second matrix
    int cols2 = matrix2[0].size();  // number of columns in the second matrix

    if (cols1 != rows2) {
        // include a check for the dimensionality of the two matricies
        std::cerr << "Error: the number of columns in the first matrix must be equal to the number of rows in the second matrix" << std::endl;
        return std::vector<std::vector<double> >();
    }

    std::vector<std::vector<double> > result(rows1, std::vector<double>(cols2, 0));  // initialize the result matrix
    std::vector<std::vector<double> > matrix2Transpose(cols2, std::vector<double>(rows2, 0));  // initialize the transpose of the second matrix
    for (int i = 0; i < rows2; ++i) {
        for (int j = 0; j < cols2; ++j) {
            matrix2Transpose[j][i] = matrix2[i][j];
        }
    }
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            for (int k = 0; k < cols1; ++k) {
                result[i][j] += matrix1[i][k] * matrix2Transpose[j][k];
            }
        }
    }
    return result;
}


// Define a matrix multiplication function that uses cache blocking to improve cache performance

std::vector<std::vector<double> > MatrixReader::multiplyMatricesCacheBlocking(const std::vector<std::vector<double> > & matrix1,
                                                             const std::vector<std::vector<double> > & matrix2,
                                                             int blockSize){
    int rows1 = matrix1.size();  // number of rows in the first matrix
    int cols1 = matrix1[0].size();  // number of columns in the first matrix
    int rows2 = matrix2.size();  // number of rows in the second matrix
    int cols2 = matrix2[0].size();  // number of columns in the second matrix

    if (cols1 != rows2) {
        // include a check for the dimensionality of the two matricies
        std::cerr << "Error: the number of columns in the first matrix must be equal to the number of rows in the second matrix" << std::endl;
        return std::vector<std::vector<double> >();
    }

    // initialize the result matrix
    std::vector<std::vector<double> > result(rows1, std::vector<double>(cols2, 0));  // initialize the result matrix
   
    // Making sure we do not attempt to access elements outside the matrix

    for (int i = 0; i < rows1; i += blockSize) {
        for (int j = 0; j < cols2; j += blockSize) {
            for (int k = 0; k < cols1; k += blockSize) {
                for (int i2 = i; i2 < i + blockSize && i2 < rows1; ++i2) {
                    for (int j2 = j; j2 < j + blockSize && j2 < cols2; ++j2) {
                        for (int k2 = k; k2 < k + blockSize && k2 < cols1; ++k2) {
                            result[i2][j2] += matrix1[i2][k2] * matrix2[k2][j2];
                        }
                    }
                }
            }
        }
    }


    return result;
}





// defining a function to output the result matrix

void MatrixReader::printMatrix(const std::vector<std::vector<double> > & matrix){
    std::cout << "Result matrix is:" << std::endl;
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}
