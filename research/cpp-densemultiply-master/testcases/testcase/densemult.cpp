/**
 * @brief COSC2430 - HW 1 
 * 
 * @file densemult.cpp
 * @author Omer Tarik Koc
 * @date 2018-08-28
 */

#include <string>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include <iomanip>
#include <sstream>
#include "ArgumentManager.h"

bool is_number(const std::string &);

class MatrixMultiply
{
  private:
    double matrixA[20][20];
    int matrixA_row_count;
    int matrixA_column_count;
    double matrixB[20][20];
    int matrixB_row_count;
    int matrixB_column_count;
    double matrixC[20][20];
    int matrixC_row_count;
    int matrixC_column_count;
    std::string outfilename;

    /**
     * @brief When an error founds this function will terminate the program and write "error" to the output file
     * 
     */
    int error()
    {
        ofstream outfile;
        outfile.open(outfilename);
        outfile << "error";
        outfile.close();
        std::cout << "error";
        exit(EXIT_FAILURE);
        return -1;
    }

    /**
     * @brief The number of columns of the 1st matrix must equal the number of rows of the 2nd matrix.
     * 
     * @return true if matrices can multiply
     * @return false if an error with the sizes
     */
    bool checkMatrixSizes()
    {
        if (matrixA_column_count == matrixB_row_count)
        {
            // Set MatrixC sizes
            matrixC_row_count = matrixA_row_count;
            matrixC_column_count = matrixB_column_count;
            return true;
        }
        else
        {
            error();
            return false;
        }
    }

    void checkInvalidInput(std::string filename)
    {
        ifstream cinFile;
        cinFile.open(filename);
        std::string str;
        while (getline(cinFile, str))
        {
            if (str.empty())
            {
                std::cout << "ERROR: file is empty" << std::endl;
                error();
            }
            std::stringstream ss(str);
            std::string word;
            while (ss >> word)
            {
                std::cout << word << std::boolalpha << ", is_number " << is_number(word) << std::endl;
                if (!(is_number(word)))
                {
                    std::cout << "Number error: " << word << std::endl;
                    error();
                }
            }
        }
        cinFile.close();
    }

    /**
    * @brief Determine if the input is number
    * @param input string the number that will be checked 
    */
    bool is_number(const std::string &input)
    {
        for (int i = 0; i < input.size(); i++)
        {
            if (!isdigit(input.at(i)))
            {
                // Check if we encounter "." or "-" or "\n" or " "
                if (input.at(i) == '.' || input.at(i) == '-')
                {
                    if (!isdigit(input.at(i + 1)))
                    {
                        return false;
                    }
                }
                else
                {
                    std::cout << input.at(i) << std::endl;
                    return false;
                }
            }
        }
        return true;
    }

  public:
    MatrixMultiply(std::string fileNameA, std::string fileNameB, std::string fileNameC)
    {
        outfilename = fileNameC;
        checkInvalidInput(fileNameA);
        checkInvalidInput(fileNameB);
        readMatrices(fileNameA, fileNameB);
        checkMatrixSizes();
        denseMultiply();
        writeOutputFile();
    }

    /**
     * @brief Read and store the matrices to the private members
     * @param fileNameA coming from the argument A
     * @param fileNameB coming from the argument B
     */
    void readMatrices(std::string fileNameA, std::string fileNameB)
    {
        ifstream infile;
        std::string *p;
        std::string delim = " ";
        int *row_count = 0;
        int column_count = 0;
        double *row;
        row = new double[20];

        //////////////////////////////
        // Matrix A Process Start
        //////////////////////////////

        infile.open(fileNameA);
        p = new std::string;
        row_count = new int(0);

        while (getline(infile, *p))
        {
            column_count = 0;
            std::stringstream ss(*p);
            double num;
            // if (!(ss >> num))
            //     error();
            while (ss >> num)
            {
                row[column_count] = num;
                column_count++;
            }
            for (int i = 0; i < column_count; i++)
            {
                matrixA[*row_count][i] = row[i];
            }
            (*row_count)++;
            std::cout << std::endl;
        }

        infile.close();

        matrixA_column_count = column_count;
        matrixA_row_count = *row_count;

        printMatrixA();

        delete row;
        delete row_count;
        delete p;
        // //////////////////////////////
        // // Matrix A Process Finished
        // //////////////////////////////

        // //////////////////////////////
        // // Matrix B Process Start
        // //////////////////////////////

        infile.open(fileNameB);
        p = new std::string;
        row_count = new int(0);
        row = new double[20];

        while (getline(infile, *p))
        {
            column_count = 0;
            std::stringstream ss(*p);
            double num;
            while (ss >> num)
            {
                row[column_count] = num;
                column_count++;
            }
            for (int i = 0; i < column_count; i++)
            {
                matrixB[*row_count][i] = row[i];
            }
            (*row_count)++;
            std::cout << std::endl;
        }

        infile.close();

        matrixB_column_count = column_count;
        matrixB_row_count = *row_count;

        printMatrixB();

        delete row;
        delete row_count;
        delete p;
    }

