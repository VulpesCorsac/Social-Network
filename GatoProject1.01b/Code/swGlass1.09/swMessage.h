#ifndef _SW_MESSAGE_H_
#define _SW_MESSAGE_H_

//------------------------------------------------------------------------------

namespace Swamp
	{

//------------------------------------------------------------------------------

class Message
	{
	private:
		unsigned int id_;
		bool         (*action_) (int first, int second);

	public:
		unsigned int id () 				  const {return id_;}
		unsigned int id (unsigned int id)  	    {return id_ = id;}

		bool action (int first, int second)      {action_ (first, second); return true;}
		bool action (bool (* action) (int, int)) {action_ = action; return true;}

		Message ():
				id_ 	(0),
				action_ (0)
				{}

		Message (int id, bool (*action) (int, int)): 
				id_ 	(id),
				action_ (action)
				{}

	   ~Message ()
	   			{
				id_ 	= 0;		
				action_ = 0;
				}
	};


//------------------------------------------------------------------------------

	}; //end of namespace Swamp

//------------------------------------------------------------------------------

#endif
