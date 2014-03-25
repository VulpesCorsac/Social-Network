#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using std::cout;

char english( char rus );

int main()
{
  FILE* rus = fopen( "to_aisee.txt", "r" );
  if( rus == NULL ) return 1;

  FILE* eng = fopen( "to_aisee_eng.txt", "w" );
  if( eng == NULL ) return 1;

  char c = 0;

  while( ( c = fgetc( rus ) ) != ';' )
  {
    fputc( english( c ), eng );
    cout << c ;
  }

  fclose( rus );
  fclose( eng );

  system( "PAUSE" );
  return 0;
}

//Vlad
char english( char rus )
  {
//�������������������������������
    switch( rus )
      {
      case '�': rus = 'a';
                break;
      case '�': rus = 'A';
                break;
      case '�': rus = 'b';
                break;
      case '�': rus = 'B';
                break;
      case '�': rus = 'v';
                break;
      case '�': rus = 'V';
                break;
      case '�': rus = 'g';
                break;
      case '�': rus = 'G';
                break;
      case '�': rus = 'd';
                break;
      case '�': rus = 'D';
                break;
      case '�': rus = 'e';
                break;
      case '�': rus = 'E';
                break;
      case '�': rus = '#';
                break;
      case '�': rus = '#';
                break;
      case '�': rus = 'z';
                break;
      case '�': rus = 'Z';
                break;
      case '�': rus = 'i';
                break;
      case '�': rus = 'I';
                break;
      case '�': rus = 'k';
                break;
      case '�': rus = 'K';
                break;
      case '�': rus = 'l';
                break;
      case '�': rus = 'L';
                break;
      case '�': rus = 'm';
                break;
      case '�': rus = 'M';
                break;
      case '�': rus = 'n';
                break;
      case '�': rus = 'N';
                break;
      case '�': rus = 'o';
                break;
      case '�': rus = 'O';
                break;
      case '�': rus = 'p';
                break;
      case '�': rus = 'P';
                break;
      case '�': rus = 'r';
                break;
      case '�': rus = 'R';
                break;
      case '�': rus = 's';
                break;
      case '�': rus = 'C';
                break;
      case '�': rus = 't';
                break;
      case '�': rus = 'T';
                break;
      case '�': rus = 'u';
                break;
      case '�': rus = 'U';
                break;
      case '�': rus = 'f';
                break;
      case '�': rus = 'F';
                break;
      case '�': rus = 'h';
                break;
      case '�': rus = 'H';
                break;
      case '�':
      case '�': rus = '@';
                break;
      case '�':
      case '�': rus = '!';
                break;
      case '�': rus = '$';
                break;
      case '�': rus = '%';
                break;
      case '�': rus = '^';
                break;
      case '�': rus = '&';
                break;
      case '�': rus = '^';
                break;
      case '�': rus = 'a';
                break;
      case '�': rus = 'u';
                break;
      case '�': rus = '*';
                break;
      case '�': rus = '*';
                break;
      default : return rus;
                break;
      };
  return rus;
  }
