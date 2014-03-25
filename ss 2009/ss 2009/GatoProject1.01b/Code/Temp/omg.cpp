/*
void OnChar (char key)
	{
    glClearColor (PHONE_R, PHONE_G, PHONE_B, 1.0f); 
    glClear      (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	swNodeManager static nm ("../DATA/GRAPH.txt");

	static bool i = false;
	if (!i)
    	{
		nm.set_hwnd  (MAIN_WND.hwnd ());
		nm.spreat    (3, 0);
		nm.spreat    (5, 0);
		nm.dump      ();
		i = true;
		}

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
		
		case VK_SPACE:
			nm.count ();
			break;
		}	

	nm.draw ();

	SwapBuffers (MAIN_WND.dc ());
	}

void OnClick ()
	{
    glClearColor (PHONE_R, PHONE_G, PHONE_B, 1.0f); 
    glClear      (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	swEmptyFun ef;

	swButton but1 ("../DATA/Help1.tga", 
				   "../DATA/Help2.tga", 
				   "../DATA/Help3.tga",
				   ef);

	swButton but2 ("../DATA/Developers1.tga", 
				   "../DATA/Developers2.tga", 
				   "../DATA/Developers3.tga",
				   ef);

	swButton but3 ("../DATA/StartWork1.tga", 
				   "../DATA/StartWork2.tga", 
				   "../DATA/StartWork3.tga",
				   ef);

	
	swButtonManager bm (MAIN_WND.dc (), 100, 100, 3, 40);	

	bm.add_button (but1);
	bm.add_button (but2);
	bm.add_button (but3);

	bm.draw (110, 110, 1);

	/*	
	swNodeManager static nm ("../DATA/GRAPH.txt");

	static bool i = false;
	if (!i)
    	{
		nm.set_hwnd  (MAIN_WND.hwnd ());
		nm.add_info  (0, 1, 1, 1);
		nm.dump      ();
		i = true;
		}

	nm.start ();

//	nm.dump ();
	*/
//	SwapBuffers (MAIN_WND.dc ());
	}

int get_mx (int double_mouse_coords)
	{
	return double_mouse_coords & SIXT_ZERO_SIXT_ONES;
	}

int get_my (int double_mouse_coords)
	{
	return (double_mouse_coords & SIXT_ONES_SIXT_ZERO) >> sizeof (int) * BITES_IN_BYTE / 2 ;
	}

bool get_mouse_pressed (int mode)
	{
	return mode == MK_LBUTTON;
	}


void OnMouseMove (int mx, int my, bool pressed)
	{
	static swEmptyFun ef;

	static swButton but1 ("../DATA/Help1.tga", 
			              "../DATA/Help2.tga", 
				   		  "../DATA/Help3.tga",
				   		  ef);

	static swButton but2 ("../DATA/Developers1.tga", 
			   			  "../DATA/Developers2.tga", 
				   		  "../DATA/Developers3.tga",
				   		  ef);

	static swButton but3 ("../DATA/StartWork1.tga", 
			              "../DATA/StartWork2.tga", 
						  "../DATA/StartWork3.tga", 
				   		  ef);

	static swButton but4 ("../DATA/LoadNewNet1.tga", 
			              "../DATA/LoadNewNet2.tga", 
						  "../DATA/LoadNewNet3.tga", 
				   		  ef);


	static swButtonManager bm (MAIN_WND.dc (), 100, 100, 4, 40);	


	static bool ft = true;
	if (ft)
		{
		bm.add_button (but1);
		bm.add_button (but2);
		bm.add_button (but3);
		bm.add_button (but4);
		ft = false;
		}

	bm.draw (mx, my, pressed);
	}
*/
