#ifndef _SW_LINE_H_
#define _SW_LINE_H_

#include <math.h>
#include <iostream> 

using std :: ostream;
using std :: cout;
using std :: endl;

typedef float line_t;

class swLine
	{
	private:
		line_t a_, b_, c_; //line is ax + by + c = 0;
	
	public:
		swLine   ();
		swLine   (line_t x0, line_t y0, line_t x1, line_t y1);
		swLine   (line_t a,  line_t b,  line_t c);
	   ~swLine   ();
		
		line_t a () const {return a_;}	
		line_t b () const {return b_;}	
		line_t c () const {return c_;}	

		bool OK () {cout << "a = " << a_ << " b = " << b_ << endl; return a_ != 0 && b_ != 0;}

		bool gen_new        (line_t x0, line_t y0, line_t x1, line_t y1);
		bool is_on_line     (line_t x0, line_t y0);		

		bool is_normal_less (line_t x0, line_t y0, line_t max_height);
		bool is_normal_more (line_t x0, line_t y0, line_t min_height);

		line_t normal       (line_t x0, line_t y0);

		friend ostream& operator << (ostream& s, const swLine& l);
	};

swLine :: swLine () :
	a_ (0),
	b_ (0),
	c_ (0)
	{}

swLine :: swLine (line_t x0, line_t y0, line_t x1, line_t y1) :
	a_ (0),
	b_ (0),
	c_ (0)
	{
	gen_new (x0, y0, x1, y1);	
	}

swLine :: swLine (line_t a,  line_t b,  line_t c) :
	a_ (a),
	b_ (b),
	c_ (c)
	{}

swLine :: ~swLine ()
	{
	a_ = b_ = c_ = 0;
	}

bool swLine :: gen_new (line_t x0, line_t y0, line_t x1, line_t y1)
	{
    swREPORT;
	if (x0 == x1 && x0 != 0) 
		{
//		cout << "I AM BIIIIG KREVEDKO!!!! " << x0 << ' ' << x1 << endl;
//		getch ();
		}

	if (x0 == x1) return false;


	a_ = (y0 - y1) / (x0 - x1);
	b_ = - 1;
    c_ = - (a_ * x0 + b_ * y0);

	return true;
	}

bool swLine :: is_on_line (line_t x0, line_t y0)
	{
    swREPORT;
	return (a_ * x0 + b_ * y0 + c_ == 0);
	}

bool swLine :: is_normal_less (line_t x0, line_t y0, line_t max_height)
	{
    swREPORT;

	float norm = normal (x0, y0);

	bool res = (norm <= max_height);
/*
	int static  true_res = 0;
	int static false_res = 0;

	if (res) true_res ++; 
	else    false_res ++;

	
	cout << *this << endl;

	cout << '(' << x0 << ", " << y0 << ')' << endl;

	cout << "norm = " << norm << ' '; 

	cout << "true = " << true_res << " false = " << false_res << endl << endl; 
*/	
	return res; 	
	}

bool swLine :: is_normal_more (line_t x0, line_t y0, line_t min_height)
	{
    swREPORT;
	return (normal (x0, y0) >= min_height); 	
	}

line_t swLine :: normal (line_t x0, line_t y0)
	{
    swREPORT;
    
	if (a_ == 0 &&
        b_ == 0) return 0;
	
	return fabs (a_ * x0 + b_ * y0 + c_) / sqrt (a_ * a_ + b_ * b_); 	
	}

ostream& operator << (ostream& s, const swLine& l)
	{
	s << l.a () << "x + " << l.b () << "y + " << l.c () << " = 0;";
	return s;	
	}	

#endif
