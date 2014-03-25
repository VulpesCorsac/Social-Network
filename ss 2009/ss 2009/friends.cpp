#include "vlSqMatrix.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;


int main()
	{

  const int size = 120;

  ofstream bok;
  bok.open( "bok.txt" );

  FILE* inp = fopen( "OUTPUT.TXT", "r" );

  vlSqMatrix matr(size);

  //read and bool the matrix
  
  char tmp = '0';
  for( int i = 0 ; i < size ; i ++ )
  {
    for( int j = 0 ; j < size ; j ++ )
    {
    //in >> i >> " ";
    //fscanf( inp, "%c", &tmp );
    tmp = fgetc( inp );
    cout << ( matr( i , j ) = (bool)( tmp - '0' ) );
    }
  }

  //set 1 on diag
  for( int i = 0 ; i < size ; i ++ )
  {
    matr( i, i ) = 1;
  }

  bok << matr;

  vlSqMatrix answers(size);

  for ( int el = 0 ; el < size ; ++ el )
  {
    for ( int fr = 0 ; fr < size ; ++ fr )
    //for ( int fr = el+1 ; fr < size ; ++ fr )
    {
      for ( int j = 0 ; j < size ; ++ j )
      {
        if( matr(el,j) && matr(fr,j) )
        {
          answers(el,fr) ++ ;     
        }
      }
    }
  }

  ofstream out;
  out.open( "answer_file.txt" );

  //printing answer matrix to FILE
  for( int i = 0 ; i < size ; i ++ )
  {
    for( int j = 0 ; j < size ; j ++ )
    {
      out << answers( i, j ) << " " ;
      //fprintf( file, "%d ", answers(i,j) );
    }
  out << "\n";
  //fprintf( file, "\n" );
  }


  fclose( inp );
  bok.close();
  out.close();

/*  int pers = 0;
  cin >> pers;
  for( int i  = 0 ; i < size ; i ++ )
  {
    if( answers(pers,i) )
    {
      cout << matr.get_numbers()[i] << "\t" << answers(pers,i) << '\n';
    }
  }
*/

  system( "PAUSE" );
	return 0;

  }
