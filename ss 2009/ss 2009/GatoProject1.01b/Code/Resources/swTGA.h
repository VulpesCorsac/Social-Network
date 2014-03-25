#include <stdio.h>
#include <stdlib.h>

//------------------------------------------------------------------------------

#ifndef _SW_TGA_H_
#define _SW_TGA_H_

//------------------------------------------------------------------------------

class swTGA
	{
	private:
		//variables
		int sx_;
		int sy_;

		int bpp_;
		
		unsigned char* data_;
		
		//functions
		bool unload ();
	    bool flip   ();

		//unreleased
		swTGA 			  (swTGA&);//{}
		swTGA& operator = (swTGA&);//{}

	public:
		//costructors
		swTGA (char* filename);
		swTGA ();
	   ~swTGA ();
 
	    //functions
	    bool load (const char* filename);
	    bool draw (HDC dc, int x0, int y0);
	    bool grey ();
	    
		int sx  () const {return sx_;}
	    int sy  () const {return sy_;}
	    int bpp () const {return bpp_;}
	    
	    bool get_mass (unsigned char* where); //Работает долго, сразу говорю... 8(
	    
	    float get_r (int x, int y) {if (!data_) return -1; 
									return ((float) data_ [y * sx_ * bpp_ + x * bpp_ + 0] / 255);}
	    float get_g (int x, int y) {if (!data_) return -1; 
								    return ((float) data_ [y * sx_ * bpp_ + x * bpp_ + 1] / 255);}
	    float get_b (int x, int y) {if (!data_) return -1; 
									return ((float) data_ [y * sx_ * bpp_ + x * bpp_ + 2] / 255);}
	};

//------------------------------------------------------------------------------

swTGA :: swTGA ():
	sx_   (0),
	sy_   (0),
	bpp_  (0),
	data_ (0)
	{
	
	
	unload ();	
	}

swTGA :: swTGA (char* filename):
	sx_   (0),
	sy_   (0),
	bpp_  (0),
	data_ (0)
	{
	
	
	load (filename);
	}

swTGA :: ~swTGA ()
	{
	
	
	unload ();	
	}

//------------------------------------------------------------------------------

bool swTGA :: unload ()
	{
	
	
	delete [] data_;

	sx_    = 0;
	sy_    = 0;
	
	bpp_   = 0;
	
	data_  = 0;
	
	return true;
	}

bool swTGA :: load (const char* filename)
	{
	
	
	if (!filename) return false;

	unload ();
	
	FILE* file = fopen (filename, "rb");
    if (!file) return false; 
	
	char length   = 0;	
	char imgType  = 0;	
	
	int bits      = 0;	

	fread (&length, 1, 1, file);
	fseek (file, 1, SEEK_CUR);

	fread (&imgType, 1, 1, file);
	fseek (file,     9, SEEK_CUR);

	fread (&sx_,  2, 1, file);
	fread (&sy_,  2, 1, file);
	fread (&bits, 1, 1, file);
	
	fseek(file, length + 1, SEEK_CUR);

	if (bits == 24 ||
		bits == 32)
		{
		bpp_ = bits / 8;
		
		try {
			data_ = new unsigned char [sx_ * sy_ * bpp_];
			}
		
		catch (...)
			{
			printf ("Sorry, the image is too big...\n");
			getch ();
			return false;
			}	
		
		unsigned char* line = 0;
		unsigned char  temp = 0;
		
		for (int y = 0; y < sy_; y ++)
			{
			line = &(data_ [sx_ * bpp_ * y]);

			fread (line, bpp_ * sx_, 1, file);
 	        
			for (int i = 0; i < sx_ * bpp_; i += bpp_) 
				{
				temp        = line [i];		
				line[i]     = line [i + 2];
				line[i + 2] = temp;
				}
			}
		}
	
	else
		{
		fclose (file);
		return false;	
		}
	
	flip ();
	
	fclose (file);

	return true;
	}

bool swTGA :: flip ()
	{
	
	
	if (!data_) return false;
	
	unsigned char temp = 0;
	
	for (int y = 0; y < sy_ / 2; y ++)
		for (int x = 0; x < sx_ * bpp_; x ++)
			{
			temp 						 	       = data_ [y             * sx_ * bpp_ + x];
			data_ [y             * sx_ * bpp_ + x] = data_ [(sy_ - y - 1) * sx_ * bpp_ + x];
			data_ [(sy_ - y - 1) * sx_ * bpp_ + x] = temp;
			}
	
	return true;	
	}


bool swTGA :: draw (HDC dc, int x0, int y0)
	{
	
	
	if (!data_) return false;
	
	for (int y = 0; y < sy_; y ++)
		for (int x = 0; x < sx_ * bpp_; x += bpp_)
			{
			SetPixel (dc, x0 + x / bpp_, y0 + y, RGB (data_ [y * sx_ * bpp_ + x + 0],
			   			    		   	              data_ [y * sx_ * bpp_ + x + 1],
												      data_ [y * sx_ * bpp_ + x + 2]));	
			}
	
	return true;	
	}

bool swTGA :: grey ()
	{
	
	
	if (!data_) return false;
	
	for (int y = 0; y < sy_; y ++)
		for (int x = 0; x < sx_ * bpp_; x += bpp_)
			{
			unsigned char midd = (data_ [y * sx_ * bpp_ + x + 0] + 
						  		  data_ [y * sx_ * bpp_ + x + 1] + 
						  		  data_ [y * sx_ * bpp_ + x + 2]) / 3;
			
			data_ [y * sx_ * bpp_ + x + 0] =
			data_ [y * sx_ * bpp_ + x + 1] =
			data_ [y * sx_ * bpp_ + x + 2] = midd;
			}		
	return true;
	}

bool swTGA :: get_mass (unsigned char* where)
	{
	
	
	if (!where || !data_) return false;
	
	for (int y = 0; y < sy_; y ++)
		for (int x = 0; x < sx_ * bpp_; x ++)
			where [y * sx_ * bpp_ + x] = data_ [y * sx_ * bpp_ + x]; 
	
    return true;
    }

//------------------------------------------------------------------------------

#endif
