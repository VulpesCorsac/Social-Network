#ifndef _SW_NODE_H_
#define _SW_NODE_H_

//=====================================================================================================

#include "swBall.h"
#include "../Resources/swResources.h"

//=====================================================================================================

class swNode
	{
	private:
		swBall& inf_;
		string& txt_;
		secs_t  mem_;  //memory
		actv_t  act_;  //activity
		secs_t  lget_; //last getting of information
		pos_t   x_, y_;

	public:
		swNode& operator = (const swNode& copy);

		swNode (const swNode& copy);
		swNode ();
		swNode (secs_t mem, actv_t act);
		swNode (secs_t mem, actv_t act, char* text);
		swNode (colr_t r, colr_t g, colr_t b, secs_t, actv_t);
		swNode (colr_t r, colr_t g, colr_t b);
	   ~swNode ();

		const swBall& inf () const {return inf_;}
		
		secs_t mem  () const     {return mem_;}
		actv_t act  () const     {return act_;}
		secs_t lget () const     {return lget_;}

		secs_t mem  (secs_t mem) {return mem_ = mem;}
		actv_t act  (actv_t act) {return act_ = act;}
		secs_t lget (secs_t lg)  {return lget_= lg;}

		colr_t r    () const     {return inf_.r ();}
		colr_t g    () const     {return inf_.g ();}
		colr_t b    () const     {return inf_.b ();}

		colr_t r (colr_t r)      {return inf_.r (r);}
		colr_t g (colr_t g)      {return inf_.g (g);}
		colr_t b (colr_t b)      {return inf_.b (b);}

		const swBall& info () const {return inf_;}

		pos_t  x    () const     {return x_;}  		
		pos_t  y    () const     {return y_;}  		

		pos_t  x    (pos_t x)    {inf_.x (x); return x_ = x;}  		
		pos_t  y    (pos_t y)    {inf_.y (y); return y_ = y;}  		

		const byte_t* txt () const {return txt_.c_str ();} 
		const string& str () const {return txt_;}

		const byte_t* txt (byte_t* txt) {return (txt_ = txt).c_str ();} 
		const string& str (string& str) {return  txt_ = str;}
		
		bool is_ball ()                 {return inf_.is_ball ();}
		
		bool set_inf    (const swBall& b) {inf_ = b; inf_.x (x_); inf_.y (y_); lget_ = 0; 
										   return true;}
		
		bool forget_inf ()              {
										inf_.r (NOT_BALLS);
										inf_.g (NOT_BALLS);
										inf_.b (NOT_BALLS);
										return true;
										}
										
		bool draw (pos_t z);
	};

//=====================================================================================================

#include "swNode.cpp"


#endif
