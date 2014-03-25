#ifndef _SW_SNET_CONTAINER_H_
#define _SW_SNET_CONTAINER_H_

//==============================================================================

enum SW_SNET_CONTAINER_CONSTS
	{
	N_BUTTONS       = 4,
	DEF_SIZE_WND_X  = 700,
	DEF_SIZE_WND_Y  = 700,
	
	BETWEEN_BUTS    = 30,
	X0_OF_BUTTONS   = 201,
	Y0_OF_BUTTONS   = 169
	};

enum NUMS_OF_BUTTONS
	{
	HELP_BUTTON         = 0,
	DEVELOPERS_BUTTON   = 1,
	START_WORK_BUTTON   = 2,
	LOAD_NEW_NET_BUTTON = 3
	};

const string HELP_BUTTON_MODE_UNTOUCHED         ("../../DATA/Help1.tga");
const string HELP_BUTTON_MODE_TOUCHED           ("../../DATA/Help2.tga");
const string HELP_BUTTON_MODE_PRESSED  		    ("../../DATA/Help3.tga");

const string DEVELOPERS_BUTTON_MODE_UNTOUCHED   ("../../DATA/Developers1.tga");
const string DEVELOPERS_BUTTON_MODE_TOUCHED     ("../../DATA/Developers2.tga");
const string DEVELOPERS_BUTTON_MODE_PRESSED     ("../../DATA/Developers3.tga");

const string START_WORK_BUTTON_MODE_UNTOUCHED   ("../../DATA/StartWork1.tga");
const string START_WORK_BUTTON_MODE_TOUCHED     ("../../DATA/StartWork2.tga");
const string START_WORK_BUTTON_MODE_PRESSED     ("../../DATA/StartWork3.tga");

const string LOAD_NEW_NET_BUTTON_MODE_UNTOUCHED ("../../DATA/LoadNewNet1.tga");
const string LOAD_NEW_NET_BUTTON_MODE_TOUCHED   ("../../DATA/LoadNewNet2.tga");
const string LOAD_NEW_NET_BUTTON_MODE_PRESSED   ("../../DATA/LoadNewNet3.tga");

//==============================================================================

typedef swAbsFunctor* ptr_func;
typedef swButton*     ptr_butt;

//==============================================================================


class swSNetContainer
	{
	private:
		swWindow*        wnd_;
		swButtonManager* bm_;
		
		ptr_func* funcs_;		
		ptr_butt* bts_;
		
		swSNetContainer 			(swSNetContainer&); //{}
		swSNetContainer& operator = (swSNetContainer&); //{}

	public:
		
		swSNetContainer ();
	   ~swSNetContainer ();	
	
		bool on_mouse_mode_change (int mx, int my, bool pressed);
	
		int  get_mx            (int double_mouse_coords) const;
		int  get_my            (int double_mouse_coords) const;
		bool get_mouse_pressed (int mode)    		     const;

		int sx    () const {return wnd_ -> s_x ();}
		int sy    () const {return wnd_ -> s_y ();}

		HDC  dc   () const {return wnd_ -> dc   ();}
		HWND hwnd () const {return wnd_ -> hwnd ();}
		
		const swWindow* wnd () const {return wnd_;}
		
		bool process (void (*on_idle) () = 0) {return wnd_ -> process ();}
	
		bool clear   (HDC dc);
	};

//==============================================================================

