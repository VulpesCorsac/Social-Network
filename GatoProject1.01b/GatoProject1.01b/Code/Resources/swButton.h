#ifndef _SW_BUTTON_H_
#define _SW_BUTTON_H_

//==============================================================================

#include "swTGA.h"

//==============================================================================

enum SW_BUTTON_MODES
	{
	MODE_UNTOUCHED = 0,
	MODE_TOUCHED   = 1,
	MODE_PRESSED   = 2,
		
	N_MODES        = 3
	};

enum SW_BUTTON_COORDS
	{
	X_COORD  = 0,
	Y_COORD  = 1,
		
	N_COORDS = 2
	};

	
//==============================================================================

class swButton
	{
	private:	
		HDC*     dcs_;  //[N_MODES]
		HBITMAP* bmps_; //[N_MODES]
		int*     coords_;
		int      mode_;
		
		swAbsFunctor* func_;
		
		swButton             ();          //{}
		swButton       		 (swButton&); //{}
		swButton& operator = (swButton&); //{}

	public:
		swButton (const char* fname_mode_unt, 
				  const char* fname_mode_tch, 
				  const char* fname_mode_pre,
				  swAbsFunctor& func);

		~swButton ();
		
		bool draw (HDC dc, int x0, int y0); 

		int sx (int mode) const {return coords_ [mode * N_COORDS + X_COORD];} 
		int sy (int mode) const {return coords_ [mode * N_COORDS + Y_COORD];} 

		int sx () const {return coords_ [mode_ * N_COORDS + X_COORD];} 
		int sy () const {return coords_ [mode_ * N_COORDS + Y_COORD];} 

		int mode () const   {return mode_;}
		int mode (int mode) {return mode_ = mode;}
		
		bool action () {return func_ -> action ();}
	};
	
//==============================================================================

swButton :: swButton (const char* fname_mode_unt, 
				  	  const char* fname_mode_tch, 
				  	  const char* fname_mode_pre,
				  	  swAbsFunctor& func) :
	dcs_    (new HDC     [N_MODES]),
	bmps_   (new HBITMAP [N_MODES]),
	coords_ (new int     [N_MODES * N_COORDS]),
	func_   (&func),
	mode_   (MODE_UNTOUCHED)
	{
	swTGA tga;
	
	//---------------------
	
	if (!tga.load (fname_mode_unt)) return;

	dcs_  [MODE_UNTOUCHED] = CreateCompatibleDC     (0);

	bmps_ [MODE_UNTOUCHED] = CreateCompatibleBitmap (GetDC (0), tga.sx (), tga.sy ());

	SelectObject (dcs_  [MODE_UNTOUCHED], bmps_ [MODE_UNTOUCHED]);

	tga.draw (dcs_  [MODE_UNTOUCHED], 0, 0);

	coords_ [MODE_UNTOUCHED * N_COORDS + X_COORD] = tga.sx ();
	coords_ [MODE_UNTOUCHED * N_COORDS + Y_COORD] = tga.sy ();

	//---------------------

	if (!tga.load (fname_mode_tch)) return;

	dcs_  [MODE_TOUCHED] = CreateCompatibleDC       (0);
	bmps_ [MODE_TOUCHED] = CreateCompatibleBitmap   (GetDC (0),   tga.sx (), tga.sy ());

	SelectObject (dcs_  [MODE_TOUCHED], bmps_ [MODE_TOUCHED]);

	tga.draw (dcs_  [MODE_TOUCHED], 0, 0);

	coords_ [MODE_TOUCHED * N_COORDS + X_COORD] = tga.sx ();
	coords_ [MODE_TOUCHED * N_COORDS + Y_COORD] = tga.sy ();

	//---------------------

	if (!tga.load (fname_mode_pre)) return;
 
	dcs_  [MODE_PRESSED] = CreateCompatibleDC       (0);
	bmps_ [MODE_PRESSED] = CreateCompatibleBitmap   (GetDC (0),   tga.sx (), tga.sy ());

	SelectObject (dcs_  [MODE_PRESSED], bmps_ [MODE_PRESSED]);

	tga.draw (dcs_  [MODE_PRESSED], 0, 0);

	coords_ [MODE_PRESSED * N_COORDS + X_COORD] = tga.sx ();
	coords_ [MODE_PRESSED * N_COORDS + Y_COORD] = tga.sy ();

	}

swButton :: ~swButton ()
	{
	for (int i = 0; i < N_MODES; i ++)
		{
		DeleteDC     (dcs_  [i]);	
		DeleteObject (bmps_ [i]);	
		}	
		
	delete [] dcs_;
	delete [] bmps_;
	
	dcs_  = 0;
	bmps_ = 0;
	
	func_ = 0;
	}

bool swButton :: draw (HDC dc, int x0, int y0)
	{
	BitBlt (dc, x0, y0, sx (), sy (), dcs_ [mode_], 0, 0, SRCCOPY);
		
	return true;
	}

#endif
