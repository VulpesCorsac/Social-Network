#ifndef _SW_NODE_MANAGER_H_
#define _SW_NODE_MANAGER_H_

//==============================================================================

#include "../Resources/swLine.h"
#include "swNode.h"
#include "../Resources/swResources.h"

//==============================================================================
class swNodeManager
	{
	private:
		vector<swNode>& objs_;
		vector<arc_t>&  arcs_;
		vector<swBall>& infs_;
  		indx_t          size_;

		swNodeManager              ();               //{}
		swNodeManager              (swNodeManager&); //{}
		swNodeManager& operator =  (swNodeManager&); //{}

		bool get_new_node_coords (indx_t what);
		bool test_node_coords    (indx_t what);
		bool is_able_draw_arcs   (indx_t what);
		bool del_inf             (indx_t what);
		bool del_obj             (indx_t what);
		bool is_alive            (indx_t what);
		bool set_size            (indx_t s);

		bool make_one_period     ();
		bool draw_one_period     ();
		bool count_one_period    ();

		bool send_info           (indx_t from, indx_t where);
		bool draw_arc            (indx_t from, indx_t where);
		bool is_path_more_diam   (indx_t from, indx_t where);
		
		bool erase               ();
		bool test_arcs           ();   
		bool gen_new             ();
		bool set_rand_arcs       ();
		bool set_rand_mems       ();
		bool set_rand_acts       ();

		bool is_stay_arcs (bool* is_arcs);

		inline bool bad_reading ();

		indx_t find_free_info ();
		
		bool get_graph (FILE* from);

	public:
		swNodeManager (const char* fname = DEFAULT_GRAPG_FILE.c_str ());
		swNodeManager (const indx_t size);
	   ~swNodeManager ();

		bool add_arc (indx_t first, indx_t second, arc_t inten);
		bool del_arc (indx_t first, indx_t second);
		
		bool add_info (indx_t where, colr_t r, colr_t g, colr_t b);
		
		bool dump (const char* filename = DEF_DUMP_FNAME.c_str ());
	
 		bool start ();
 		bool draw  () {draw_one_period  ();}
 		bool count () {count_one_period ();}

		bool spreat          (indx_t what, indx_t from);
		bool is_ball         (indx_t what);
		bool is_obj_has_ball (indx_t what);

		indx_t size () const {return size_;}
    };

//==============================================================================

swNodeManager :: swNodeManager (const indx_t size):
	objs_ (*new vector<swNode> (size)),
	arcs_ (*new vector<arc_t>  (size * size)),
	infs_ (*new vector<swBall> (size * BALLS_PA)),
	size_ (size)
	{
	

	srand (time (0));

	set_rand_arcs ();
    set_rand_mems ();
	set_rand_acts ();
	
	gen_new ();
	}

swNodeManager :: swNodeManager (const char* fname):
	objs_ (*new vector<swNode> (DEFAULT_N_NODES)),
	arcs_ (*new vector<arc_t>  (DEFAULT_N_NODES * DEFAULT_N_NODES)),
	infs_ (*new vector<swBall> (DEFAULT_N_NODES * BALLS_PA)),
	size_ (DEFAULT_N_NODES)
	{
	

	srand (time (0));

	if (!fname) return;

	FILE* f = fopen (fname, "r");

	if (!f) return;

	get_graph (f);

	fclose (f);
	}

swNodeManager :: ~swNodeManager ()
	{
	delete &objs_;
	delete &arcs_;
	delete &infs_;

	size_ = 0;
	}

bool swNodeManager :: set_size (indx_t s)
	{
	if (s <= 0) return false;

	objs_ = vector<swNode> (s);
	arcs_ = vector<arc_t>  (s * s);
	infs_ = vector<swBall> (s * BALLS_PA);

	size_ = s;

	return true;
	}


//==============================================================================

bool swNodeManager :: add_info (indx_t where, colr_t r, colr_t g, colr_t b)
	{
	
		
	objs_ [where].r (r);
	objs_ [where].g (g);
	objs_ [where].b (b);

	return false;
	}

bool swNodeManager :: add_arc (indx_t first, indx_t second, arc_t inten)
	{
	

	if (first  >= size_ ||
		second >= size_) return false;

	arcs_ [size_ * first  + second] =
	arcs_ [size_ * second + first]  = inten;

	return true;
	}

bool swNodeManager :: del_arc (indx_t first, indx_t second)
	{
	

	if (first  >= size_ ||
		second >= size_) return false;

	arcs_ [size_ * first  + second] =
	arcs_ [size_ * second + first]  = NOT_ARC;

	return true;
	}

