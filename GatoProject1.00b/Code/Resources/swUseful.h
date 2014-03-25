#ifndef _SW_USEFUL_H_
#define _SW_USEFUL_H_

//=============================================================================

#ifdef _WINDOWS_H

LRESULT CALLBACK MainWndProc (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

#endif

//=============================================================================

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <math.h>

using std :: cout;
using std :: cin;
using std :: string;
using std :: exception;
using std :: endl;

void OutLogo () 
               
     {
     cout << endl;

     cout << "*********************************************************************" << endl;
     cout << "*===================================================================*" << endl;
     cout << "*=                                                                 =*" << endl;
     cout << "*=           ===                                   ======          =*" << endl;
     cout << "*=          =   =                                  =     =         =*" << endl;
     cout << "*=          =                                      =     =         =*" << endl;
     cout << "*=           ==     =        =     =     ==   ==   ======          =*" << endl;
     cout << "*=             =    =        =    = =    = = = =   =               =*" << endl;
     cout << "*=              =   =   ==   =   =   =   =  =  =   =               =*" << endl;
     cout << "*=         =    =    = =  = =    == ==   =     =   =               =*" << endl;
     cout << "*=          ====     ==    ==    =   =   =     =   =               =*" << endl;
     cout << "*=                                                                 =*" << endl;
     cout << "*===================================================================*" << endl;
     cout << "*********************************************************************" << endl;

     cout << endl;
     }
     
#ifdef _WINDOWS_H

bool swShowError (char* error, char* title = "SW_ERROR")
      {
      MessageBox (0, error, title, MB_ICONERROR);

      return true;
      }

bool swAsk (char* ask, char* title = "SW_QUESTION")
      {
      if (MessageBox (0, ask, title, MB_YESNO | MB_ICONQUESTION) == IDNO) return false;
      return true;
      }

bool swInfo (char* info, char* title = "SW_INFO")
      {
	  MessageBox (0, info, title, MB_ICONINFORMATION);
      return true;
      }

#endif

//=============================================================================
#ifdef _WINDOWS_H

class swWindow
	{
	private:
		string& title_;
		string& wnd_class_name_;
		
		int sx_;
		int sy_;	
		
		HINSTANCE h_instance_;
		HWND      h_window_;
		
		HDC dc_;
	
		swWindow             ();          //{}
		swWindow             (swWindow&); //{}
		swWindow& operator = (swWindow&); //{}

		bool show    ();
		bool init    (int size_x, int size_y, int x0, int y0);

	public:
		const HDC&       dc   () const {return dc_;        }
		const HWND&      hwnd () const {return h_window_;  }
		const HINSTANCE& inst () const {return h_instance_;}
		
		bool process (void (*on_idle) () = 0);
		
		int s_x () const;	
		int s_y () const;	
		
		swWindow (const char* title, int size_x, int size_y, int x0 = CW_USEDEFAULT, 
													         int y0 = CW_USEDEFAULT);
       ~swWindow ();
	};

//==============================================================================

swWindow :: swWindow (const char* title, int size_x, int size_y, int x0, int y0):
	title_          (*new string (title)),
	wnd_class_name_ (*new string),
	sx_             (size_x),
	sy_             (size_y),
	h_instance_     (GetModuleHandle (NULL)),
	h_window_       (NULL),
	dc_             (NULL)
    {
    init (size_x, size_y, x0, y0);
    }

swWindow :: ~swWindow ()
	{
	UnregisterClass (wnd_class_name_.c_str (), h_instance_);
	
	delete &title_;
	delete &wnd_class_name_;
	sx_             = 0;
	sy_             = 0;
	h_instance_     = 0;
	h_window_       = 0;
	dc_             = 0;
	}

//==============================================================================

bool swWindow :: show ()
	{
	ShowWindow   (h_window_, SW_SHOW);
	UpdateWindow (h_window_);
	
	return true;
	}

bool swWindow :: process (void (*on_idle) ())
	{
	MSG msg = {0};
	msg.message = 0;
	
	while (msg.message != WM_QUIT)
		{
		if (on_idle) on_idle ();
		if (PeekMessage (& msg, NULL, 0, 0, PM_REMOVE))
			{
			TranslateMessage (& msg);
			DispatchMessage  (& msg);
			}
		}
	
	return true;
	}



bool swWindow :: init (int size_x, int size_y, int x0, int y0)
	{
	wnd_class_name_ = "stnd_class";
	WNDCLASS wnd_class_ = {0};
	
	wnd_class_.lpszClassName = wnd_class_name_.c_str ();
	wnd_class_.lpfnWndProc   = MainWndProc;
	wnd_class_.style         = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	wnd_class_.hInstance     = h_instance_;
	wnd_class_.hIcon         = NULL;
	wnd_class_.hCursor       = LoadCursor (NULL, IDC_ARROW);
	wnd_class_.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);
	wnd_class_.lpszMenuName  = NULL;
	
	wnd_class_.cbClsExtra = 0;
	wnd_class_.cbWndExtra = 0;
	
	RegisterClass (& wnd_class_);
	

	h_window_ = CreateWindow (wnd_class_name_.c_str (), title_.c_str (), WS_OVERLAPPEDWINDOW,
	                      x0, y0, size_x, size_y, NULL, NULL, h_instance_, NULL);
	
	dc_  = GetDC (h_window_);
	
	show    ();
	
	return true;
	}

int swWindow :: s_x () const 
	{
    RECT wnd = {0}; 
    GetClientRect (h_window_, &wnd);  

    return wnd.right - wnd.left;
	}

