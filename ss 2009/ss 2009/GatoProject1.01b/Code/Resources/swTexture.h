#ifndef _SW_TEXTURE_
#define _SW_TEXTURE_

#include "swTGA.h"

enum SW_MODES
	{
	SW_RGB  = 3,
	SW_RGBA = 4	
	};

class swTexture
      {
      private:
            swTGA*         image_;
            unsigned char* data_;
            GLuint         id_;
            
            swTexture  			  (swTexture&); //{}
            swTexture& operator = (swTexture&); //{}

		    bool load   (const char* filename); 
			bool deinit ();

      public:
            swTexture (const char* filename);
            swTexture ();
           ~swTexture ();
		   
		    int id () {return id_;}
		   
			bool bind ();
			bool init (const char* filename);
      };
      
swTexture :: swTexture () :
	image_ (new swTGA),
	data_  (0),
	id_    (0)
	{
	
	}

swTexture :: swTexture (const char* filename) :
	image_ (new swTGA),
	data_  (0),
	id_    (0)
	{
	
	
	load (filename);	
	}

swTexture :: ~swTexture ()
	{
	
	
	deinit ();
		
	delete    image_;
	delete [] data_;
	
	id_    = 0;
	data_  = 0;
	image_ = 0;	
	}

bool swTexture :: load (const char* filename)
	{
	
	
	if (!image_) return false;
	
	bool res = image_ -> load (filename);
	
	delete [] data_;
	
	try {
		data_ = new unsigned char [image_ -> sx () * image_ -> sy () * image_ -> bpp ()];
		}
	
	catch (...)
		{
		printf ("Too big mass!\n");
		getch ();
		return false;	
		}
	
	//image_ -> draw (GetDC (0), 0, 0);

	return res; 
	}

bool swTexture :: bind ()
	{
	
	
	if (!data_ ||
		!image_) return false;

	deinit ();
	
    glGenTextures   (1, &id_);

    glBindTexture   (GL_TEXTURE_2D, id_);

    glPixelStorei   (GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
	glEnable        (GL_TEXTURE_2D);

	int mode = 0;
	switch (image_ -> bpp ())
		{
		case SW_RGB:
			mode = GL_RGB;
			break;

		case SW_RGBA:
			mode = GL_RGBA;
			break;
		};

    image_ -> get_mass (data_);            
    gluBuild2DMipmaps (GL_TEXTURE_2D, 
					   image_ -> bpp (),             
                       image_ -> sx  (),
                       image_ -> sy  (),
                       mode, GL_UNSIGNED_BYTE, 
                       data_);            
    
	return true;
	}

bool swTexture :: init (const char* filename)
	{
	
	
	return 	load (filename) &&	bind ();
	}

bool swTexture :: deinit ()
	{
	
	
	if (!id_) return false;
	
	glDeleteTextures (1, &id_);
	
	id_ = 0;
	
	return true;
	}


#endif
