// Practical 1

#include <iostream> // for input and output
#include <fstream> // for file handling
#include <string>   // for string handling
#include <vector>   // for vectors
#include "multiply.h" // for the class MatrixReader
#include <random> // for random number generation
#include "timing.h" // for timing

int main(int argc, char* argv[]){

    if(argc == 6){
        
        // two matrix dimensions are provided as inputs
        // Generate random matrices of the given dimensions

        int rows1 = std::stoi(argv[2]);    // convert the string to an integer by using std::stoi
        int cols1 = std::stoi(argv[3]);
        int rows2 = std::stoi(argv[4]);
        int cols2 = std::stoi(argv[5]);

        std::vector<std::vector<double>> matrix1(rows1, std::vector<double>(cols1));
        std::vector<std::vector<double>> matrix2(rows2, std::vector<double>(cols2));

        for (int i = 0; i < rows1; ++i) {
            for (int j = 0; j < cols1; ++j) {
                matrix1[i][j] = rand() % 10;  // generate a random number between 0 and 9
            }
        }

        for (int i = 0; i < rows2; ++i) {
            for (int j = 0; j < cols2; ++j) {
                matrix2[i][j] = rand() % 10;  // generate a random number between 0 and 9
            }
        }   

        std::cout << "First matrix:" << std::endl;
        for (const auto& row : matrix1) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "Second matrix:" << std::endl;
        for (const auto& row : matrix2) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }

        if(std::string(argv[1]) == "vanilla"){
            timing::start_clock();
            MatrixReader::printMatrix(MatrixReader::multiplyMatrices(matrix1, matrix2));
            std::cout << "Multiplication time for vanilla method: " << timing::get_split() << " ms" << std::endl;
        }

        else if(std::string(argv[1]) == "flatten"){
            timing::start_clock();
            MatrixReader::printMatrix(MatrixReader::multiplyMatricesFlatten(matrix1, matrix2));
            std::cout << "Multiplication time for flatten method: " << timing::get_split() << " ms" << std::endl;
        }

        else if(std::string(argv[1]) == "transpose"){
            timing::start_clock();
            MatrixReader::printMatrix(MatrixReader::multiplyMatricesTranspose(matrix1, matrix2));
            std::cout << "Multiplication time for transpose method: " << timing::get_split() << " ms" << std::endl;
        }

        else if(std::string(argv[1]) == "cache_blocking"){

            timing::start_clock();
            int blockSize;
            MatrixReader::printMatrix(MatrixReader::multiplyMatricesCacheBlocking(matrix1, matrix2, blockSize = 8));
            std::cout << "Multiplication time for cache blocking method with block size " << blockSize << ": " << timing::get_split() << " ms" << std::endl;

            // Loop over different block sizes and save the time taken for each
            for (int blockSize = 1; blockSize <= 64; blockSize += 1) {
                timing::start_clock();
                MatrixReader::printMatrix(MatrixReader::multiplyMatricesCacheBlocking(matrix1, matrix2, blockSize));
                
                // Save the time taken for each block size to a file
                std::ofstream file("cache_blocking_times_no_opt.txt", std::ios::app);
                file << "Block size: " << blockSize << " Time: " << timing::get_split() << " ms" << std::endl;
            file.close();

            }
        }
            


        else{

            std::cout << "Error: incorrect matrix multiplication method" << std::endl;
            return 1;
        }
   
        
    }
       

    else if (argc == 2){

    // create two matrices
    std::vector<std::vector<double>> matrix1, matrix2;

    if (MatrixReader::readMatricesFromFile(argv[1], matrix1, matrix2)) {
        std::cout << "First matrix:" << std::endl;
        for (const auto& row : matrix1) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "Second matrix:" << std::endl;
        for (const auto& row : matrix2) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
        MatrixReader::printMatrix(MatrixReader::multiplyMatrices(matrix1, matrix2));
        


    } else {
        std::cerr << "Failed to open the file: " << argv[1] << std::endl;
    }

    }

    else {


        // test if the user has entered the correct number of arguments
        std::cout << "Error: incorrect number of arguments" << std::endl;
        return 1;
    }

    return 0;

}

