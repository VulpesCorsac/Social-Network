#ifndef _SW_MOUSE_H_
#define _SW_MOUSE_H_

//------------------------------------------------------------------------------

namespace Swamp
	{

//------------------------------------------------------------------------------

enum GLASS_MOUSE_COORDS_POSES
	{
	GLASS_MX_COORD = 0,
	GLASS_MY_COORD = 1,
	GLASS_MZ_COORD = 2,

	GLASS_N_MS_COORDS = 3
	};

//------------------------------------------------------------------------------

template <typename T>
class Mouse
	{
	private:
		vector<T>& coords_;

		vector<T>& coords () {return coords_;}

	public:
		T x () const {return coords () [GLASS_MX_COORD];}
		T y () const {return coords () [GLASS_MY_COORD];}
		T z () const {return coords () [GLASS_MZ_COORD];}
	
		T x (T x) {return coords () [GLASS_MX_COORD] = x;}
		T y (T y) {return coords () [GLASS_MY_COORD] = y;}	
		T z (T z) {return coords () [GLASS_MZ_COORD];}

		T& operator [] (int const pos) 		 {return coords () [pos];}
		T  operator [] (int const pos) const {return coords () [pos];}

		const vector<T>& coords () const {return coords_;}

		Mouse ();
	   ~Mouse ();

		Mouse 			   (const Mouse<T>& opd);
		Mouse& operator =  (const Mouse<T>& opd);
	};

//------------------------------------------------------------------------------

template <typename T>
Mouse<T> :: Mouse () :
	coords_ (*new vector<T> (GLASS_N_MS_COORDS))
	{}

template <typename T>
Mouse<T> :: ~Mouse ()
	{
	delete &coords ();
	}	 

template <typename T>
Mouse<T> :: Mouse (const Mouse<T>& opd) :
	coords_ (*new vector<T> (opd.coords ()))
	{}

template <typename T>
Mouse<T>& Mouse<T> :: operator = (const Mouse<T>& opd)
	{
	coords () = opd.coords ();
	return *this;	
	}

//------------------------------------------------------------------------------

	}; //end of namespace Swamp

//------------------------------------------------------------------------------

#endif
