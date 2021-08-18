/* My_matrix.h

Header file for the class My_matrix

Write your name and UIN here
Nikhil Nunna 52508698
*/

#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <typeinfo>

using namespace std;
// Definitions of user defined type exceptions 
struct invalid_input : public exception {
  virtual const char* what() const throw()
  { return "Invalid matrix input"; }
};

struct incompatible_matrices : public exception {
  virtual const char* what() const throw()
  { return "Incompatible matrices"; }
};

template <typename T> class My_matrix {
	
private://member variables
  int n, m;
  string type;
  T **ptr;
  // memory allocater
  void allocate_memory()
  {
	  ptr = new T *[n];
	  for (int count = 0; count < n; count++)
		  ptr[count] = new T[m];
  }
public:	
	//member functions
	// default constructor
	My_matrix()
	{
		type = typeid(T).name();
		ptr = nullptr;
	}
	// parameter constructor
	My_matrix(int n1, int m1)
	{
		type = typeid(T).name();
		n = n1;
		m = m1;
		allocate_memory();
		for (int i = 0; i < n1; i++)
		{
			for (int j = 0; j < m1; j++)
			{
				if (type == "long"||"float"||"double"||"int")
				{
					ptr[i][j] = 0;
				}
				
			}
		}

	}
	// destructor
	~My_matrix()
	{
		if (ptr != nullptr) {
			for (int i = 0; i < n; i++)
			{
				delete[] ptr[i];
			}
			delete[] ptr;
		}

	}
	// copy constructor
	My_matrix(const My_matrix& mat)
	{
		type = typeid(T).name();
		n = mat.n;
		m = mat.m;
		allocate_memory();
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				ptr[i][j] = mat.ptr[i][j];
			}
		}

	}
	// move constructor (optional)
	My_matrix(My_matrix&& mat)
	{
		type = typeid(T).name();
		n = mat.n;
		m = mat.m;
		allocate_memory();
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				ptr[i][j] = mat.ptr[i][j];
			}
		}
		mat.ptr = nullptr;

	}
	// copy assignment
	My_matrix& operator=(const My_matrix& mat)
	{
		if ((mat.Of_type() != Of_type()))
		{
			throw incompatible_matrices();
		}
		else
		{
			n = mat.n;
			m = mat.m;
			allocate_memory();
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					ptr[i][j] = mat.ptr[i][j];
				}
			}
			return *this;
		}
	}
	// move assignment operator (optional)
	My_matrix& operator=(My_matrix&& mat)
	{
		if ((mat.Of_type() != Of_type()))
		{
			throw incompatible_matrices();
		}
		else
		{
			n = mat.n;
			m = mat.m;
			allocate_memory();
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					ptr[i][j] = mat.ptr[i][j];
				}
			}
			mat.ptr = nullptr;
			return *this;
		}
		
	}
	// row getter
	int number_of_rows() const
	{
		int rows = n;
		return rows;
	}
	// column getter
	int number_of_columns() const
	{
		int cols = m;
		return cols;
	}
	// type getter
	string Of_type() const
	{
		string type1 = type;
		return type1;
	}
	// returns ptr to row
	int* operator()(int i) const
	{
		if (i < 0 || i >= n) throw out_of_range("Out of range");
		else return ptr[i];
	}
	// returns variable at a postion 
	T operator()(int i, int j) const
	{
		if (i < 0 || i >= n) throw out_of_range("Out of range");
		if (j < 0 || j >= m) throw out_of_range("Out of range");
		else return ptr[i][j];
	}
	// return postition of an int
	T& operator()(int i, int j)
	{
		if (i < 0 || i >= n) throw out_of_range("Out of range");
		if (j < 0 || j >= m) throw out_of_range("Out of range");
		else return ptr[i][j];
	}

	T& elem(int i, int j) const
	{
		if (i < 0 || i >= n) throw out_of_range("Out of range");
		if (j < 0 || j >= m) throw out_of_range("Out of range");
		else return ptr[i][j];
	}

	T& elem(int i, int j)
	{
		if (i < 0 || i >= n) throw out_of_range("Out of range");
		if (j < 0 || j >= (m + 1)) throw out_of_range("Out of range");
		else return ptr[i][j];
	}
	// row setter
	void set_rows(int i_rows)
	{
		n = i_rows;
	}
	//column setter
	void set_cols(int i_cols)
	{
		m = i_cols;
	}
  // input operator
  friend istream& operator>>(istream& in, My_matrix& mat)
  {
	  int row = 0;
	  int col = 0;
	  in >> row >> col;
	  mat.set_rows(row);
	  mat.set_cols(col);
	  mat.allocate_memory();
	  for (int i = 0; i < row; i++)
	  {
		  for (int j = 0; j < col; j++)
		  {
			  in >> mat.ptr[i][j];
		  }
	  }
	  return in;
  }
  // output operator
  friend ostream& operator<<(ostream& out, const My_matrix& mat)
  {
	  for (int i = 0; i < mat.number_of_rows(); ++i) {
		  out << mat(i, 0);
		  for (int j = 1; j < mat.number_of_columns(); ++j) {
			  out << " " << mat(i, j);
		  }
		  out << endl;
	  }
	  return out;
  }
  // addition operator
  friend My_matrix operator+(const My_matrix& mat1, const My_matrix& mat2)
  {
	  if ((mat1.Of_type() != mat2.Of_type()))
	  {
		  throw incompatible_matrices();
	  }
	  else
	  {
		  if (mat1.number_of_columns() == mat2.number_of_columns() && mat1.number_of_rows() == mat2.number_of_rows())
		  {
			  My_matrix temp(mat1.number_of_rows(), mat1.number_of_columns());
			  for (int i = 0; i < mat1.number_of_rows(); ++i)
			  {
				  for (int j = 0; j < mat2.number_of_columns(); ++j)
				  {
					  temp.elem(i, j) = mat1.elem(i, j) + mat2.elem(i, j);
				  }
			  }
			  return temp;
		  }
		  else
		  {
			  throw incompatible_matrices();
		  }
	  }
	  
  }
  // multiplication operator
  friend My_matrix operator*(const My_matrix& mat1, const My_matrix& mat2)
  {

	  if (mat1.number_of_columns() != mat2.number_of_rows()|| (mat1.Of_type() == "char") || (mat1.Of_type() == "string") || (mat2.Of_type() != mat1.Of_type()))
	  {
		  throw incompatible_matrices();
	  }
	  else
	  {
		  My_matrix temp(mat1.number_of_rows(), mat2.number_of_columns());
		  for (int i = 0; i < mat1.number_of_rows(); ++i) {
			  for (int j = 0; j < mat2.number_of_columns(); ++j) {
				  for (int k = 0; k < mat1.number_of_columns(); ++k) {
					  temp.elem(i, j) += (mat1.elem(i, k) * mat2.elem(k, j));
				  }
			  }
		  }
		  return temp;


	  }
  }
  };