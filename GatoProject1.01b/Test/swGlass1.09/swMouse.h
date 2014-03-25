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

enum GLASS_MOUSE_BUTTONS
	{
	SW_MB_LEFT  = 0,
	SW_MB_RIGHT = 1,
	
	N_SW_BUTTONS = 2
	};

bool const MB_DOWN = true;
bool const MB_UP   = false;

//------------------------------------------------------------------------------

template <typename T>
class Mouse
	{
	private:
		vector<T>&    coords_;
		vector<bool>& buttons_;

		vector<T>&    coords  () {return coords_;}
		vector<bool>& buttons () {return buttons_;}

	public:
		T x () const {return coords () [GLASS_MX_COORD];}
		T y () const {return coords () [GLASS_MY_COORD];}
		T z () const {return coords () [GLASS_MZ_COORD];}

		bool left_b  () const {return buttons () [SW_MB_LEFT];}
		bool right_b () const {return buttons () [SW_MB_RIGHT];}

		T x (T x) {return coords () [GLASS_MX_COORD] = x;}
		T y (T y) {return coords () [GLASS_MY_COORD] = y;}	
		T z (T z) {return coords () [GLASS_MZ_COORD] = z;}

		bool left_b  (bool left_b)  {return buttons () [SW_MB_LEFT]  = left_b;}
		bool right_b (bool right_b) {return buttons () [SW_MB_RIGHT] = right_b;}

		T& operator [] (int const pos) 		 {return coords () [pos];}
		T  operator [] (int const pos) const {return coords () [pos];}

		const vector<T>&    coords  () const {return coords_;}
		const vector<bool>& buttons () const {return buttons_;}

		Mouse ();
	   ~Mouse ();

		Mouse 			   (const Mouse<T>& opd);
		Mouse& operator =  (const Mouse<T>& opd);
	};

//------------------------------------------------------------------------------

template <typename T>
Mouse<T> :: Mouse () :
	coords_  (*new vector<T>    (GLASS_N_MS_COORDS)),
	buttons_ (*new vector<bool> (N_SW_BUTTONS))
	{}

template <typename T>
Mouse<T> :: ~Mouse ()
	{
	delete &coords  ();
	delete &buttons ();
	}	 

template <typename T>
Mouse<T> :: Mouse (const Mouse<T>& opd) :
	coords_  (*new vector<T>    (opd.coords  ())),
	buttons_ (*new vector<bool> (opd.buttons ()))
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
