#include <cstdlib>
#include <iostream>

#include "vlSqMatrix.h"

#include <iostream>
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
  vlSqMatrix m( 4 );

  int size = m.size();

  cout << size << "\n" << m << endl;

  for( int i = 0 ; i < size ; i ++ )
  {
    for( int j = 0 ; j < size ; j ++ )
    {
      m(i,j) = i*2 + j;
    }
  }

  cout << m << "\n";

  m.print_raw(2);
  m.print_col(3);

  system("PAUSE");
  return EXIT_SUCCESS;
}