    void denseMultiply()
    {
        for (int i = 0; i < matrixA_row_count; ++i)
            for (int j = 0; j < matrixB_column_count; ++j)
                for (int k = 0; k < matrixA_column_count; ++k)
                {
                    matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
                }

        printMatrixC();
    }

    /**
     * @brief print Matrix A
     * 
     */
    void printMatrixA()
    {
        std::cout << showpoint << fixed << std::setprecision(2);
        std::cout << std::endl;
        std::cout << "================ " << std::endl;
        std::cout << "Matrix A (" << matrixA_row_count << "x" << matrixA_column_count << ")" << std::endl;
        for (int j = 0; j < matrixA_row_count; j++)
        {
            for (int m = 0; m < matrixA_column_count; m++)
            {
                std::cout << matrixA[j][m] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "================  " << std::endl;
        std::cout << std::endl
                  << std::endl;
    }

    /**
     * @brief Print Matrix B
     * 
     */
    void printMatrixB()
    {
        std::cout << showpoint << fixed << std::setprecision(2);
        std::cout << std::endl;
        std::cout << "================ " << std::endl;
        std::cout << "Matrix B (" << matrixB_row_count << "x" << matrixB_column_count << ")" << std::endl;
        for (int j = 0; j < matrixB_row_count; j++)
        {
            for (int m = 0; m < matrixB_column_count; m++)
            {
                std::cout << matrixB[j][m] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "================ " << std::endl;
        std::cout << std::endl
                  << std::endl;
    }

    /**
     * @brief Print Matrix C
     * 
     */
    void printMatrixC()
    {
        std::cout << showpoint << fixed << std::setprecision(2);
        std::cout << std::endl;
        std::cout << "================ " << std::endl;
        std::cout << "Matrix C (" << matrixC_row_count << "x" << matrixC_column_count << ")" << std::endl;

        for (int j = 0; j < matrixC_row_count; j++)
        {
            for (int m = 0; m < matrixC_column_count; m++)
            {
                std::cout << matrixC[j][m] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "================ " << std::endl;
        std::cout << std::endl
                  << std::endl;
    }

    void writeOutputFile()
    {
        ofstream outfile;
        outfile.open(outfilename);
        outfile << showpoint << fixed << std::setprecision(2);
        for (int j = 0; j < matrixC_row_count; j++)
        {
            for (int m = 0; m < matrixC_column_count; m++)
            {
                outfile << matrixC[j][m] << " ";
            }
            outfile << std::endl;
        }
        outfile << std::endl;
    }
};

int main(int argc, char *argv[])
{
    // Check if the argument number is correct
    // Otherwise print the proper usage of the program
    if (argc < 2)
    {
        std::cout << "Please call like that: densemult \"A=<file>;B=<file>;C=<file>\"" << std::endl;
        return -1;
    }

    // Using ArgumentManager.h parse the arguments and print out
    ArgumentManager am(argc, argv);
    std::string matrixA = am.get("A");
    std::string matrixB = am.get("B");
    std::string outfilename = am.get("C");
    std::cout << "File name for matrix A: " << matrixA << std::endl
              << "File name for matrix B: " << matrixB << std::endl
              << "File name for output matrix C: " << outfilename << std::endl;

    MatrixMultiply m(matrixA, matrixB, outfilename);
    return 0;
}