int swWindow :: s_y () const 
	{
    RECT wnd = {0}; 
    GetClientRect (h_window_, &wnd); 

    return wnd.bottom - wnd.top;
	}


#endif

#ifdef __gl_h_
#ifdef __glu_h__
#ifdef _WINDOWS_H

class swGL_init
	{
	private:
		HGLRC           rc_;
		const swWindow* wind_;
		
		swGL_init ();
		
		bool init         ();
		bool set_pix_form (HDC dc);
	
	public:
		swGL_init (const swWindow* wind);
	   ~swGL_init ();
	};
      
swGL_init :: swGL_init () :
	rc_   (NULL),
	wind_ (NULL)
	{}

swGL_init :: swGL_init (const swWindow* wind) :
	rc_   (NULL),
	wind_ (wind)
	{
	init ();
	
	glClearDepth(1.0f);
	glEnable    (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);
	glHint      (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	}
	
swGL_init :: ~swGL_init ()
	{
	if (rc_)
		{
		wglMakeCurrent  (wind_ -> dc (), 0);
		wglDeleteContext(rc_);
		}
	}

bool swGL_init :: init ()
	{
	if (!set_pix_form (wind_ -> dc ())) return false;
	
	rc_ = wglCreateContext (wind_ -> dc ());
	wglMakeCurrent         (wind_ -> dc (), rc_);
	
	return true;
	}

bool swGL_init :: set_pix_form (HDC dc)
	{
	int pix_form = 0;
	PIXELFORMATDESCRIPTOR pfd = {0};
	
	ZeroMemory (&pfd, sizeof (PIXELFORMATDESCRIPTOR));
	
	pfd.nSize      = sizeof (PIXELFORMATDESCRIPTOR);
	pfd.nVersion   = GL_VERSION_1_1;
	pfd.dwFlags    = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	
	pix_form = ChoosePixelFormat (dc, &pfd);
	
	if (!pix_form)                           return false;
	if (!SetPixelFormat(dc, pix_form, &pfd)) return false;
	
	return true;
	}

void OnSize (HWND hwnd, float corner = 60, float z_near = 0.1, float z_far = 20)
    {
	
    RECT client = {0, 0, 0, 0};
    GetClientRect (hwnd, &client);
	
	if (client.top   == client.bottom || 
        client.right == client.left) return;
	
    glViewport     (0, 0, client.right, client.bottom);
    gluPerspective (corner, (client.right  - client.left) / //!!!int, not float 
                            (client.bottom - client.top), z_near, z_far);
    
	}


bool OnSize2D (HWND hwnd)
    {
    static RECT new_client = {0, 0, 0, 0};
    static RECT old_client = {0, 0, 0, 0};

	old_client = new_client;

    GetClientRect (hwnd, &new_client);

	if (new_client.top    == new_client.bottom || 
        new_client.right  == new_client.left   ||
		old_client.right  == 0                 ||
		old_client.bottom == 0) return false;

    glViewport (0, 0, new_client.right, new_client.bottom);

	float x_new_to_old = (float) new_client.right  / (float) old_client.right; 
	float y_new_to_old = (float) new_client.bottom / (float) old_client.bottom; 

	glOrtho (- x_new_to_old, 
		  	   x_new_to_old,
			 - y_new_to_old, 
			   y_new_to_old,
			   1,
			 - 1);

	return true;
	}


#endif
#endif
#endif

//=============================================================================

/*
class swError : public exception
	{
	private:
		string* descrip_;
	
	public:      
		swError ()              throw () : exception (), 
										   descrip_      (0)
										   {}
		swError (char* descrip) throw () : exception (), 
										   descrip_      (new string (descrip)) 
										   {}
	   ~swError ()              throw ()   {
										   delete descrip_; 
										   descrip_ = 0;
										   }
	
	const char* what () 
		{
		if (descrip_) return descrip_ -> c_str ();
		else return 0;      
		}
	};
*/


//=============================================================================

#ifdef _WINDOWS_H

bool swAss (bool tested, const char* filename, const int line, const char* funcname)
   {
   if (tested) return true;

   char buff [256] = {0};

   sprintf (buff, "File Name: %s\nString Number: %d\nFunction Name: %s\nswAssert has returned false!",
            filename, line, funcname);

   swShowError (buff);

   return false;
   }

#ifdef SW_TEST
    #define swAssert(b) (swAss (b, __FILE__, __LINE__, __FUNCTION__))
#endif

#ifndef SW_TEST
    #define swAssert(b)
#endif

#endif

//=============================================================================

class swReport
	{
	private:		
		const  char* funcname_;
		static int   spaces_;
	
		swReport (); //{}
	
		void imp_spc (int num) {spaces_ += num;}
		
	public:
		swReport (const char* funcname) : 
		funcname_ (funcname) 
			{
			if (!funcname) return;
			
			for (int i = 0; i < spaces_; i ++) printf (" ");  
			
			printf ("_%s_ function started!\n", funcname_);
			
			imp_spc (3);
			}
	
		~swReport ()
			{
			imp_spc (-3);
			
			for (int i = 0; i < spaces_; i ++) printf (" ");
			
			printf ("_%s_ function ended!\n", funcname_);
			} 
	};

int swReport :: spaces_;

#ifdef  SW_REPORT
	#define swREPORT swReport __rep (__PRETTY_FUNCTION__); //getch (); 
#endif

#ifndef SW_REPORT
	#define swREPORT 
#endif

//=============================================================================

enum SW_VK_KEYS
	{
	VK_ENTER  = 13
//	VK_ESCAPE = 27
	};

#endif
