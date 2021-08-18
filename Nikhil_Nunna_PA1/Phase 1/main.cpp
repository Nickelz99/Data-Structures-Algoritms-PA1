// main.cpp
// Tests all functionality of the class My_matrix class.

#include <iostream>
#include <fstream>
#include "My_matrix.h"

int main(){
  
  // Some test cases are expected to throw an exception.
  // Add more try and catch blocks as necessary for your code
  // to finish execution.
    
  try{
    
    // Test 1
    // * Create an object of type My_matrix, called m1, using constructor
    // * Initialize m1 in main (by assigning numbers to matrix elements)
    // * Display m1 on the screen using the operator <<
	  My_matrix m1(5, 5);
	  for (int i = 0; i < m1.number_of_rows(); i++)
	  {
		  for (int j = 0; j < m1.number_of_columns(); j++)
		  {
			  (m1)(i,j) = j;
		  }
	  }
	  cout << m1 << endl;

    // Test 2
    // * Create an object of type My_matrix, called m2, using (default)
    //   constructor
    // * Open an input file containing a matrix (row by row)
    // * Initialize m2 by reading from the input file using
    //   the operator >>
    // * Open an output file (can be empty)
    // * Write m2 to the output file using the operator <<
	  My_matrix m2;
	  ifstream in("Test.txt");
	  ofstream out("output.txt");
	  in >> m2;
	  out << m2;
	  
	// Test 3
    // * Use the copy constructor to make a copy of m1 called m3
    // * Apply the copy assignment to m1 called m4
    // * Display m3 and m4 on the screen using the operator <<
	  My_matrix m3(m1);
	  My_matrix m4 = m1;
	  cout << m3 << endl;
	  cout << m4 << endl;


    // test 4
    // * test the matrix multiplication operator (operator*)
    // * apply the multiplication operator to valid and invalid cases
    // * display the resulting matrix and its number of rows and columns
	  My_matrix m5(18, 4);
	  for (int i = 0; i < m5.number_of_rows(); i++)
	  {
		  for (int j = 0; j < m5.number_of_columns(); j++)
		  {
			  (m5)(i, j) = j;
		  }
	  }
	  My_matrix m6(4, 5);
	  for (int i = 0; i < m6.number_of_rows(); i++)
	  {
		  for (int j = 0; j < m6.number_of_columns(); j++)
		  {
			  (m6)(i, j) = i
;
		  }
	  }
	  My_matrix m11;
	  m11 = m5*m6;
	  cout << m11 << endl;
	  


	  
	
    // Test 5
    // * Test the matrix addition operator (operator+)
    // * Apply the addition operator to valid and invalid cases
    // * Display the resulting matrix and its number of rows and columns
	  My_matrix m7(7, 2);
	  for (int i = 0; i < m7.number_of_rows(); i++)
	  {
		  for (int j = 0; j < m7.number_of_columns(); j++)
		  {
			  (m7)(i, j) = i;
		  }
	  }
	  My_matrix m8(7, 2);
	  for (int i = 0; i < m8.number_of_rows(); i++)
	  {
		  for (int j = 0; j < m8.number_of_columns(); j++)
		  {
			  (m8)(i, j) = j;
		  }
	  }
	   My_matrix m10;
	   m10 = m7 + m8;
	   cout << m10;
	  

  } catch(exception &error){
    cerr << "Error: " << error.what() << endl;
  }
}
