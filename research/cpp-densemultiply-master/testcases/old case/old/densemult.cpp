#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sys/stat.h>
#include <unistd.h>
#include "ArgumentManager.h"

bool read_matrix(const char* filename, std::vector<std::vector<double> >& m);
void write_matrix(const char* filename, const std::vector<std::vector<double> >& o);
void dense_mult(const std::vector<std::vector<double> >& m, std::vector<std::vector<double> >& o);

int main(int argc, char* argv[]) 
{
  if (argc < 2) {
    std::cout << "Usage: densemult \"A=<file>;C=<file>\"" << std::endl;
    return -1;
  }
    
  ArgumentManager am(argc, argv);
  std::string infilename = am.get("A");
  std::string outfilename = am.get("C");
  std::cout << "File name for matrix A: " << infilename << std::endl
       << "File name for matrix C: " << outfilename << std::endl;

  std::vector<std::vector<double> > m;
  std::vector<std::vector<double> > o;
  if (read_matrix(infilename.c_str(), m))
    dense_mult(m, o);
  write_matrix(outfilename.c_str(), o);

  return 0;
}

bool is_number(const std::string& s)
{
  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it)) ++it;
  return !s.empty() && it == s.end();
}

int get_matrix_size(const std::string& str){
  std::stringstream ss(str);
  int size = 0;
  std::string word;
  while (ss >> word){
    if (is_number(word)){
      size = std::stoi(word);
      break;
    }
  }
  return size;
}

bool read_matrix(const char* filename, std::vector<std::vector<double> >& m){
  std::ifstream ifs(filename);
  std::string str;
  getline(ifs, str);
  if (str.empty()){
    std::cout << "ERROR! Input file EMPTY!" << std::endl;
    return false;
  }

  if (get_matrix_size(str) <= 0) {
    std::cout << "ERROR! The size of Matrix is not valid!" << std::endl;
    return false;
  }

  while (getline(ifs, str)) {
    std::vector<double> row;
    std::stringstream ss(str);
    double num;
    while (ss >> num)
      row.push_back(num);
    if (!row.empty())
      m.push_back(row);
  }

  return true;
}

void write_matrix(const char* filename, const std::vector<std::vector<double> >& o){
  std::ofstream ofs(filename);
  if (o.empty())
    return;
  //ofs << "#Matrix C=AA, 2 decimals\n";
  ofs.precision(2);
  ofs.setf(std::ios::fixed);
  for (size_t i = 0; i < o.size(); i++) {
    ofs << o[i][0];
    for (size_t j = 1; j < o[i].size(); j++)
      ofs << " " << o[i][j];
    ofs << "\n";
  }
}

void dense_mult(const std::vector<std::vector<double> >& m, std::vector<std::vector<double> >& o) {
  o = m;
  for (size_t i = 0; i < m.size(); i++) {
    for (size_t j = 0; j < m[i].size(); j++) {
      o[i][j] = 0.0;
      for (size_t ii = 0; ii < m[0].size(); ii++)
        o[i][j] += m[i][ii] * m[ii][j];
    }
  }
}
