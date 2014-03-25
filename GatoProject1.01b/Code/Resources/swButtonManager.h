#ifndef _SW_BUTTON_MANAGER_H_
#define _SW_BUTTON_MANAGER_H_

//==============================================================================

#include "swButton.h"

//==============================================================================

class swButtonManager
	{
	private:	
		swButton** objs_;
		int        hei_spc_;
		int        size_;
		int        counter_;
		int        x0_, y0_;
		
		swButtonManager 			();				   //{}
		swButtonManager             (swButtonManager&);//{}
		swButtonManager& operator = (swButtonManager&);//{}
	
		bool test_mouse_coords (int index, int mx, int my, int mode);

		int get_x              (int index);
		int get_y              (int index); 

	public:
		swButtonManager    (int x0, int y0, int size, int height);
	   ~swButtonManager    ();
		
		bool draw          ();
 
		bool add_button    (swButton& but);	


		bool refresh 	   ();
	};

//==============================================================================

int swButtonManager :: get_x (int index) 
	{
	return x0_;
	}

int swButtonManager :: get_y (int index) 
	{
	int res = y0_;

	for (int i = 0; i < index; i ++)
		{
		res += hei_spc_;
		res += objs_ [i] -> sy (MODE_UNTOUCHED);	
		}	

	return res;
	}

//==============================================================================

swButtonManager :: swButtonManager (int x0, int y0, int size, int height):
	objs_    (new swButton* [size]),
	hei_spc_ (height),
	size_    (size),
	counter_ (0),
	x0_      (x0),
	y0_      (y0)
	{
		
	}

swButtonManager :: ~swButtonManager ()
	{
	delete [] objs_;
	}

bool swButtonManager :: add_button (swButton& but)
	{
	objs_ [counter_] = &but;
	
	counter_ ++;
	
	return true;
	}	

//==============================================================================

bool swButtonManager :: test_mouse_coords (int index, int mx, int my, int mode)
	{
	return (mx > get_x (index)                              &&
			mx < get_x (index) + objs_ [index] -> sx (mode) &&
			my > get_y (index)                              &&
			my < get_y (index) + objs_ [index] -> sy (mode));
	}

//==============================================================================


bool swButtonManager :: refresh ()
	{
	Swamp :: win_mouse_t mx = __GLASS_WND.mx ();
	Swamp :: win_mouse_t my = __GLASS_WND.my ();

	bool pressed = __GLASS_WND.left_mb ();
	
	for (int i = 0; i < counter_; i ++)
		{
		if (pressed)
			{
			if (test_mouse_coords (i, mx, my, MODE_TOUCHED))
				{
				objs_ [i] -> mode (MODE_PRESSED);
				}

			else
				{
			    objs_ [i] -> mode (MODE_UNTOUCHED);
				} 

			}

		else
			{
			if (test_mouse_coords (i, mx, my, MODE_UNTOUCHED))
				{
				if (objs_ [i] -> mode () == MODE_PRESSED)
					{
					objs_ [i] -> draw (__GLASS_WND.dc (), get_x (i), get_y (i));

					objs_ [i] -> action ();
					}
				
			    objs_ [i] -> mode (MODE_TOUCHED);	
			    }
			
			else
				{
			    objs_ [i] -> mode (MODE_UNTOUCHED);	
				} 
			}
		
    	//glClearColor (PHONE_R, PHONE_G, PHONE_B, 1.0f); 
    	//glClear      (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//SwampBuffers ();
	
		objs_ [i] -> draw (__GLASS_WND.dc (), get_x (i), get_y (i));
		}

	return true;		
	}

#endif
