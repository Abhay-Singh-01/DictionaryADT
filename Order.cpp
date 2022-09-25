//-----------------------------------------------------------------------------
// Abhay Singh, abrsingh
// 2022 Spring CSE101 PA#7
// Order.cpp
// Order program that uses the Dictionary ADT
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<stdexcept>
#include<fstream>
#include<iomanip>
#include "Dictionary.h"

using namespace std;

int main(int argc, char * argv[]){

   ifstream in;
   ofstream out;

   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

   Dictionary D;
   keyType str1;
   int count = 0;

   while (getline(in, str1)) {
       count += 1;
       D.setValue(str1, count);
   }

   out << D << endl;

   out << D.pre_string() << endl;

   in.close();
   out.close();

}
