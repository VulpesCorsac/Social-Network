#ifndef _SW_SNET_START_CONTAINER_H_
#define _SW_SNET_START_CONTAINER_H_

//==============================================================================

enum SW_SNET_START_CONTAINER_CONSTS
	{
	DEF_SIZE_WND_X  = 700,
	DEF_SIZE_WND_Y  = 700
	};

class swSNetStartContainer
	{
	private:
		swNodeManager*   nm_;

		swSNetStartContainer 		 	 (swSNetStartContainer&); //{}
		swSNetStartContainer& operator = (swSNetStartContainer&); //{}

	public:
		
		swSNetStartContainer ();
	   ~swSNetStartContainer ();	
	
		bool on_key (char key);
	};

//==============================================================================

swSNetStartContainer :: swSNetStartContainer ():
	nm_    (new swNodeManager (DEFAULT_GRAPG_FILE.c_str ())                  )
	{
	for (indx_t i = 0; i < nm_ -> size (); i ++)
		{
		if (nm_ -> is_obj_has_ball (i)) nm_ -> spreat (i, nm_ -> size ());
		}

	//nm_ -> draw ();
	}

swSNetStartContainer :: ~swSNetStartContainer ()
	{	
	delete nm_;	
	}

//==============================================================================

bool swSNetStartContainer :: on_key (char key)
	{
    glClearColor (PHONE_R, PHONE_G, PHONE_B, 1.0f); 
    glClear      (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (key)
		{
		case VK_RIGHT:
			gluLookAt  (  SHIFT_SCREEN, 0,                0,
						  SHIFT_SCREEN, 0,              - 1,
						0,              1,                0);
			break;	

		case VK_LEFT:
			gluLookAt  (- SHIFT_SCREEN, 0,                0, 
						- SHIFT_SCREEN, 0,              - 1,
						0,              1,                0);
			break;	

		case VK_DOWN:
			gluLookAt  (0,              - SHIFT_SCREEN,   0,
						0,              - SHIFT_SCREEN, - 1,
						0,              1,                0);
			break;	

		case VK_UP:
			gluLookAt  (0,                SHIFT_SCREEN,   0,
						0,                SHIFT_SCREEN, - 1,
						0,              1,                0);
			break;

		case '1':
			glOrtho (- MINUS_SCREEN, 
				  	   MINUS_SCREEN,
					 - MINUS_SCREEN, 
					   MINUS_SCREEN,
				   	   1,
				 	 - 1);
			break;

		case '2':
			glOrtho (- PLUS_SCREEN, 
				  	   PLUS_SCREEN,
					 - PLUS_SCREEN, 
					   PLUS_SCREEN,
				   	   1,
				 	 - 1);
			break;

		
		case VK_SPACE:
			nm_ -> count ();
			break;
		}	

	nm_ -> draw ();

	SwampBuffers ();
	}

//==============================================================================

#endif
