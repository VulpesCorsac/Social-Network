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
//àáâãäåæçèêëìíîïðñòóôõö÷øùúûüýþÿ
    switch( rus )
      {
      case 'à': rus = 'a';
                break;
      case 'À': rus = 'A';
                break;
      case 'á': rus = 'b';
                break;
      case 'Á': rus = 'B';
                break;
      case 'â': rus = 'v';
                break;
      case 'Â': rus = 'V';
                break;
      case 'ã': rus = 'g';
                break;
      case 'Ã': rus = 'G';
                break;
      case 'ä': rus = 'd';
                break;
      case 'Ä': rus = 'D';
                break;
      case 'å': rus = 'e';
                break;
      case 'Å': rus = 'E';
                break;
      case 'æ': rus = '#';
                break;
      case 'Æ': rus = '#';
                break;
      case 'ç': rus = 'z';
                break;
      case 'Ç': rus = 'Z';
                break;
      case 'è': rus = 'i';
                break;
      case 'È': rus = 'I';
                break;
      case 'ê': rus = 'k';
                break;
      case 'Ê': rus = 'K';
                break;
      case 'ë': rus = 'l';
                break;
      case 'Ë': rus = 'L';
                break;
      case 'ì': rus = 'm';
                break;
      case 'Ì': rus = 'M';
                break;
      case 'í': rus = 'n';
                break;
      case 'Í': rus = 'N';
                break;
      case 'î': rus = 'o';
                break;
      case 'Î': rus = 'O';
                break;
      case 'ï': rus = 'p';
                break;
      case 'Ï': rus = 'P';
                break;
      case 'ð': rus = 'r';
                break;
      case 'Ð': rus = 'R';
                break;
      case 'ñ': rus = 's';
                break;
      case 'Ñ': rus = 'C';
                break;
      case 'ò': rus = 't';
                break;
      case 'Ò': rus = 'T';
                break;
      case 'ó': rus = 'u';
                break;
      case 'Ó': rus = 'U';
                break;
      case 'ô': rus = 'f';
                break;
      case 'Ô': rus = 'F';
                break;
      case 'õ': rus = 'h';
                break;
      case 'Õ': rus = 'H';
                break;
      case 'ö':
      case 'Ö': rus = '@';
                break;
      case '×':
      case '÷': rus = '!';
                break;
      case 'ø': rus = '$';
                break;
      case 'ù': rus = '%';
                break;
      case 'ú': rus = '^';
                break;
      case 'û': rus = '&';
                break;
      case 'ü': rus = '^';
                break;
      case 'ý': rus = 'a';
                break;
      case 'þ': rus = 'u';
                break;
      case 'ÿ': rus = '*';
                break;
      case 'ß': rus = '*';
                break;
      default : return rus;
                break;
      };
  return rus;
  }
