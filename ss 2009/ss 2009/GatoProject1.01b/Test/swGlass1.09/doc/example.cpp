#define SW_USING_OPEN_GL

#include "../swGlass.h"

using namespace Swamp;

bool on_left_click (int, int coords)
	{
   	cout << "Mouse Win32 (" << __GLASS_WND.mx () << ", " << __GLASS_WND.my () << ")" << endl;

	return true;	
	}

bool on_right_click (int, int coords)
	{
	__GLASS_GL_OBJ.get_gl_mouse ();
   
	bool static ft = true;
	if (ft)
		{	
	    glClearColor (03.f, 0.9f, 0.4f, 1.0f); 
	    glClear      (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		ft = false;
		}
	
	glColor3f (0, 0, 1);
			
	glPointSize (3);

	glBegin (GL_POINTS);
		{
		glVertex2f (__GLASS_GL_OBJ.mx (), __GLASS_GL_OBJ.my ());	
		}
	glEnd ();

	SwampBuffers ();

	return true;	
	}

bool on_key (int, int coords)
	{
	cout << "No Swamp!" << endl;

	return true;	
	}


int main ()
	{
	use_handle_mouse ();
		
	swMsg on_key_msg (WM_KEYDOWN, on_key);
		
	__GLASS_WND.add_msg (swMsg (WM_LBUTTONDOWN, on_left_click));
	__GLASS_WND.add_msg (swMsg (WM_RBUTTONDOWN, on_right_click));
	
	swIter i1 = __GLASS_WND.add_msg (on_key_msg);
	
	__GLASS_WND.del_msg (i1);
	
	__GLASS_WND.fly ();

	return 0;
	}
