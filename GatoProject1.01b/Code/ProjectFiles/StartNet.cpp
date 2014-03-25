#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

//#define SW_REPORT
//#define SW_TEST

#include "../Resources/swResources.h"
#include "../ProjectFiles/swSNetStartContainer.h"

swSNetStartContainer MAIN_CONTAINER;

int main ()
	{ 
    swGL_init initing (MAIN_CONTAINER.wnd ());

	MAIN_CONTAINER.process ();

	return 0;
	}

LRESULT CALLBACK MainWndProc (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{

	switch (msg)
    	{
		case WM_DESTROY:
			PostQuitMessage (0);
			break;

		case WM_KEYDOWN:
			MAIN_CONTAINER.on_key (wparam);
			break;

		case WM_SIZE:
			OnSize2D (hwnd);

			bool static ft = true;
			if (!ft) MAIN_CONTAINER.on_key (VK_ENTER);
			else ft = false;
			
			break;
        }

	return DefWindowProc (hwnd, msg, wparam, lparam);
	}
