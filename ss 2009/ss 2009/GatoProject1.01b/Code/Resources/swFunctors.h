#ifndef _SW_FUNCTORS_H_
#define _SW_FUNCTORS_H_

//==============================================================================

#include "../ProjectFiles/swNodeManager.h"
#include "swResources.h"

//==============================================================================

class swAbsFunctor
	{
	public:
		virtual bool action () = 0;	

				 swAbsFunctor () {}
		virtual ~swAbsFunctor () {}
	};

//==============================================================================

class swStarterNM : public swAbsFunctor
	{
	private:	
		swStarterNM 			(swStarterNM&); //{}
		swStarterNM& operator = (swStarterNM&); //{}

	public:
		virtual bool action ();
		
		     	 swStarterNM ();
		virtual ~swStarterNM ();
	};

//==============================================================================

class swEmptyFun : public swAbsFunctor
	{
	public:
		virtual bool action () {return true;}
		
		     	 swEmptyFun () : swAbsFunctor () {}
		virtual ~swEmptyFun ()                   {}
	};

//==============================================================================

swStarterNM :: swStarterNM ()
	{}

swStarterNM :: ~swStarterNM ()
	{}
	
bool swStarterNM :: action ()
	{
	const char* msg = DEFAULT_START_FILE_CMD.c_str ();
	
	system (msg);
	
	return true;
	}

#endif
