#define SW_USING_OPEN_GL

#include "swLine.h"
#include "swGlass1.09/swGlass.h"

swLine LINE (0.3, -0.5, 12, 17.4);


bool on_click (int, int)
	{
	bool static ft = true;
	if (ft)
		{
		Swamp :: OnSize2D (0, 0);

    glClearColor (0, 0.6, 0.3, 1); 

		ft = false;	
		}

  __GLASS_GL_OBJ.get_gl_mouse ();

  cout << LINE.normal (__GLASS_GL_OBJ.mx (), __GLASS_GL_OBJ.my ()) << endl;
    
   
  glClear      (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3f (1, 1, 1);

  glBegin (GL_LINES);
    {
    glVertex2f (- 1, (- LINE.c () + LINE.a ()) / LINE.b ());
    glVertex2f (  1,  (- LINE.c () - LINE.a ()) / LINE.b ());
    }
  glEnd   ();

  SwampBuffers ();

	return true;	
	}



int main ()
	{

	use_handle_mouse ();

  __GLASS_WND.add_msg (swMsg (WM_LBUTTONDOWN, on_click));

	__GLASS_WND.fly ();

	return 0;
	}


/*
  bool rez [8*8] = {0};
  int sum = 0;
  // multiplate
  for( int i = 0 ; i < 8 ; ++i )
  {
    for( int j = 0 ; j < 8 ; ++j )
    {
      sum = 0;
      for( int kk = 0 ; kk < 8 ; ++kk )
      {
        sum += matr[i*8+kk] * matr[kk*8+j];
      }
      rez[i*8+j] = (bool)sum;
    }
  }   

  cout << endl;

  for( int i = 0 ; i < 8 ; ++i )
  {
    for( int j = 0 ; j < 8 ; ++j )
    {
    cout << rez [i*8+j] << " " ;
    }
  cout << endl;
  }

  bool rez2 [8*8] = {0};

  for( int i = 0 ; i < 8 ; ++i )
  {
    for( int j = 0 ; j < 8 ; ++j )
    {
      sum = 0;
      for( int kk = 0 ; kk < 8 ; ++kk )
      {
        sum += rez[i*8+kk] * matr[kk*8+j];
      }
      rez2[i*8+j] = (bool)sum;
    }
  }   
  
  cout << "\n" ;
  for( int i = 0 ; i < 8 ; ++i )
  {
    for( int j = 0 ; j < 8 ; ++j )
    {
    cout << rez2 [i*8+j] << " " ;
    }
  cout << endl;
  }
*/
