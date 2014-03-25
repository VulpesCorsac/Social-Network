#ifndef _SW_SNET_START_CONTAINER_H_
#define _SW_SNET_START_CONTAINER_H_

//==============================================================================

enum SW_SNET_START_CONTAINER_CONSTS
	{
	DEF_SIZE_WND_X  = 700,
	DEF_SIZE_WND_Y  = 700,
	};

class swSNetStartContainer
	{
	private:
		swWindow*        wnd_;
		swNodeManager*   nm_;

		swSNetStartContainer 		 	 (swSNetStartContainer&); //{}
		swSNetStartContainer& operator = (swSNetStartContainer&); //{}

	public:
		
		swSNetStartContainer ();
	   ~swSNetStartContainer ();	
	
		int sx    () const {return wnd_ -> s_x ();}
		int sy    () const {return wnd_ -> s_y ();}

		HDC  dc   () const {return wnd_ -> dc   ();}
		HWND hwnd () const {return wnd_ -> hwnd ();}

		bool on_key (char key);
		
		const swWindow* wnd () const {return wnd_;}
		
		bool process (void (*on_idle) () = 0) {return wnd_ -> process ();}
	};

//==============================================================================

swSNetStartContainer :: swSNetStartContainer ():
	wnd_   (new swWindow      (DEFAULT_WINDOW_TITLE.c_str (), DEF_SIZE_WND_X, 
															  DEF_SIZE_WND_Y)),
	nm_    (new swNodeManager (DEFAULT_GRAPG_FILE.c_str ())                  )
	{
	swREPORT;
	
	nm_ -> set_hwnd  (hwnd ());
	
	for (indx_t i = 0; i < nm_ -> size (); i ++)
		{
		if (nm_ -> is_obj_has_ball (i)) nm_ -> spreat (i, nm_ -> size ());
		}

	//nm_ -> draw ();
	}

swSNetStartContainer :: ~swSNetStartContainer ()
	{	
	delete wnd_;
	delete nm_;	
	}

//==============================================================================

bool swSNetStartContainer :: on_key (char key)
	{
    glClearColor (PHONE_R, PHONE_G, PHONE_B, 1.0f); 
    glClear      (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (key)
		{
		case VK_RIGHT:
			gluLookAt  (  SHIFT_SCREEN, 0,                0,
						  SHIFT_SCREEN, 0,              - 1,
						0,              1,                0);
			break;	

		case VK_LEFT:
			gluLookAt  (- SHIFT_SCREEN, 0,                0, 
						- SHIFT_SCREEN, 0,              - 1,
						0,              1,                0);
			break;	

		case VK_DOWN:
			gluLookAt  (0,              - SHIFT_SCREEN,   0,
						0,              - SHIFT_SCREEN, - 1,
						0,              1,                0);
			break;	

		case VK_UP:
			gluLookAt  (0,                SHIFT_SCREEN,   0,
						0,                SHIFT_SCREEN, - 1,
						0,              1,                0);
			break;

		case '1':
			glOrtho (- MINUS_SCREEN, 
				  	   MINUS_SCREEN,
					 - MINUS_SCREEN, 
					   MINUS_SCREEN,
				   	   1,
				 	 - 1);
			break;

		case '2':
			glOrtho (- PLUS_SCREEN, 
				  	   PLUS_SCREEN,
					 - PLUS_SCREEN, 
					   PLUS_SCREEN,
				   	   1,
				 	 - 1);
			break;

		
		case VK_SPACE:
			nm_ -> count ();
			break;
		}	

	nm_ -> draw ();

	SwapBuffers (dc ());
	}

//==============================================================================

#endif
