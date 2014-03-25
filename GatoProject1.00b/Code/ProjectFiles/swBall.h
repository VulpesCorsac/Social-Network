#ifndef _SW_BALL_H_
#define _SW_BALL_H_

//==============================================================================

#include "../Resources/swResources.h"

//==============================================================================

class swBall
	{
	private:
		vector<colr_t>& cls_; //colors
		indx_t          from_;
		indx_t          where_;
		secs_t          full_path_;
		secs_t          comp_path_; //complited path
		pos_t           x_, y_;
	
	public:		
		swBall& operator = (const swBall&); 
		swBall             (const swBall&); 

		swBall ();
		swBall (colr_t r, colr_t g, colr_t b);
	   ~swBall ();	
	
		colr_t r    	  () const       {return cls_ [0];}
		colr_t g    	  () const       {return cls_ [1];}
		colr_t b     	  () const       {return cls_ [2];}

		indx_t from  	  () const       {return from_;}
		indx_t where	  () const       {return where_;}
		secs_t full_path  () const       {return full_path_;}
		secs_t comp_path  () const       {return comp_path_;}
		pos_t  x          () const       {return x_;}
		pos_t  y          () const       {return y_;}

		colr_t r     	  (colr_t r)     {return cls_ [0] = r;}
		colr_t g     	  (colr_t g)     {return cls_ [1] = g;}
		colr_t b     	  (colr_t b)     {return cls_ [2] = b;}

		indx_t from       (indx_t from)  {return from_  = from;}
		indx_t where      (indx_t where) {return where_ = where;}
		secs_t full_path  (secs_t path)  {return full_path_  = path;}
		secs_t comp_path  (secs_t path)  {return comp_path_  = path;}
		pos_t  x          (pos_t  x)     {return x_ = x;}
		pos_t  y          (pos_t  y)     {return y_ = y;}

		const vector<colr_t>& cls () const {return cls_;}
		
		bool is_ball      () {swREPORT; return r () != NOT_BALLS &&
						  	                   g () != NOT_BALLS &&
								               b () != NOT_BALLS;}

		bool draw         (pos_t z);
	};

//==============================================================================

swBall& swBall :: operator = (const swBall& copy)
	{
	swREPORT;

	from_       = copy.from       ();
	where_      = copy.where      ();
	full_path_  = copy.full_path  ();
	comp_path_  = copy.comp_path  ();
	x_          = copy.x          ();
	y_          = copy.y          ();
	
	r (copy.r ());
	g (copy.g ());
	b (copy.b ());
	
	return *this;	
	}

swBall :: swBall (const swBall& copy):
	cls_        (*(new vector<colr_t> (N_COLORS_ING))),
	from_       (copy.from      ()),
	where_      (copy.where     ()),
	full_path_  (copy.full_path ()),
	comp_path_  (copy.comp_path ()),
	x_          (copy.x         ()),
	y_          (copy.y         ())
	{
	swREPORT;

	r (copy.r ());
	g (copy.g ());
	b (copy.b ());
	}

swBall :: swBall ():
	cls_        (*(new vector<colr_t> (N_COLORS_ING))),
	from_       (0),
	where_      (0),
	full_path_  (0),
	comp_path_  (0),
	x_          (0),
	y_          (0)
	{
	swREPORT;

	cls_ [0] = NOT_BALLS;	
	cls_ [1] = NOT_BALLS;	
	cls_ [2] = NOT_BALLS;	
	}

swBall :: swBall (colr_t r, colr_t g, colr_t b):
	cls_        (*(new vector<colr_t> (N_COLORS_ING))),
	from_       (0),
	full_path_  (0),
	comp_path_  (0),
	x_          (0),
	y_          (0)
	{
	swREPORT;

	cls_ [0] = r;	
	cls_ [1] = g;	
	cls_ [2] = b;	
	}

swBall :: ~swBall ()
	{
	swREPORT;

	delete &cls_;
	   
	from_       = 0;
	where_      = 0;
	full_path_  = 0;
	comp_path_  = 0;
	x_          = 0;
	y_          = 0;
	}	

bool swBall :: draw (pos_t z)
	{
	swREPORT;

	glBegin (GL_TRIANGLE_FAN); 
		{
		glColor3f   ((BALL_RAD + r ()) / 2, (BALL_G + g ()) / 2, (BALL_B + b ()) / 2);

		glVertex3f  (x_,          				y_, z);

		glColor3f   (r (),                g (),                b ());

		glVertex3f  (x_,                        y_ +               BALL_RAD, z);

		glColor3f   ((BALL_RAD + r ()) / 2, (BALL_G + g ()) / 2, (BALL_B + b ()) / 2);

		glVertex3f  (x_ + HALF_SQRT_2 * BALL_RAD, y_ + HALF_SQRT_2 * BALL_RAD, z);

		glColor3f   (BALL_RAD,              BALL_G,              BALL_B);

		glVertex3f  (x_  +              BALL_RAD, y_, z);

		glColor3f   ((BALL_RAD + r ()) / 2, (BALL_G + g ()) / 2, (BALL_B + b ()) / 2);

		glVertex3f  (x_ + HALF_SQRT_2 * BALL_RAD, y_ - HALF_SQRT_2 * BALL_RAD, z);

		glColor3f   (r (),                g (),                b ());

		glVertex3f  (x_, 						y_ -               BALL_RAD, z);

		glColor3f   ((BALL_RAD + r ()) / 2, (BALL_G + g ()) / 2, (BALL_B + b ()) / 2);

		glVertex3f  (x_ - HALF_SQRT_2 * BALL_RAD, y_ - HALF_SQRT_2 * BALL_RAD, z);

		glColor3f   (BALL_RAD,              BALL_G,              BALL_B);

		glVertex3f  (x_ - 				BALL_RAD, y_, z);

		glColor3f   ((BALL_RAD + r ()) / 2, (BALL_G + g ()) / 2, (BALL_B + b ()) / 2);

		glVertex3f  (x_ - HALF_SQRT_2 * BALL_RAD, y_ + HALF_SQRT_2 * BALL_RAD, z);

		glColor3f   (r (),                g (),                b ());

		glVertex3f  (x_,                        y_ +               BALL_RAD, z);
		}	
	glEnd ();

//	glLineWidth (INFO_LINE_WIDTH);
	/*
	glBegin (GL_LINE_STRIP);
		{
		glColor3f (0, 0, 0);

		glVertex3f  (x_,                        y_ +               BALL_RAD);
		glVertex3f  (x_ + HALF_SQRT_2 * BALL_RAD, y_ + HALF_SQRT_2 * BALL_RAD);
		glVertex3f  (x_  +              BALL_RAD, y_);
		glVertex3f  (x_ + HALF_SQRT_2 * BALL_RAD, y_ - HALF_SQRT_2 * BALL_RAD);
		glVertex3f  (x_, 						y_ -               BALL_RAD);
		glVertex3f  (x_ - HALF_SQRT_2 * BALL_RAD, y_ - HALF_SQRT_2 * BALL_RAD);
		glVertex3f  (x_ - 				BALL_RAD, y_);
		glVertex3f  (x_ - HALF_SQRT_2 * BALL_RAD, y_ + HALF_SQRT_2 * BALL_RAD);
		glVertex3f  (x_,                        y_ +               BALL_RAD);
		}
	glEnd ();
	*/
	return true;	
	}

#endif
