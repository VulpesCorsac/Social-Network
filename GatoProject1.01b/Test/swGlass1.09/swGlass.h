#ifndef _SW_GLASS_H_
#define _SW_GLASS_H_

//---------------------------------------------------------------------------
/*

1.04 version
1.05 version
1.06 version
1.07 version
1.08 version

*/
//---------------------------------------------------------------------------

#include <windows.h>
#include <time.h>

#include <iostream>
#include <string>
#include <list>
#include <vector>

#include "swPixel.h"
#include "swMessage.h"
#include "swMouse.h"

//---------------------------------------------------------------------------

using std :: list;
using std :: vector;
using std :: iterator;
using std :: string;
using std :: cerr;
using std :: cout;
using std :: endl;

//---------------------------------------------------------------------------

LRESULT CALLBACK WindowProcedure (HWND   hwnd, 
								  UINT   msg, 
								  WPARAM wparam, 
								  LPARAM lparam);

//---------------------------------------------------------------------------

namespace Swamp
	{

//---------------------------------------------------------------------------

//Array of default messagies

bool on_destroy (int, int);

//---------------------------------------------------------------------------

const string DEFAULT_TITLE ("Swamp!");

enum DEFAULT_WINDOW_PARAMS
	{
	SIZE_WND_X = 640,
	SIZE_WND_Y = 480,
	
	WINDOW_STYLE = CS_DBLCLKS
	};

enum CLASS_NAME_PARAMS
	{
	CLASS_NAME_LENGTH   = 32,
	MIN_LETTER_FOR_NAME = 'a',
	MAX_LETTER_FOR_NAME = 'Z' 
	};

//---------------------------------------------------------------------------

typedef int win_mouse_t;

//---------------------------------------------------------------------------

class Glass
	{
	private:
		string& class_name_;
		string& title_;
		
		list<Message>& msgs_;
		
		HWND 	  hwnd_;
		HDC  	  dc_;
		HINSTANCE hinst_;
		
		Mouse<win_mouse_t>& mc_;

		//---------------------

		Glass 			  (const Glass&); //{}
		Glass& operator = (const Glass&); //{}

		bool init (int sx 			= SIZE_WND_X, 
				   int sy 			= SIZE_WND_Y,
				   int style 		= WINDOW_STYLE, 
				   HICON icon 		= LoadIcon (NULL, IDI_APPLICATION), 
				   HICON small_icon = LoadIcon (NULL, IDI_APPLICATION));

		bool show ();

		bool add_array_def_msgs ();

	public:
	
		Glass ();	
		Glass (int sx, int sy, 		 
			   const char* title 		= DEFAULT_TITLE.c_str (), 
			   int style				= WINDOW_STYLE, 
			   const char* icon 		= 0,
			   const char* small_icon   = 0);
	   ~Glass ();	
	
		bool fly (void (*on_idle) () = 0);

		const list<Message>::iterator add_msg (const Message&  msg);
		bool         del_msg (const list<Message>::iterator& iter);

		int sx () const;
		int sy () const;

		HDC       dc   () const {return dc_;   }
		HWND      hwnd () const {return hwnd_; }
		HINSTANCE inst () const {return hinst_;}
		
		const list<Message>       msgs () const {return msgs_;}
		const Mouse<win_mouse_t>& mc   () const {return mc_;}
		
		list<Message>::iterator msgs_end   () const {return msgs_.end   ();}
		list<Message>::iterator msgs_begin () const {return msgs_.begin ();}
		
		bool set_title (char* new_title) {return SetWindowText (hwnd (), 
																new_title);}

		bool set_point (int x, int y, const swWinPixel& color);
	
		win_mouse_t mx () const {return mc ().x ();}		
		win_mouse_t my () const {return mc ().y ();}		
		win_mouse_t mz () const {return mc ().z ();}		

		bool left_mb  () const {return mc ().left_b  ();}
		bool right_mb () const {return mc ().right_b ();}

		bool get_win_mouse (int coords);
		bool set_mouse_btn (bool lb, bool rb) {mc_.left_b  (lb);
											   mc_.right_b (rb);}
		};

//---------------------------------------------------------------------------

Glass :: Glass ():
	class_name_ (*new string),
	title_      (*new string (DEFAULT_TITLE.c_str ())),
	msgs_       (*new list<Message>),
	hwnd_       (0),
	dc_         (0),
	hinst_      (GetModuleHandle (NULL)),
	mc_         (*new Mouse<win_mouse_t>)
	{
	if (!init ()) cerr << "Error in initing Swamp :: Glass window!\n";
	else          add_array_def_msgs ();
	}
	
Glass :: Glass (int sx, int sy, 		 
		 		const char* title, 
		 		int style, 
		 		const char* icon,
		 		const char* small_icon):
	class_name_ (*new string),
	title_      (*new string (title)),
	msgs_       (*new list<Message>),
	hwnd_       (0),
	dc_         (0),
	hinst_      (GetModuleHandle (NULL)),
	mc_         (*new Mouse<win_mouse_t>)
	{
	if (!init (sx, sy, style, LoadIcon (hinst_, icon),
						 	  LoadIcon (hinst_, small_icon)))
		cerr << "Error in initing Swamp :: Glass window!\n";
	else add_array_def_msgs (); 
	}

Glass :: ~Glass ()
	{
	delete& class_name_;
	delete& title_;
	
	delete& msgs_;
	delete& mc_;

	hwnd_  = 0;
	dc_    = 0;
	hinst_ = 0;
	}

//---------------------------------------------------------------------------

bool Glass :: init (int sx, int sy, int style, HICON icon, HICON small_icon)
	{
	srand (time (0));

	for (int i = 0; i < CLASS_NAME_LENGTH; i ++) 
		{
		class_name_ [i] = MIN_LETTER_FOR_NAME + 
						  rand () % (MAX_LETTER_FOR_NAME - 
									 MIN_LETTER_FOR_NAME);	
		}
	
	WNDCLASSEX swamp_window = {0};

	swamp_window.lpszClassName = class_name_.c_str ();
	swamp_window.lpfnWndProc   = WindowProcedure;
	swamp_window.style         = style;
	swamp_window.hInstance     = hinst_;
    swamp_window.cbSize        = sizeof (WNDCLASSEX);
	swamp_window.hIcon         = icon;
    swamp_window.hIconSm       = small_icon;
    swamp_window.hCursor 	   = LoadCursor (NULL, IDC_ARROW);
    swamp_window.lpszMenuName  = NULL;
    swamp_window.cbClsExtra    = 0;
    swamp_window.cbWndExtra    = 0;
    swamp_window.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);

    if (!RegisterClassEx (&swamp_window)) 
		{
		cerr << "Can't register so noob class! :(\n";
		return false;
		}

 	hwnd_ = CreateWindow (class_name_.c_str (), 
                          title_.c_str      (), 
                          WS_OVERLAPPEDWINDOW,
	                      CW_USEDEFAULT, 
                          CW_USEDEFAULT, 
                          sx, 
                          sy, 
                          NULL, 
                          NULL, 
                          hinst_, 
                          NULL);

	dc_ = GetDC (hwnd_);
	
	return show ();
	}

