#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>

#include "vlSqMatrix.h"

using namespace std;

#define input_file_matrx "OUTPUT_2.cpp"
#define input_file_names "names.txt"
#define stream_file      "bok.txt"

#define RAZMER 103

int main()
{

  FILE* input;
  if ( ( input = fopen( "LASTOUT.TXT", "r" ) ) == NULL )
  {
    cerr << "BAD OPEN" << "LASTOUT.TXT" << endl;
  }

  int count = 0;

  ofstream out( "bok.txt" );

  vlSqMatrix matr(RAZMER);

  for ( int i = 0 ; i < RAZMER ; i ++ )
  {
    for ( int j = 0 ; j < RAZMER ; j ++ )
    {
      fscanf( input , "%d" , &matr(i,j) );
    }
  }

  for ( int i = 1 ; i < RAZMER ; i ++ )
  {
    for ( int j = i+1 ; j < RAZMER ; j ++ )
    {
      matr(i,j) = matr(j,i);
    }
  }

  out << matr;

  fclose( input );
  out.close();

  system( "PAUSE" );
  return 0;
}
