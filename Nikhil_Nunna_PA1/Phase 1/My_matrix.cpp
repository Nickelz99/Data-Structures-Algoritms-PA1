/* 
Implementation of the clas My_matrix
*/

#include "My_matrix.h"
#include <stdexcept>

My_matrix::My_matrix()
{
	ptr = nullptr;
}
// memory allocater
void My_matrix::allocate_memory()
{
	ptr = new int *[n];
	for (int count = 0; count < n; count++)
		ptr[count] = new int[m];
}
// parameter constructor
My_matrix::My_matrix(int n1, int m1)
{
	n = n1;
	m = m1;
	allocate_memory();
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < m1; j++)
		{
			ptr[i][j] = 0;
		}
	}

}
// copy constructor
My_matrix::My_matrix(const My_matrix& mat)
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

}

// move constructor (optional)
My_matrix::My_matrix(My_matrix&& mat)
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
	
}
// destructor
My_matrix::~My_matrix()
{
	if (ptr != nullptr) {
		for (int i = 0; i < n; i++)
		{
			delete[] ptr[i];
		}
		delete[] ptr;
	}
	
}
// copy assignment
My_matrix& My_matrix::operator=(const My_matrix& mat)
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

// move assignment operator (optional)
My_matrix& My_matrix::operator=(My_matrix&& mat)
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
// row getter
int My_matrix::number_of_rows() const
{
	int rows = n;
	return rows;
}
// column getter
int My_matrix::number_of_columns() const
{ 
	int cols = m;
	return cols;
}
// returns ptr to row
int* My_matrix::operator()(int i) const
{
	if (i < 0 || i >= n) throw out_of_range("Out of range");
	else return ptr[i];
}
// returns int at a postion 
int My_matrix::operator()(int i, int j) const
{
	if (i < 0 || i >= n) throw out_of_range("Out of range");
	if (j < 0 || j >= m) throw out_of_range("Out of range");
	else return ptr[i][j];
}
// return postition of an int
int& My_matrix::operator()(int i, int j)
{
	if (i < 0 || i >= n) throw out_of_range("Out of range");
	if (j < 0 || j >= m) throw out_of_range("Out of range");
	else return ptr[i][j];
}

int& My_matrix::elem(int i, int j) const
{
  if (i < 0 || i >= n) throw out_of_range("Out of range");
  if (j < 0 || j >= m) throw out_of_range("Out of range");
  else return ptr[i][j];
}

int& My_matrix::elem(int i, int j)
{
	if (i < 0 || i >= n) throw out_of_range("Out of range");
	if (j < 0 || j >= (m+1)) throw out_of_range("Out of range");
	else return ptr[i][j];
}
// row setter
void My_matrix::set_rows(int i_rows) 
{
	n = i_rows;
}
//column setter
void My_matrix::set_cols(int i_cols) 
{
	m = i_cols;
}

// output operator
ostream& operator<<(ostream& out, const My_matrix& mat)
{
	for (int i = 0; i < mat.number_of_rows(); ++i) {
		out << mat(i,0);
		for (int j = 1; j < mat.number_of_columns(); ++j) {
			out << " " << mat(i,j);
		}
		out << endl;
	}
	return out;
}
// input operator
istream& operator>>(istream& in, My_matrix& mat)
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
// addition operator
My_matrix operator+(const My_matrix& mat1, const My_matrix& mat2)
{
	if (mat1.number_of_columns() == mat2.number_of_columns() && mat1.number_of_rows() == mat2.number_of_rows())
	{
		My_matrix temp(mat1.number_of_rows(), mat1.number_of_columns());
		for (int i = 0; i < mat1.number_of_rows(); ++i) 
		{
			for (int j = 0; j < mat2.number_of_columns(); ++j)
			{
				temp.elem(i,j) = mat1.elem(i,j) + mat2.elem(i,j);
			}		
		}
		return temp;
	}
	else
	{
		throw incompatible_matrices();
	}
}
// multiplication operator
My_matrix operator*(const My_matrix& mat1, const My_matrix& mat2)
{

	if (mat1.number_of_columns() != mat2.number_of_rows())
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

