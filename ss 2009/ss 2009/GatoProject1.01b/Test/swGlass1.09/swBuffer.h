#ifndef _SW_BUFFER_H_
#define _SW_BUFFER_H_

//------------------------------------------------------------------------------

#include <iostream>

#include "swPixel.h"

using std :: vector;

//------------------------------------------------------------------------------

namespace Swamp
	{

typedef unsigned long size_t;

//------------------------------------------------------------------------------

enum DEFAULT_SW_BUFFER_CONSTS
	{
	DEF_BUFF_SX = 800,
	DEF_BUFF_SY = 600,
	
	DEF_POINT_SIZE = 1
	};

//------------------------------------------------------------------------------

template <bpp_t bpp>
class Buffer
	{
	private:
		typedef Pixel<win_color, bpp> buff_pix_t;

	private:
		vector<buff_pix_t>& buff_;
		size_t              sx_, sy_;

		size_t sx (size_t sx) {return sx_ = sx;}
		size_t sy (size_t sy) {return sy_ = sy;}

	public:
		Buffer ();
		Buffer (size_t sx, size_t sy);
	   ~Buffer ();	

		Buffer 			   (const Buffer<bpp>& opd);
		Buffer& operator = (const Buffer<bpp>& opd);

		const vector<buff_pix_t>& buff () const {return buff_;} 

		size_t sx () const {return sx_;}
		size_t sy () const {return sy_;}
		
		const buff_pix_t& operator () (size_t x, size_t y) const {return buff_ [sx () * y + x];}
		      buff_pix_t& operator () (size_t x, size_t y)       {return buff_ [sx () * y + x];}

		bool resize (size_t new_sx, size_t new_sy);
		
		bool draw (int x0, int y0) const;
	};

//------------------------------------------------------------------------------

template <bpp_t bpp>
Buffer<bpp> :: Buffer () :
	buff_ (*new vector<buff_pix_t> (DEF_BUFF_SX * DEF_BUFF_SY)),
	sx_   (DEF_BUFF_SX),
	sy_   (DEF_BUFF_SY)
	{}

template <bpp_t bpp>
Buffer<bpp> :: Buffer (size_t sx, size_t sy) :
	buff_ (*new vector<buff_pix_t> (sx * sy)),
	sx_   (sx),
	sy_   (sy)
	{}

template <bpp_t bpp>
Buffer<bpp> :: ~Buffer ()
	{
	sx (0);
	sy (0);
	
	delete &buff_;
	}

template <bpp_t bpp>
Buffer<bpp> :: Buffer (const Buffer<bpp>& opd):
	buff_ (*new vector<buff_pix_t> (opd.sx () * opd.sy ())),
	sx_   (opd.sx ()),
	sy_   (opd.sy ())
	{
	buff_ = opd.buff ();	
	}

template <bpp_t bpp>
Buffer<bpp>& Buffer<bpp> :: operator = (const Buffer<bpp>& opd)
	{
	buff_ = opd.buff ();	

	return *this;		
	}

template <bpp_t bpp>
bool Buffer<bpp> :: resize (size_t new_sx, size_t new_sy)
	{
	buff_.resize (new_sx * new_sy);
	
	sx (new_sx);
	sy (new_sy);
	
	return true;
	}

template <bpp_t bpp>
bool Buffer<bpp> :: draw (int x0, int y0) const
	{
	for (size_t y = 0; y < sy (); y ++)
		for (size_t x = 0; x < sx (); x ++)
			{
			__GLASS_WND.set_point (x0 + x, x0 + y, (*this) (x, y));
			}
	
	return true;
	}

//------------------------------------------------------------------------------

	}; //end of namespace Swamp

//------------------------------------------------------------------------------

typedef Swamp :: Buffer<Swamp :: N_COLORS> swBuff;

//------------------------------------------------------------------------------

#endif
