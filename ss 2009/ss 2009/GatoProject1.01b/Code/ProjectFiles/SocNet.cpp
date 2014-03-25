#include "../Resources/swResources.h"
#include "../ProjectFiles/swSNetStartContainer.h"

swSNetStartContainer MAIN_CONTAINER;

bool on_key (int key, int)
	{
	bool static ft = true;
	if (ft)
		{
		Swamp :: OnSize2D (0, 0);
		ft = false;	
		}
		
	MAIN_CONTAINER.on_key (key);
	
	return true;
	}

//vlad
#include <fstream>
#include <iostream>
using namespace std;

bool on_l_click (int, int)
	{
  ofstream out_stream_of_figna;
  out_stream_of_figna.open( "zopa.txt" );

 // if( out_stream_of_figna.bad() )
 // {
 //   cerr << "Bad opening of file";
 //   out_stream_of_figna.close();
 //   return false;
 // }

  swNodeManager* net = MAIN_CONTAINER.nm();
  indx_t size = net -> size();
  //cout << size << endl;

/* 
  //printing all matrix
  for( int i = 0 ; i < size ; ++i )
  {
    for( int j = 0 ; j < size ; ++j )
    {
    cout << net -> get_arcs () [i*size+j] << " " ;
    }
  cout << endl;
  }
*/
/*
  int matr [8*8] =  { 
                    0,1,0,0,0,1,0,0,
                    1,0,1,1,1,0,0,0,
                    0,1,0,1,0,0,0,0,
                    0,1,1,0,1,1,0,0,
                    0,1,0,1,0,0,0,0,
                    1,0,0,1,0,0,1,0,
                    0,0,0,0,0,1,0,1,
                    0,0,0,0,0,0,1,0,
                    };
*/
/*
  const int size = 6;
  int matr [6*6] =  { 
                    0,1,1,0,0,0,
                    1,0,1,1,0,0,
                    1,1,0,0,1,0,
                    0,1,0,0,1,1,
                    0,0,1,1,0,1,
                    0,0,0,1,1,0,
                    };

*/
  bool matr [size*size];

/**/
  //bool the matrix
  
  for( int i = 0 ; i < size ; i ++ )
  {
    for( int j = 0 ; j < size ; j ++ )
    {
    matr [i*size+j] = (bool) net -> get_arcs() [i*size+j];
    }
  }

  cout << "we are here!" << endl;
  //set 1 on diag
  for( int i = 0 ; i < size ; i ++ )
  {
    matr[i*size+i] = 1;
  }

  /*
  //print logical matrix
  for( int i = 0 ; i < size ; ++i )
  {
    for( int j = 0 ; j < size ; ++j )
    {
    cout << matr [i*size+j] << "" ;
    }
  cout << endl;
  }
*/

/*
  int answer = 0;
  //int is
  int bad = 0;
  for ( int k = 0 ; k < size ; k++ )
  {
    for ( int j = k ; j < size ; j++ )
    {
      if( matr[k*size+j] == 0 )
      {
        bad = 0;
        for ( int pp = 0 ; pp < size ; pp++ )
        {
          if( matr[k*size+pp] && matr[j*size+pp] )
          {
            bad = 1;
          }
        }
        if( bad == 0 )
        {
          answer ++ ;
          //cout << net -> get_objs()[k].str() << " - " ;
          //cout << net -> get_objs()[j].str() << endl;
          if( answer < 1000 )
            {
            cout << net -> get_objs()[k] << " - "
                 << net -> get_objs()[j] << "\n";
            }
        }
      }
    }
  }

//  cout << "\n" << answer << endl;
  */


  int answers [size*size];//= {0};
              for( int i = 0 ; i < size*size ; ++ i ) { answers[i] = 0; }
  for ( int el = 0 ; el < size ; ++ el )
  {
    //for ( int fr = 0 ; fr < size ; ++ fr )
    for ( int fr = el+1 ; fr < size ; ++ fr )
    {
      //for ( int j = 0 ; j < size ; ++ j )
      for ( int j = 0 ; j < size ; ++ j )
      {
        if( matr [el*size+j] && matr [fr*size+j] )
        {
          answers [el*size+fr] ++ ;       
        }
      }
    }
  }
  int i = 0;
  cout << "we are here!" << endl;
  out_stream_of_figna << "\nt\n" << i << endl;

  FILE* file = fopen( "file_out.txt", "w" );

  //printing answer matrix
  for( int i = 0 ; i < size ; i ++ )
  {
    for( int j = 0 ; j < size ; j ++ )
    {
   // cout << answers [i*size+j] << " " ;
   //out_stream_of_figna << answers [i*size+j] << " " ;
      fprintf( file, "%d ", answers [i*size+j] );
    }
  //cout << "\n";
//  out_stream_of_figna << "\n";
  fprintf( file, "\n" );
  }
  out_stream_of_figna << endl << flush;


  fclose( file );

  out_stream_of_figna.close();  


  int pers = 0;
//бј√ј - зр€ считаю нули в этом ифе - надо наверно строить полную матрицу дл€ работы с каждым элементом
  cin >> pers;
  for( int i  = 0 ; i < size ; i ++ )
  {
    if( answers [pers*size+i] )
    {
      cout << net -> get_objs()[i] << "\t" << answers [pers*size+i] << '\n';
    }
  }


	return true;	
	}

bool on_r_click (int, int)
{
/*  swNodeManager* net = MAIN_CONTAINER.nm();
  indx_t size = net -> size();

  int pers = 0;
  cin >> pers;
  for( int i  = 0 ; i < size ; i ++ )
  {
    cout << net -> get_objs()[i] << ' - ' << answers

  }
*/
}



int main ()
	{

	use_handle_mouse ();

	__GLASS_WND.add_msg (swMsg (WM_KEYDOWN, on_key));

	//__GLASS_WND.add_msg (swMsg (WM_LBUTTONDOWN, on_l_click));

	//__GLASS_WND.add_msg (swMsg (WM_RBUTTONDOWN, on_r_click));

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
