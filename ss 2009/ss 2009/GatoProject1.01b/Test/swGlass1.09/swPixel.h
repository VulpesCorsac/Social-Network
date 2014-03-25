#ifndef _SW_PIXEL_H_
#define _SW_PIXEL_H_

#include <vector>

using std :: vector;

//------------------------------------------------------------------------------

namespace Swamp
	{

//------------------------------------------------------------------------------

enum SW_STD_WIN_PIXEL_CONSTS
	{
	R_COLOR_POS = 0,
	G_COLOR_POS = 1,
	B_COLOR_POS = 2,
		
	N_COLORS = 3,
	
	MAX_WIN32_COLORS = 256
	};

typedef unsigned int bpp_t;

//------------------------------------------------------------------------------

template <typename T, bpp_t bpp>
class Pixel
	{
	private:
		vector<T>& colors_;

	public:
		Pixel ();
	   ~Pixel ();	

		Pixel 			  (const Pixel<T, bpp>& opd);
		Pixel& operator = (const Pixel<T, bpp>& opd);
		
		T  operator [] (int pos) const {return colors_ [pos];}
		T& operator [] (int pos)       {return colors_ [pos];}
	
		const vector<T>& colors () const {return colors_;}

		//friend std :: ostream& operator << (std :: ostream& s, const Pixel<T>& p);
	};

//------------------------------------------------------------------------------

template <typename T, bpp_t bpp>
Pixel<T, bpp> :: Pixel () :
	colors_ (*new vector<T> (bpp))
	{
	colors_ [R_COLOR_POS] = 0;
	colors_ [G_COLOR_POS] = 0;
	colors_ [B_COLOR_POS] = 0;
	}

template <typename T, bpp_t bpp>
Pixel<T, bpp> :: ~Pixel ()
	{
	delete &colors_;
	}

template <typename T, bpp_t bpp>
Pixel<T, bpp> :: Pixel (const Pixel<T, bpp>& opd):
	colors_ (*new vector<T> (N_COLORS))
	{
	colors_ = opd.colors ();
	}
	
template <typename T, bpp_t bpp>
Pixel<T, bpp>& Pixel<T, bpp> :: operator = (const Pixel<T, bpp>& opd)
	{
	colors_ = opd.colors ();
	
	return *this;
	}

template <typename T, bpp_t bpp>
std :: ostream& operator << (std :: ostream& s, const Pixel<T, bpp>& p)
	{
	std :: cout << "Pixel (";

	for (int i = 0; i < bpp - 1; i ++)
		{
		std :: cout << p.colors () [i] << ", ";
		}

	std :: cout << p.colors () [bpp - 1] << ");" << std :: endl;

	return s;	
	}	
	
//------------------------------------------------------------------------------

typedef int   win_color;
typedef float gl_color;


//------------------------------------------------------------------------------

	}; //end of namespace Swamp

//------------------------------------------------------------------------------

typedef Swamp :: Pixel<Swamp :: win_color, Swamp :: N_COLORS> swWinPixel;
typedef Swamp :: Pixel<Swamp :: gl_color,  Swamp :: N_COLORS> swGLPixel;

//------------------------------------------------------------------------------


#endif
