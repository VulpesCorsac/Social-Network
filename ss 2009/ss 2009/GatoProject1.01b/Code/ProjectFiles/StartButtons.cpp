#include "../Resources/swResources.h"
#include "../ProjectFiles/swSNetContainer.h"

swSNetContainer MAIN_CONTAINER;

bool on_mouse_act (int, int)
	{
	MAIN_CONTAINER.on_mouse_mode_change ();// get_mouse_pressed (wparam));
	
	return true;	
	}


int main ()
	{ 
	use_handle_mouse ();

	__GLASS_WND.add_msg (swMsg (WM_MOUSEMOVE,   on_mouse_act));
	__GLASS_WND.add_msg (swMsg (WM_LBUTTONDOWN, on_mouse_act));
	__GLASS_WND.add_msg (swMsg (WM_LBUTTONUP,   on_mouse_act));

	__GLASS_WND.fly ();

	return 0;
	}
/*
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
*/