bool Glass :: show ()
	{
	return (!ShowWindow   (hwnd_, SW_SHOW) &&
			 UpdateWindow (hwnd_));
	}

bool Glass :: fly (void (*on_idle) ())
	{
	MSG msg = {0};
	msg.message = 0;
	
	while (msg.message != WM_QUIT)
		{
		if (on_idle) on_idle ();
		if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
			{
			TranslateMessage (&msg);
			DispatchMessage  (&msg);
			}
		}
	
	return true;
	}

int Glass :: sx () const 
	{
    RECT wnd = {0}; 
    GetClientRect (hwnd_, &wnd);  

    return wnd.right - wnd.left;
	}

int Glass :: sy () const 
	{
    RECT wnd = {0}; 
    GetClientRect (hwnd_, &wnd); 

    return wnd.bottom - wnd.top;
	}

//---------------------------------------------------------------------------

const list<Message>::iterator Glass :: add_msg (const Message&  msg)
	{
	msgs_.push_front (msg);
	
	return msgs_.begin ();
	}

bool Glass :: del_msg (const list<Message>::iterator& iter)
	{
	msgs_.erase (iter);
	
	return true;
	}

bool Glass :: add_array_def_msgs ()
	{
	add_msg (Message (WM_DESTROY,   on_destroy));

	return true;
	}

