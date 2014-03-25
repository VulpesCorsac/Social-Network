#ifndef _SW_GLASS_GL_H_
#define _SW_GLASS_GL_H_

//-------------------------------------------------------------------------------------------

#define SwampBuffers() {SwapBuffers(__GLASS_WND.dc ());}

//-------------------------------------------------------------------------------------------

#include <gl/gl.h>
#include <gl/glu.h>

//------------------------------------------------------------------------------

namespace Swamp
	{

//------------------------------------------------------------------------------

bool OnSize2D (int, int);

typedef double gl_mouse_t;

//------------------------------------------------------------------------------

class GlassGL
	{
	private:
		HGLRC              rc_;
		Mouse<gl_mouse_t>& mc_;
		
		bool init         ();
		bool set_pix_form (HDC dc);

	public:

		GlassGL ();
	   ~GlassGL ();

		const Mouse<gl_mouse_t>& mc () const {return mc_;}

		gl_mouse_t mx () const {return mc ().x ();}		
		gl_mouse_t my () const {return mc ().y ();}		
		gl_mouse_t mz () const {return mc ().z ();}		

        bool get_gl_mouse ();
	};

GlassGL :: GlassGL () :
	rc_  (NULL),
	mc_  (*new Mouse<gl_mouse_t>)
	{
	init ();
	
	glClearDepth(1.0f);
	glEnable    (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);
	glHint      (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	__GLASS_WND.add_msg (swMsg (WM_SIZE, OnSize2D));
	}
	
GlassGL :: ~GlassGL ()
	{
	if (rc_)
		{
		wglMakeCurrent  (__GLASS_WND.dc (), 0);
		wglDeleteContext(rc_);
		}
	
	delete &mc_;
	}

bool GlassGL :: init ()
	{
	if (!set_pix_form (__GLASS_WND.dc ())) return false;
	
	rc_ = wglCreateContext (__GLASS_WND.dc ());
	wglMakeCurrent         (__GLASS_WND.dc (), rc_);
	
	return true;
	}

bool GlassGL :: set_pix_form (HDC dc)
	{
	int pix_form = 0;
	PIXELFORMATDESCRIPTOR pfd = {0};
	
	ZeroMemory (&pfd, sizeof (PIXELFORMATDESCRIPTOR));
	
	pfd.nSize      = sizeof (PIXELFORMATDESCRIPTOR);
	pfd.nVersion   = GL_VERSION_1_1;
	pfd.dwFlags    = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	
	pix_form = ChoosePixelFormat (dc, &pfd);
	
	if (!pix_form)                           return false;
	if (!SetPixelFormat(dc, pix_form, &pfd)) return false;
	
	return true;
	}
/*
void OnSize (HWND hwnd, float corner = 60, float z_near = 0.1, float z_far = 20)
    {
	
    RECT client = {0, 0, 0, 0};
    GetClientRect (hwnd, &client);
	
	if (client.top   == client.bottom || 
        client.right == client.left) return;
	
    glViewport     (0, 0, client.right, client.bottom);
    gluPerspective (corner, (client.right  - client.left) / //!!!int, not float 
                            (client.bottom - client.top), z_near, z_far);
    
	}
*/
bool OnSize2D (int, int)
    {
	
    static RECT new_client = {0, 0, SIZE_WND_X, SIZE_WND_Y};
    static RECT old_client = {0, 0, SIZE_WND_X, SIZE_WND_Y};

	old_client = new_client;

    GetClientRect (__GLASS_WND.hwnd (), &new_client);

	if (new_client.top    == new_client.bottom || 
        new_client.right  == new_client.left   ||
		old_client.right  == 0                 ||
		old_client.bottom == 0) return false;


    glViewport (0, 0, new_client.right, new_client.bottom);

	static bool ft = true;
	if (ft)
		{
		glOrtho (- (float) new_client.right / (float) new_client.bottom, 
			  	   (float) new_client.right / (float) new_client.bottom,
				 - 1, 1, 1, - 1);
		
		ft = false;	
		
		return false;
		}

	float x_new_to_old = (float) new_client.right  / (float) old_client.right; 
	float y_new_to_old = (float) new_client.bottom / (float) old_client.bottom; 

	glOrtho (- x_new_to_old, 
		  	   x_new_to_old,
			 - y_new_to_old, 
			   y_new_to_old,
			   1,
			 - 1);

	return true;
	}

bool GlassGL :: get_gl_mouse ()
	{
	vector<gl_mouse_t> buff (GLASS_N_MS_COORDS);
	
	for (int i = 0; i < GLASS_N_MS_COORDS; i ++)
		 buff [i] = (gl_mouse_t) __GLASS_WND.mc () [i];

    GLint    viewport   [4];
    GLdouble projection [16];
    GLdouble modelview  [16];

    glGetIntegerv (GL_VIEWPORT,          viewport);
    glGetDoublev  (GL_PROJECTION_MATRIX, projection);
    glGetDoublev  (GL_MODELVIEW_MATRIX,  modelview);
  
    gluUnProject (buff  [GLASS_MX_COORD], 
				  buff  [GLASS_MY_COORD],
				  buff  [GLASS_MZ_COORD],  
				  modelview, projection, viewport, 
                  &buff [GLASS_MX_COORD], 
				  &buff [GLASS_MY_COORD], 
				  &buff [GLASS_MZ_COORD]);

    buff [GLASS_MY_COORD] = - (buff [GLASS_MY_COORD]);

	for (int i = 0; i < GLASS_N_MS_COORDS; i ++)
		mc_ [i] = buff [i];

	return true;
	}

//------------------------------------------------------------------------------

	}; //end of namespace Swamp

//------------------------------------------------------------------------------

Swamp :: GlassGL __GLASS_GL_OBJ;

//------------------------------------------------------------------------------

typedef Swamp :: GlassGL swGlassGL;

//------------------------------------------------------------------------------

#endif
