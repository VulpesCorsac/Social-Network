#ifndef _SW_RESOURCES_H_
#define _SW_RESOURCES_H_

#define SW_USING_OPEN_GL

#include "../swGlass1.08/swGlass.h"

#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <math.h>

#include <string>
#include <vector>
#include <string>
#include <iosfwd>
#include <iostream>

#include "swLine.h"

using std :: cout;
using std :: endl;
using std :: string;
using std :: vector;
using std :: ostream;

enum SW_MAX_VALUES
	{
	MAX_ACTIV      = 100,
	MAX_RAND       = 1000,
	MAX_ARC        = 90,
	MAX_LINE_WIDTH = 4,
	MAX_MEMORY     = 70,
	MAX_L_NAME     = 32
	};

enum SW_BALL_NUMBERS
	{
	N_COLORS_ING = 3,
	};

enum SW_WND_SIZES
	{
	LEFT_BOR  = - 1, // left border
	RIGHT_BOR =   1,
	UP_BOR    =   1,
	DOWN_BOR  = - 1
	};

enum SW_DEFAULTS
	{
	DEFAULT_N_NODES = 1,
	};

enum SW_TEXT_CONSTS
	{
	N_ASCII_CODES    = 256,
	N_SYMBOLS_X      = 16,
	N_SYMBOLS_Y      = 16,
	SIZE_X_FONT_TEXT = 256,
	SIZE_Y_FONT_TEXT = 256
	};

enum SW_MASKS
	{
	SIXT_ZERO_SIXT_ONES = 0xffff,     //000000000000000111111111111111	
	SIXT_ONES_SIXT_ZERO = 0xffff0000 //111111111111111000000000000000	
	};

typedef unsigned int   arc_t;
typedef float          colr_t;
typedef float          font_t;
typedef line_t         pos_t;
typedef unsigned int   secs_t;
typedef unsigned int   indx_t;
typedef unsigned int   actv_t;
typedef char           byte_t;

const indx_t BALLS_PA = 4;


const colr_t PHONE_R = 0.8;
const colr_t PHONE_G = 0.8;	
const colr_t PHONE_B = 0.8;	

const colr_t TEXT_R  = 1;
const colr_t TEXT_G  = 1;
const colr_t TEXT_B  = 1;

const colr_t ARC_R   = 0.0;
const colr_t ARC_G   = 0.0;
const colr_t ARC_B   = 0.0;

const colr_t BALL_R  = 0.3;
const colr_t BALL_G  = 0.8;
const colr_t BALL_B  = 0.5;

const colr_t NODE_R  = 1.0;
const colr_t NODE_G  = 1.0;
const colr_t NODE_B  = 0.0;

const pos_t  NODE_RAD     =   0.07;
const pos_t  BALL_RAD     =   0.04;	
const pos_t  NODE_KOEF    =   0.65;
const pos_t  SHIFT_SCREEN =   0.1;
const pos_t  NODE_Z_COORD = - 0.1;
const pos_t  INFO_Z_COORD = - 0.2;
const pos_t  TEXT_Z_COORD = - 0.3;

const string DEF_DUMP_FNAME                ("../../Dump/dump.inf");
const string DEFAULT_START_FILE_CMD        ("start ../../Main/SocNetStart/SocialNetStart.exe");
const string DEFAULT_GRAPG_FILE            ("../../DATA/GRAPH.txt");
const string DEFAULT_APPHABET_FILE_TEXTURE ("../../DATA/Lol.tga");
const string DEFAULT_WINDOW_TITLE          ("Social Network (c) Gato & Vlad");

const colr_t NOT_BALLS     = - 1;
const arc_t  NOT_ARC       = 0;
const indx_t NOT_FREE_INFO = 0;
const pos_t  DEAD_NODE     = 0;

const pos_t  HALF_SQRT_2 = sqrt (2) / 2; 

const pos_t  PLUS_SCREEN  = 1.5; 
const pos_t  MINUS_SCREEN = 0.75; 

const font_t FONT_SX = 0.04;	
const font_t FONT_SY = 0.04;	

const int INFO_LINE_WIDTH = 1;
const int BITES_IN_BYTE   = 8;

#include "swTextOut.h"
#include "../ProjectFiles/swBall.h"
#include "../ProjectFiles/swNode.h"
#include "../ProjectFiles/swNodeManager.h"

#include "swFunctors.h"
#include "swButtonManager.h"

#endif