//==============================================================================

bool swNodeManager :: dump (const char* filename)
	{
	
	
	FILE* f = fopen (filename, "w");
	
	fprintf (f, "I am dump file about swNodeManager object\n\n");
	fprintf (f, "adress = %d\nsize_  = %d\n", this, size_);
	fprintf (f, "Arcs is:\n\n", this, size_);
	
	for (indx_t y = 0; y < size_; y ++)
		{
		for (indx_t x = 0; x < size_; x ++)
			{
			fprintf (f, "%d ", arcs_ [y * size_ + x]);     
			}
		fprintf (f, "\n");
		}

	fprintf (f, "\n");


	for (indx_t i = 0; i < size_; i ++)
		{
		fprintf (f, "objs [%d] name = %s mem = %3d act = %3d red = %f green = %f blue = %f\n",
		i, objs_ [i].txt (), objs_ [i].mem (), objs_ [i].act (), objs_ [i].r (), 
																 objs_ [i].g (),
																 objs_ [i].b ());
		}

	
	fclose (f);
	
	/*
	ostream file = ostream (filename);
	
	file << "qq ku ku" << endl;
	
	file.close ();
	*/
	return true;            
	}

//==============================================================================

bool swNodeManager :: start ()
	{
	

	//while (true)
		{
		make_one_period ();	
		}

	return true;
	}

bool swNodeManager :: make_one_period ()
	{
	

	draw_one_period  ();
	count_one_period ();

	return true;
	}

bool swNodeManager :: draw_one_period ()
	{

	for (indx_t i = 0; i < size_; i ++)
		{
        for (indx_t k = i + 1; k < size_; k ++) draw_arc (i, k); 
        
		objs_ [i].draw (NODE_Z_COORD);
		}

	for (indx_t i = 0; i < size_ * BALLS_PA ; i ++)
		{
		if  (is_ball  (i)) infs_ [i].draw (INFO_Z_COORD);
		}

	return true;
	}

bool swNodeManager :: get_new_node_coords (indx_t what)
	{
	

	objs_ [what].x (LEFT_BOR + NODE_RAD + (RIGHT_BOR - LEFT_BOR - NODE_RAD * 2) * 
				                        ((pos_t) (rand () % MAX_RAND))      / 
				                         MAX_RAND);

	objs_ [what].y (DOWN_BOR + NODE_RAD + (UP_BOR    - DOWN_BOR - NODE_RAD * 2) * 
				                        ((pos_t) (rand () % MAX_RAND))      / 
				                         MAX_RAND);

	return test_node_coords (what);
	}

bool swNodeManager :: test_node_coords (indx_t what)
	{
	

	if (!is_alive (what)) return false;
	
	
	for (indx_t i = 0; i < size_; i ++)
		{
		if (!is_path_more_diam (i, what) &&
			 is_alive          (i)       &&
			(i !=  what)) 
			{
			return false;
			}
		}

	return is_able_draw_arcs (what);
	}

bool swNodeManager :: is_able_draw_arcs (indx_t what)
	{
	
	
	swLine line;

	//pos_t tmp_x = 0;
	//pos_t tmp_y = 0;

	for (indx_t i = 0; i < size_; i ++)
		{
		for (indx_t k = i + 1; k < size_; k ++)
			{
			if (line.gen_new (objs_ [i].x (), objs_ [i].y (), 
							  objs_ [k].x (), objs_ [k].y ()) &&
				(i != what)                                   &&
				(k != what)                                   &&
				is_alive (i)                                  &&
				is_alive (k))

				{
                if (line.is_normal_less (objs_ [what].x (), 
								     	 objs_ [what].y (),
									 	 NODE_RAD)) return false;
				}
			}
		}

	return true;
	}

bool swNodeManager :: draw_arc  (indx_t from, indx_t where)
     {
	

	glColor3f (ARC_R, ARC_G, ARC_B);

	float lw = (float) ((float) (MAX_LINE_WIDTH               )) * 
					   ((float) (arcs_ [size_ * from  + where])) /
					   ((float) (MAX_ARC));

	if (!lw) return false;

	glLineWidth (lw); 

	glBegin (GL_LINES); 
		{
		glVertex2f  (objs_ [from].x  (), objs_ [from].y  ());
		glVertex2f  (objs_ [where].x (), objs_ [where].y ());
		}	
	glEnd ();
	
	return true;     
    }

bool swNodeManager :: is_alive (indx_t what)
	{
	return (objs_ [what].x () != DEAD_NODE &&
		    objs_ [what].y () != DEAD_NODE);
	}

