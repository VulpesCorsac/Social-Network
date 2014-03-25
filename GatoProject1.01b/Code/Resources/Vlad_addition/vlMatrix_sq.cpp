#ifndef VLMATRIX_SQ_H
#define VLMATRIX_SQ_H

#include <vector>
using std::vector;

#include <iostream>
using std::cout;


class vlMatrix_sq : public vlMatrix //?? оно нам вообще надо??
{
  private:
    vector<int>& numbers;

  public:
    vlMatrix();
   ~vlMatrix();

    vlMatrix( const vlMatrix& );
    vlMatrix& operator= ( const vlMatrix& );

    vlMatrix( int size );

    vector<int>& get_numbers() const { return numbers; };
    vector<int>& set_numbers( vector<int>& new_vect ) { return numbers = new_vect; };

    int operator() ( int, int ) const;

    int size() const { return size };

};

//===========//===========//===========//===========//===========//===========//

vlMatrix::vlMatrix():
  numbers( *new vector<int> )
{
  cout << "matrix with vector size = " << numbers.size() << " created\n";
}

vlMatrix::~vlMatrix()
{
  delete &numbers;
}


vlMatrix::vlMatrix( const vlMatrix& orig ):
  numbers( *new vector<int> )
{
  numbers = orig.get_numbers();
  cout << "copy size = " << numbers.size() << "\n";
}

vlMatrix& vlMatrix::operator= ( const vlMatrix& orig )
{
  set_numbers( orig.get_numbers() );
  cout << "operator= : " << numbers.size() << "=" << orig.get_numbers().size() << "\n";
  return *this;
}

vlMatrix::vlMatrix( int size ):
  numbers( *new vector<int>( size ) )
{
  cout << "matrix with vector size = " << numbers.size() << " created\n";
}

int vlMatrix::operator( int i, int j )
{
  return numbers[ i * numbers.size() + j ];
}

#endif