swSNetContainer :: swSNetContainer ():
	wnd_   (new swWindow      (DEFAULT_WINDOW_TITLE.c_str (), DEF_SIZE_WND_X, 
															  DEF_SIZE_WND_Y)),
	bm_    (new swButtonManager (dc (),     X0_OF_BUTTONS, Y0_OF_BUTTONS, 
								 N_BUTTONS, BETWEEN_BUTS)                    ),
	funcs_ (new ptr_func [N_BUTTONS]),
	bts_   (new ptr_butt [N_BUTTONS])
	{
	swREPORT;
	
	funcs_ [HELP_BUTTON] = new swEmptyFun;
	bts_   [HELP_BUTTON] = new swButton (HELP_BUTTON_MODE_UNTOUCHED.c_str (),
										 HELP_BUTTON_MODE_TOUCHED.  c_str (),
										 HELP_BUTTON_MODE_PRESSED.  c_str (),
										 *funcs_ [HELP_BUTTON]);
		
	funcs_ [DEVELOPERS_BUTTON] = new swEmptyFun;
	bts_   [DEVELOPERS_BUTTON] = new swButton (DEVELOPERS_BUTTON_MODE_UNTOUCHED.c_str (),
						 					   DEVELOPERS_BUTTON_MODE_TOUCHED.  c_str (),
										 	   DEVELOPERS_BUTTON_MODE_PRESSED.  c_str (),
										 	   *funcs_ [DEVELOPERS_BUTTON]);

	funcs_ [START_WORK_BUTTON] = new swStarterNM;
	bts_   [START_WORK_BUTTON] = new swButton (START_WORK_BUTTON_MODE_UNTOUCHED.c_str (),
										 	   START_WORK_BUTTON_MODE_TOUCHED.  c_str (),
										 	   START_WORK_BUTTON_MODE_PRESSED.  c_str (),
										 	   *funcs_ [START_WORK_BUTTON]);

	funcs_ [LOAD_NEW_NET_BUTTON] = new swEmptyFun;
	bts_   [LOAD_NEW_NET_BUTTON] = new swButton (LOAD_NEW_NET_BUTTON_MODE_UNTOUCHED.c_str (),
										 		 LOAD_NEW_NET_BUTTON_MODE_TOUCHED.  c_str (),
										 		 LOAD_NEW_NET_BUTTON_MODE_PRESSED.  c_str (),
										 		 *funcs_ [LOAD_NEW_NET_BUTTON]);

	bm_ -> add_button (*bts_ [START_WORK_BUTTON]);
	bm_ -> add_button (*bts_ [LOAD_NEW_NET_BUTTON]);
	bm_ -> add_button (*bts_ [HELP_BUTTON]);
	bm_ -> add_button (*bts_ [DEVELOPERS_BUTTON]);

	clear (dc ());
	}

swSNetContainer :: ~swSNetContainer ()
	{	
	for (int i = 0; i < N_BUTTONS; i ++)
		{
		delete funcs_ [i];	
		delete bts_   [i];	
		}	
	
	delete wnd_;
	delete bm_;	
	
	delete [] bts_;
	delete [] funcs_;
	}

//==============================================================================

int swSNetContainer :: get_mx (int double_mouse_coords) const
	{
	return double_mouse_coords & SIXT_ZERO_SIXT_ONES;
	}

int swSNetContainer :: get_my (int double_mouse_coords) const
	{
	return (double_mouse_coords & SIXT_ONES_SIXT_ZERO) >> sizeof (int) * BITES_IN_BYTE / 2 ;
	}

bool swSNetContainer :: get_mouse_pressed (int mode) const
	{
	return mode == MK_LBUTTON;
	}

//==============================================================================

bool swSNetContainer :: on_mouse_mode_change (int mx, int my, bool pressed)
	{	
	return bm_ -> refresh (mx, my, pressed);
	}

bool swSNetContainer :: clear (HDC dc)
	{
	int const n_verts = 8;
	
	int const vpc     = 2;      
	
	POINT Client [n_verts] = {0, 0, 0, sy (), sx (), sy (), sx (), 0};
	
	HBRUSH phone_brush = CreateSolidBrush (RGB (PHONE_R * 255, PHONE_G * 255, PHONE_B * 255));
	
	SelectObject (dc, phone_brush);
	
	Polygon (dc, Client, n_verts / vpc);
	
	DeleteObject (phone_brush);
	
	return true;
	}


/*
bool swSNetContainer :: on_char (char key)
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
		
		case VK_SPACE:
			nm.count ();
			break;
		}	

	nm_ -> draw ();

	SwapBuffers (MAIN_WND.dc ());
	}
*/

//==============================================================================

#endif