bool swNodeManager :: is_obj_has_ball (indx_t what)
	{
	return objs_ [what].is_ball ();
	}

bool swNodeManager :: is_ball (indx_t what)
	{
	return infs_ [what].is_ball ();
	}

bool swNodeManager :: count_one_period ()
	{
	

	for (indx_t i = 0; i < size_; i ++)
		{
		if (is_alive (i)) objs_ [i].lget (objs_ [i].lget () + 1);

		if  (objs_ [i].is_ball () &&
			(objs_ [i].lget    () >=
			 objs_ [i].mem     ())) 
			{
			objs_ [i].forget_inf ();
			}
		}

	for (indx_t i = 0; i < size_ * BALLS_PA ; i ++)
		{
		if (is_ball  (i)) infs_ [i].comp_path (infs_ [i].comp_path () + 1);

		if (is_ball  (i))
			{
			if (infs_ [i].full_path () ==
				infs_ [i].comp_path ()) 
				{
				objs_   [infs_ [i].where ()].set_inf (infs_ [i]);
				spreat  (infs_ [i].where (), infs_ [i].from ());
				del_inf (i);
				}

			else
				{
				infs_ [i].x  (objs_ [infs_ [i].from  ()].x         ()  + 
							 (objs_ [infs_ [i].where ()].x         ()  - 
							  objs_ [infs_ [i].from  ()].x         ()) * 
							  infs_ [i].				 comp_path ()  /
							  infs_ [i].				 full_path ());

				infs_ [i].y  (objs_ [infs_ [i].from  ()].y         ()  + 
							 (objs_ [infs_ [i].where ()].y         ()  - 
							  objs_ [infs_ [i].from  ()].y         ()) * 
							  infs_ [i].				 comp_path ()  /
							  infs_ [i].				 full_path ());
				}
			}
		}

	return true;	
	}

bool swNodeManager :: del_inf (indx_t what)
	{
	

	infs_ [what].r (NOT_BALLS);
	infs_ [what].g (NOT_BALLS);
	infs_ [what].b (NOT_BALLS);
	
	return true;
	}

bool swNodeManager :: del_obj (indx_t what)
	{
	

	objs_ [what].x (DEAD_NODE);
	objs_ [what].y (DEAD_NODE);
	
	return true;
	}

bool swNodeManager :: spreat (indx_t what, indx_t from)
	{
	

	bool is_arcs [size_];

	indx_t rand_pos = 0;

	for (indx_t i = 0; i < size_; i ++)
		{
		is_arcs [i] = (arcs_ [what * size_ + i] != NOT_ARC);
		}


	for (;; rand_pos = rand () % size_)
		{
		if (!(is_stay_arcs (is_arcs))) return true;

		if (is_arcs [rand_pos])
			{
			if (rand () % MAX_ACTIV <  objs_ [what].act () &&
				rand_pos            != from) 
				{
				send_info (what, rand_pos); 
				}
			
			is_arcs [rand_pos] = false;
			}
		}
	
	return true;
	}

bool swNodeManager :: is_stay_arcs (bool* is_arcs)
	{
	

	for (indx_t i = 0; i < size_; i ++)
		{
		if (is_arcs [i]) return true;
		}
	
	return false;
	}


bool swNodeManager :: erase ()
	{
	

	for (indx_t i = 0; i < size_; i ++)
		{
		del_inf (i);
		del_obj (i);
		
		for (indx_t k = 0; k < size_; k ++)
			del_arc (i, k);
		}
	
	return true;
	}

bool swNodeManager :: gen_new ()
	{
	

	erase ();
	
	set_rand_arcs ();	
	
	for (indx_t i = 0; i < size_; i ++)
		{
		if (!get_new_node_coords (i)) i --;
		}

	return true;
	}

bool swNodeManager :: send_info (indx_t from, indx_t where)
	{
	

	indx_t ball = find_free_info ();

	if (is_ball (ball)) return false;
	
	if (arcs_ [from * size_ + where] == NOT_ARC) return false;

	infs_ [ball] = objs_ [from].info ();

	infs_ [ball].from      (from);
	infs_ [ball].where     (where);
	infs_ [ball].full_path (arcs_ [from * size_ + where]);
	infs_ [ball].comp_path (0);

//	cout << "color = " << infs_ [ball].r () << " ball = " << ball << endl;
	
	return true;	
	}

indx_t swNodeManager :: find_free_info ()
	{
	

	for (indx_t i = 0; i < size_; i ++)
		if (!is_ball (i)) return i;	

	return 0;
	}

