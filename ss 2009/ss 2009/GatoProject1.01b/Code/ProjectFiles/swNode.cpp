swNode& swNode :: operator = (const swNode& copy)
	{
	swREPORT;

    mem_  = copy.mem  ();
	act_  = copy.act  ();
	lget_ = copy.lget ();
	x_    = copy.x    (); 
    y_    = copy.y    ();

	txt_ = copy.str ();
	inf_ = copy.inf ();

	return *this;	
	}

swNode :: swNode (const swNode& copy):
	inf_  (*(new swBall)),
	txt_  (*(new string)),
    mem_  (copy.mem  ()),
	act_  (copy.act  ()),
	lget_ (copy.lget ()),
	x_    (copy.x    ()),
	y_    (copy.y    ())
	{
	swREPORT;	

	inf_ = copy.inf ();
	txt_ = copy.str ();
	}

swNode :: swNode ():
	inf_  (*(new swBall)),
	txt_  (*(new string)),
    mem_  (0),
	act_  (0),
	lget_ (0),
	x_    (DEAD_NODE),
	y_    (DEAD_NODE)
	{
	swREPORT;
	}

swNode :: swNode (secs_t mem, actv_t act):
	inf_  (*(new swBall)),
	txt_  (*(new string)),
    mem_  (mem),
	act_  (act),
	lget_ (0),
	x_    (DEAD_NODE),
	y_    (DEAD_NODE)
	{
	swREPORT;
	}

swNode :: swNode (secs_t mem, actv_t act, char* text):
	inf_  (*(new swBall)),
	txt_  (*(new string (text))),
    mem_  (mem),
	act_  (act),
	lget_ (0),
	x_    (DEAD_NODE),
	y_    (DEAD_NODE)
	{
	swREPORT;
	}	


swNode :: swNode (colr_t r, colr_t g, colr_t b, secs_t mem, actv_t act):
	inf_  (*(new swBall (r, g, b))),
	txt_  (*(new string)),
    mem_  (mem),
	act_  (act),
	lget_ (0),
	x_    (DEAD_NODE),
	y_    (DEAD_NODE)
	{
	swREPORT;
	}

swNode :: swNode (colr_t r, colr_t g, colr_t b):
	inf_  (*(new swBall (r, g, b))),
	txt_  (*(new string)),
    mem_  (0),
	act_  (0),
	lget_ (0),
	x_    (DEAD_NODE),
	y_    (DEAD_NODE)
	{
	swREPORT;
	}

swNode :: ~swNode ()
	{
	swREPORT;	

	delete &inf_;
	delete &txt_;

	mem_  = 0;
	act_  = 0;
	lget_ = 0;
	x_    = 0;
	y_    = 0;
    } 

//=====================================================================================================

bool swNode :: draw (pos_t z)
	{
	swREPORT;

	glColor3f   (NODE_R, NODE_G, NODE_B);


	glBegin (GL_QUADS); 
		{
		glVertex3f  (x_ + NODE_RAD * NODE_KOEF, y_ + NODE_RAD * NODE_KOEF, z);
		glVertex3f  (x_ + NODE_RAD * NODE_KOEF, y_ - NODE_RAD * NODE_KOEF, z);
		glVertex3f  (x_ - NODE_RAD * NODE_KOEF, y_ - NODE_RAD * NODE_KOEF, z);
		glVertex3f  (x_ - NODE_RAD * NODE_KOEF, y_ + NODE_RAD * NODE_KOEF, z);

		glVertex3f  (x_,            y_ + NODE_RAD, z);
		glVertex3f  (x_ - NODE_RAD, y_,            z);
		glVertex3f  (x_,            y_ - NODE_RAD, z);
		glVertex3f  (x_ + NODE_RAD, y_,            z);
		}	
	glEnd ();

	if (is_ball ()) 
		{
//		if (inf_.x () != x_ ||
//			inf_.y () != y_) cout << "AAAAAAAAAAA!" << endl;
		inf_.draw (INFO_Z_COORD);
		}

	static swTextOut texter (DEFAULT_APPHABET_FILE_TEXTURE.c_str (), 
							 FONT_SX, FONT_SY);

	pos_t x0 = x_ - texter.sx () / 2 * strlen (txt_.c_str ());
	pos_t y0 = y_ - texter.sy () / 2;

	texter.print (x0, y0, TEXT_Z_COORD, txt_.c_str ());
	
	return true;	
	}
