/**********************************
Your name: Lucian Pate
Your programmer number: 25
How many hours did you spend?:
Any difficulties?: 

Template prepared by Kazumi Slott
CS311

matrix class

Replace the ?????s

For examples of matrix multiplication
https://matrix.reshish.com/multCalculation.php 
***********************************/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
using namespace std;

//This forward declaration of Matrix class is necessary because the following operator>> and << are using Matrix as a parameter
template <class T>
class Matrix;

//This forward declaration of operator>> is necessary Since operator<< is a template function.
template<class T>
ifstream& operator>>(ifstream& o, Matrix<T>& m);

//This forward declaration of operator<< is necessary Since operator<< is a template function.
template <class T>
ostream& operator<<(ostream& o, const Matrix<T> & m);

//Template class so we can have a matrix of any data types, int or double
template <class T>
class Matrix
{
  friend ifstream& operator>> <T>(ifstream& o, Matrix<T>& m);
  friend ostream& operator<< <T>(ostream& o, const Matrix<T> & m);  
 private: 
  T** m; //2 dimensional dynamic array
  const int R; //number of rows
  const int C; //number of columns
  
 public: 
  Matrix(int R, int C);
  Matrix();
  ~Matrix();
  void fill(); //filling the matrix
  Matrix operator*(const Matrix& other);// matrix multiplication
  class size_error{};//exception class
};

//default constructor
template<class T>
Matrix<T>::Matrix() : R(0), C(0) //setting const R and C to initial value, 0.
{
  m = NULL;
}

//constructor to create a matrix, row x col 
template<class T>
Matrix<T>::Matrix(int row, int col) : R(row), C(col) //setting const R and C 
{
  if(row <= 0 || col <= 0)
    {
      m = NULL;
      return;
    }

  //m = new T[R][C]; //this doesn't compile
  m = new T*[R]; //create a single dimensional array of pointers of the T type
  for (int i=0; i<R; i++) //create a single dimensional array for each slot of m
    m[i] = new T[C];

  //initialize each element to 0
  for(int row = 0; row < R; row++)
    for(int col = 0; col < C; col++)
	m[row][col] = 0;
}

//fill a matrix using an input file
template<class T>
ifstream& operator>>(ifstream& fin, Matrix<T>& mrx)
{
  
  for(int i = 0; i < mrx.R; i++)
    {
      for(int j = 0; j < mrx.C; j++)
	{
	  fin >> mrx.m[i][j];
	}
    }  
  return fin;
  
}

/*
output the matrix to screen in the following format. Allocate 5 spaces for each value.
    1    1    1
    2    2    2
    3    3    3
    4    4    4 
*/

template<class T>
ostream& operator<<(ostream& o, const Matrix<T>& mrx)
{
  
  //multiple lines of code here
for(int i = 0; i < mrx.R; i++)
  {
    for(int j = 0; j < mrx.C; j++)
      {
	o << setw(10) << mrx.m[i][j]<<setw(10);
      }
    o << endl;
  }
   //use setw(5) to allocate 5 spaces to show each value
   return o;
   
}
  
//matrix multiplication


template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other)
{
  Matrix<T> ans(this->R, other.C);
  //check if the 2 matrices are comparable. If m1 is mxn, m2 has to be nxk. 
  if(this->C != other.R) //cannot compute because of incomparable sizes
    throw size_error(); //throw an exception 
  
   //multiple lines of code
  for(int i = 0; i < this->R; i++)
    {
      for(int j = 0; j < other.C; j++)
	{
	  ans.m[i][j] = 0;
	  for(int k = 0; k < this->C; k++)
	    {
	      ans.m[i][j] += this->m[i][k] * other.m[k][j];
	    }
	}
    }
  return ans;
  
}

//destructor                                                                                                                                                                                
template<class T>
Matrix<T>::~Matrix()
{
  //destroy what is created in heap memory                                    
  //if m is not NULL do the following                                   
  //HINT: delete each dynamic array pointed to by each slot of m                
  //delete m (m contains all rows)
  if( m != NULL)
    for(int i = 0; i < R; i++)
      {
	delete[] m[i];
      }
	  delete[] m;
}