bool swNodeManager :: is_path_more_diam (indx_t from, indx_t where)
	{
	return sqrt ((objs_ [from].x () -  objs_ [where].x ()) *
				 (objs_ [from].x () -  objs_ [where].x ()) +
			     (objs_ [from].y () -  objs_ [where].y ()) *
				 (objs_ [from].y () -  objs_ [where].y ())) > NODE_RAD * 2;

	}

bool swNodeManager :: set_rand_arcs ()
	{
	

	for (indx_t i = 0; i < size_; i ++)
		for (indx_t k = 0; k < size_; k ++)
			arcs_ [size_ * i  + k] = rand () % MAX_ARC;

	for (indx_t i = 0; i < size_; i ++)
		for (indx_t k = 0; k < size_; k ++)
			arcs_ [size_ * i  + k] = arcs_ [size_ * k  + i];

	}

bool swNodeManager :: set_rand_mems ()
	{
	

	for (indx_t i = 0; i < size_; i ++)
		objs_ [i].mem (rand () % MAX_MEMORY);
	}

bool swNodeManager :: set_rand_acts ()
	{
	

	for (indx_t i = 0; i < size_; i ++)
		objs_ [i].act (rand () % MAX_ACTIV);
	}


bool swNodeManager :: get_graph (FILE* from)
	{
	

	int i = 0;

	rewind (from);

	int tmp_num = 0;

	while (fscanf (from, "%d", &tmp_num)) i++;

	int sqr_i = (int) sqrt (i);

	if (sqr_i * sqr_i != i) 
		{
		return bad_reading ();
		}

	if (!set_size (sqr_i - 1)) return false;

	rewind (from);

	for (indx_t x = 0; x < size_ + 1; x ++)
		{
		if (!fscanf (from, "%d", &tmp_num)) return bad_reading ();
		}

	for (indx_t y = 0; y < size_; y ++)
		{
		if (!fscanf (from, "%d", &tmp_num)) return bad_reading (); 

		for (indx_t x = 0; x < size_; x ++)
			{
			if (!fscanf (from, "%d", &arcs_ [y * size_ + x])) return bad_reading ();
//			cout << "arcs [" << y << "] [" << x << "] = " << arcs_ [y * size_ + x] << endl;
			}

		}

	if (!test_arcs ()) return bad_reading ();

	int num = 0; //indx_t
	int mem = 0; //mem_t
	int act = 0; //act_t     
	
	float x = 0;
	float y = 0;//pos_t

	char name [MAX_L_NAME] = {0}; //byte_t

	float r = 0;
	float g = 0;
	float b = 0;
	
	fscanf (from, "\n");

	for (int c = 0; c < size_; c ++)
		{
		if (!fscanf (from, "{Node ¹ %d ",    &num) ||
			!fscanf (from, "Name: %s ",      name) ||
		    !fscanf (from, "Memory: %d ",    &mem) ||
		    !fscanf (from, "Activity: %d ",  &act) ||
			!fscanf (from, "Coord X: %f ",   &x)   ||
			!fscanf (from, "Coord Y: %f ",   &y)   ||
			!fscanf (from, "RED = %f ",      &r)   ||
			!fscanf (from, "GREEN = %f ",    &g)   ||
			!fscanf (from, "BLUE = %f }\n",  &b))
			{
			return bad_reading ();
			}			

		if (num >= size_) 
			{
			return bad_reading ();
			}


		objs_ [num].mem  (mem);
		objs_ [num].act  (act);
		objs_ [num].lget (0);

		objs_ [num].x      (x);
		objs_ [num].y      (y);

		objs_ [num].txt  (name);


		objs_ [num].r  (r);
		objs_ [num].g  (g);
		objs_ [num].b  (b);
		}

	
	return true;
	}

inline bool swNodeManager :: bad_reading ()
	{
	cerr << "Uncorrect format of GRAPH file!" << endl;
	return false;
	}

bool swNodeManager :: test_arcs ()   
	{

	for (indx_t y = 0; y < size_; y ++)
		for (indx_t x = 0; x < size_; x ++)
			if (arcs_ [size_ * x  + y] !=
				arcs_ [size_ * y  + x]) 
					{
//		cout << "arcs [" << y << "] [" << x << "] = " << arcs_ [size_ * y  + x] << endl;
//		cout << "arcs [" << x << "] [" << y << "] = " << arcs_ [size_ * x  + y] << endl;
					return false;
					}
	return true;
	}

//==============================================================================

#endif
		