bool Glass :: set_point (int x, int y, const swWinPixel& color)
	{
	SetPixel (dc (), x, y, RGB (color [R_COLOR_POS], 
								color [G_COLOR_POS], 
								color [B_COLOR_POS]));
	
	return true;
	}

bool Glass :: get_win_mouse (int coords)
	{
    int x_coord_mask = 0x0000ffff;
    int y_coord_mask = 0xffff0000;

	mc_.x  (coords & x_coord_mask);
	mc_.y ((coords & y_coord_mask) >> sizeof (win_mouse_t) * 4);
	mc_.z  (0);
	
	return true;
	}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//Non-class Functions
//---------------------------------------------------------------------------

bool on_destroy (int, int)
	{
	PostQuitMessage (0);	
	return true;
	}

//---------------------------------------------------------------------------

	}; //end of namespace Swamp

//---------------------------------------------------------------------------

Swamp :: Glass __GLASS_WND; //DECLARATION MAIN OBJECT

//---------------------------------------------------------------------------

bool on_mouse_move (int, int coords)
	{
	__GLASS_WND.get_win_mouse (coords);
	
	return true;
	}

bool on_lb_down (int, int)
	{
	__GLASS_WND.set_mouse_btn (Swamp :: MB_DOWN, __GLASS_WND.right_mb ()); 

	return true;
	}

bool on_lb_up (int, int)
	{
	__GLASS_WND.set_mouse_btn (Swamp :: MB_UP,   __GLASS_WND.right_mb ()); 

	return true;
	}

bool on_rb_down (int, int)
	{
	__GLASS_WND.set_mouse_btn (__GLASS_WND.left_mb (), Swamp :: MB_DOWN); 

	return true;
	}

bool on_rb_up (int, int)
	{
	__GLASS_WND.set_mouse_btn (__GLASS_WND.left_mb (), Swamp :: MB_UP); 

	return true;
	}


bool use_handle_mouse () 
	{
	__GLASS_WND.add_msg (Swamp :: Message (WM_MOUSEMOVE, on_mouse_move));

	__GLASS_WND.add_msg (Swamp :: Message (WM_LBUTTONDOWN, on_lb_down));
	__GLASS_WND.add_msg (Swamp :: Message (WM_LBUTTONUP,   on_lb_up));
	__GLASS_WND.add_msg (Swamp :: Message (WM_RBUTTONDOWN, on_rb_down));
	__GLASS_WND.add_msg (Swamp :: Message (WM_RBUTTONUP,   on_rb_up));

	return true;
	}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT msg, WPARAM wparam, 
													   LPARAM lparam)
	{

	for (list<Swamp :: Message>::iterator cnt = __GLASS_WND.msgs_begin (); 
		 cnt != __GLASS_WND.msgs_end (); 
		 cnt ++)
		{
		if (cnt -> id () == msg) {cnt -> action (wparam, lparam);}
		}

    return DefWindowProc (hwnd, msg, wparam, lparam);
	}

//---------------------------------------------------------------------------

typedef Swamp :: Message swMsg;
typedef Swamp :: Glass   swGlass;

typedef list<swMsg>::iterator swIter;

//---------------------------------------------------------------------------

#ifdef SW_USING_OPEN_GL
	#include "swGlassGL.h"
	#include "swPixel.h"
	#include "swBuffer.h"
#endif

//---------------------------------------------------------------------------

#endif //_SW_GLASS_H_
