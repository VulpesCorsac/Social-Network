#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main ()
	{
	FILE* f = fopen ("omg.txt", "r");
	
	printf ("%d", putc ('B', f));
	
	fclose (f);	
	
	getch ();
		
	return 0;
	}
