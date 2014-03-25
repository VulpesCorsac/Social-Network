#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

//#define SW_REPORT
//#define SW_TEST

#include "../Resources/swResources.h"
#include "../ProjectFiles/swSNetContainer.h"

swSNetContainer MAIN_CONTAINER;

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

		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		MAIN_CONTAINER.on_mouse_mode_change (MAIN_CONTAINER.get_mx            (lparam), 
											 MAIN_CONTAINER.get_my            (lparam), 
											 MAIN_CONTAINER.get_mouse_pressed (wparam));
			break;

		case WM_SIZE:
			OnSize2D             (hwnd);
			
			float static ft1 = true;
			if (ft1) ft1 = false;
			else MAIN_CONTAINER.clear (GetDC (hwnd));
			break;

		case WM_PAINT:
			float static ft2 = true;
			if (ft2) ft2 = false;
			else 
				{
				MAIN_CONTAINER.clear (GetDC (hwnd));
				MAIN_CONTAINER.on_mouse_mode_change 
							   (MAIN_CONTAINER.get_mx            (-1), 
								MAIN_CONTAINER.get_my            (-1), 
								MAIN_CONTAINER.get_mouse_pressed (-1));
				}
			break;
			}

	return DefWindowProc (hwnd, msg, wparam, lparam);
	}
