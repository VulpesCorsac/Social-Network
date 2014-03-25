//..#include <windows.h>
//#include <gl/gl.h>
//#include <gl/glu.h>

//#define SW_REPORT
//#define SW_TEST

#include "../Resources/swResources.h"
#include "../ProjectFiles/swSNetStartContainer.h"

swSNetStartContainer MAIN_CONTAINER;

bool on_key (int key, int)
	{
	MAIN_CONTAINER.on_key (key);
	
	return true;	
	}

int main ()
	{ 
	use_handle_mouse ();

	__GLASS_WND.add_msg (swMsg (WM_KEYDOWN, on_key));

	__GLASS_WND.fly ();

	return 0;
	}
