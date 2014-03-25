#ifndef VLSQMATRIX_H
#define VLSQMATRIX_H

#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::ostream;

#include <iomanip>
using std::setw;


class vlSqMatrix
{
  private:
    vector<int>& numbers;
    int raw_length;

    int set_raw_length( int new_length ) { return raw_length = new_length; }; //∆≈—“‹

  public:
    vlSqMatrix();
   ~vlSqMatrix();

    vlSqMatrix( const vlSqMatrix& );
    vlSqMatrix& operator= ( const vlSqMatrix& );

    vlSqMatrix( int size );

    vector<int>& get_numbers() const { return numbers; };
    vector<int>& set_numbers( vector<int>& new_vect ) { return numbers = new_vect; };

    inline int& operator() ( int, int );
    inline int  operator() ( int, int ) const;

    int size() const { return raw_length; };

    bool print_raw( int );
    bool print_col( int );

};

//===========//===========//===========//===========//===========//===========//

vlSqMatrix::vlSqMatrix():
  numbers( *new vector<int> ),
  raw_length( 0 )
{
  cout << "matrix with vector size = " << numbers.size() << " created\n";
}

vlSqMatrix::~vlSqMatrix()
{
  delete &numbers;
  raw_length = 0;
}


vlSqMatrix::vlSqMatrix( const vlSqMatrix& orig ):
  numbers( *new vector<int> ),
  raw_length( orig.get_numbers().size() )
{
  numbers = orig.get_numbers();
  cout << "copy size = " << numbers.size() << "\n";
}

vlSqMatrix& vlSqMatrix::operator= ( const vlSqMatrix& orig )
{
  set_numbers( orig.get_numbers() );
  set_raw_length( orig.get_numbers().size() );
  cout << "operator= : " << numbers.size() << "=" << orig.get_numbers().size() << "\n";
  return *this;
}


vlSqMatrix::vlSqMatrix( int size ):
  numbers( *new vector<int>( size*size ) ),
  raw_length( size )
{
  cout << "matrix with vector size = " << numbers.size() << " created\n";
}


inline int& vlSqMatrix::operator() ( int i, int j )
{
  return numbers[ i * raw_length + j ];
}

inline int vlSqMatrix::operator() ( int i, int j ) const
{
  return numbers[ i * raw_length + j ];
}

bool vlSqMatrix::print_raw( int number )
{
  for( int n = 0 ; n < size() ; n ++ )
  {
    cout << (*this)( number, n ) << " ";
  }
  cout << "\n";
  return true;
}

bool vlSqMatrix::print_col( int number )
{
  for( int n = 0 ; n < size() ; n ++ )
  {
    cout << (*this)( n, number ) << " ";
  }
  cout << "\n";
  return true;
}


//<<>><<>><<>><<>><<>>
ostream& operator<< ( ostream& stream, const vlSqMatrix& obj )
{
  int size = obj.size();
  for( int i = 0 ; i < size ; i ++ )
  {
    for( int j = 0 ; j < size ; j ++ )
    {
      stream << setw(4) << obj(i,j);
    }
    stream << "\n";
  }
  return stream;
}
#endif
