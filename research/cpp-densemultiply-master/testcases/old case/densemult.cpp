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
                // Check if we encounter "."
                if (input.at(i) == '.')
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

    /**
     * @brief parse each line(row) to double variables
     * 
     * @param line line to parse
     * @param count calculates column count, pass by reference
     * @return double* returns double pointer to array of the line
     */
    double *parseLine(const std::string &line, int &column_count)
    {
        std::string delim = " ";
        std::string current;
        column_count = 0;
        double *p = new double[20]; // create dynamic array

        auto start = 0U;
        auto end = line.find(delim);
        while (end != std::string::npos)
        {
            current = line.substr(start, end - start);
            if (!(is_number(current)))
            {
                error();
            }

            // convert the parsed string to double and store it in the p dynamic array
            p[column_count] = std::stod(current);
            column_count++;

            //std::cout << current << std::endl;
            start = end + delim.length();
            end = line.find(delim, start);
        }
        current = line.substr(start, end);
        p[column_count] = std::stod(current);
        column_count++;
        //std::cout << current << std::endl;
        if (!(is_number(current)))
        {
            error();
        }
        //std::cout << "Column Count: " << column_count + 1 << std::endl;

        return p;
    }

  public:
    MatrixMultiply(std::string fileNameA, std::string fileNameB, std::string fileNameC)
    {
        outfilename = fileNameC;
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
    bool readMatrices(std::string fileNameA, std::string fileNameB)
    {
        ifstream infile;
        std::string *p;
        std::string delim = " ";
        int *row_count = 0;
        int column_count = 0;
        double *row;

        //////////////////////////////
        // Matrix A Process Start
        //////////////////////////////

        infile.open(fileNameA);
        p = new std::string;
        row_count = new int(0);

        // Find row count
        while (!infile.eof())
        {
            getline(infile, *p);

            row = parseLine(*p, column_count);

            for (int i = 0; i < column_count; i++)
            {
                matrixA[*row_count][i] = row[i];
            }
            (*row_count)++;
        }

        infile.close();

        matrixA_column_count = column_count;
        matrixA_row_count = *row_count;

        printMatrixA();

        delete p;
        //////////////////////////////
        // Matrix A Process Finished
        //////////////////////////////

        //////////////////////////////
        // Matrix B Process Start
        //////////////////////////////

        infile.open(fileNameB);
        p = new std::string;
        row_count = new int(0);

        // Find row count
        while (!infile.eof())
        {
            getline(infile, *p);

            row = parseLine(*p, column_count);

            for (int i = 0; i < column_count; i++)
            {
                matrixB[*row_count][i] = row[i];
            }
            (*row_count)++;
        }

        infile.close();

        matrixB_column_count = column_count;
        matrixB_row_count = *row_count;

        printMatrixB();

        delete p;
    }

    void denseMultiply()
    {
        // Matrix A = 1x3 Matrix B = 3x4 Matrix C= 1x4
        //std::cout << matrixA[0][0] << " " << matrixA[0][1];
        // for (int i = 0; i < matrixB_row_count; i++)
        // {
        //     for (int j = 0; j < matrixA_column_count; j++)
        //     {
        //         matrixC[0][i] += matrixA[i][j] * matrixB[j][i];
        //     }
        // }

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