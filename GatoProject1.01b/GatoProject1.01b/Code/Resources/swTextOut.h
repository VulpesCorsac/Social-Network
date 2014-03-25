#ifndef _SW_TEXT_OUT_H_
#define _SW_TEXT_OUT_H_

//==============================================================================

#include "swTexture.h"
#include "../Resources/swResources.h"

//==============================================================================

class swTextOut
	{
	private:
		swTexture& texture_;
		font_t sx_, sy_;		


		swTextOut              (swTextOut&); //{}
		swTextOut& operator =  (swTextOut&); //{}

	public:
		swTextOut ();
		swTextOut (const char* fname, font_t sx, font_t sy);
		swTextOut (const char* fname);
		swTextOut (font_t sx, font_t sy);
	   ~swTextOut ();

		bool load  (const char* fname);

		bool print (pos_t x0, pos_t y0, pos_t z, const char* what, colr_t r = TEXT_R, 
																   colr_t g = TEXT_G, 
																   colr_t b = TEXT_B);

		font_t sx () const {return sx_;}
		font_t sy () const {return sy_;}

		font_t sx (font_t sx) {return sx_ = sx;}
		font_t sy (font_t sy) {return sy_ = sy;}
	};

//==============================================================================

swTextOut :: swTextOut ():
	texture_ (*new swTexture),
	sx_      (0),
	sy_      (0)
	{}

swTextOut :: swTextOut (const char* fname, font_t sx, font_t sy):
	texture_ (*new swTexture),
	sx_      (sx),
	sy_      (sy)
	{
	load (fname);
	}

swTextOut :: swTextOut (const char* fname):
	texture_ (*new swTexture),
	sx_      (0),
	sy_      (0)
	{
	load (fname);
	}

swTextOut :: swTextOut (font_t sx, font_t sy):
	texture_ (*new swTexture),
	sx_      (sx),
	sy_      (sy)
	{}

swTextOut :: ~swTextOut ()
	{
	delete &texture_;

	sx_ = 0;
	sy_ = 0;
	}

//==============================================================================

bool swTextOut :: load (const char* fname)
	{
	return (texture_.init (fname));
	}

bool swTextOut :: print (pos_t x0, pos_t y0, pos_t z, const char* what, colr_t r, 
													                    colr_t g, 
															   			colr_t b)
	{
	if (sx_  <= 0 ||
		sy_  <= 0 ||
		what <= 0) return false;

	const unsigned char* new_what = (const unsigned char*) what;

	pos_t x = 0;
	pos_t y = 0;

	glColor3f (r, g, b);

	glBegin (GL_QUADS);

	for (int i = 0; new_what [i]; i ++) 
		{
		x =  new_what [i]      % N_SYMBOLS_X;
		y = (new_what [i] - x) / N_SYMBOLS_X;
		
		glTexCoord3f (    (x + 0) * N_SYMBOLS_X / SIZE_X_FONT_TEXT, 
					  1 - (y + 1) * N_SYMBOLS_Y / SIZE_Y_FONT_TEXT, z);
		glVertex3f   (x0 + (i + 0) * sx_, y0 + 0, z);

		glTexCoord3f (    (x + 1) * N_SYMBOLS_X / SIZE_X_FONT_TEXT, 
					  1 - (y + 1) * N_SYMBOLS_Y / SIZE_Y_FONT_TEXT, z);
		glVertex3f   (x0 + (i + 1) * sx_, y0 + 0, z);

		glTexCoord3f (    (x + 1) * N_SYMBOLS_X / SIZE_X_FONT_TEXT, 
					  1 - (y + 0) * N_SYMBOLS_Y / SIZE_Y_FONT_TEXT, z);
		glVertex3f   (x0 + (i + 1) * sx_, y0 + sy_, z);

		glTexCoord3f (    (x + 0) * N_SYMBOLS_X / SIZE_X_FONT_TEXT, 
					  1 - (y + 0) * N_SYMBOLS_Y / SIZE_Y_FONT_TEXT, z);
		glVertex3f   (x0 + (i + 0) * sx_, y0 + sy_, z);

/*
		glTexCoord3f (0, 1, z);
		glVertex3f   (x0 + (i + 0) * sx_, y0 + 0, z);

		glTexCoord3f (1, 1, z);
		glVertex3f   (x0 + (i + 1) * sx_, y0 + 0, z);

		glTexCoord3f (1, 0, z);
		glVertex3f   (x0 + (i + 1) * sx_, y0 + sy_, z);

		glTexCoord3f (0, 0, z);
		glVertex3f   (x0 + (i + 0) * sx_, y0 + sy_, z);
*/
		}

	glEnd ();

	return true;

	}

//==============================================================================



#endif
