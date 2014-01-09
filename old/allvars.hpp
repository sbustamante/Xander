/****************************************************************************************
    EXTERNAL LIBRARIES
****************************************************************************************/
#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <typeinfo>

using namespace std;

/****************************************************************************************
    FUNCTIONS
****************************************************************************************/
/*Alternative function to detect one key per time, and detect if it has been pressed 
constantly*/
int nSDL_getch()
{
  SDL_Event suceso;
  //Imitation of "getch()" for SDL
  while (1) {                            
    while (SDL_PollEvent(&suceso)) {     
        if (suceso.type == SDL_KEYDOWN)  
          return suceso.key.keysym.sym;
      }
  }
}


/*Alternative function to detect one key per time, and don't detect if it has been pressed 
constantly*/
int nSDL_keypressed() 
{
  SDL_Event suceso;

    while (SDL_PollEvent(&suceso)) {   
        if (suceso.type == SDL_KEYDOWN)
          return suceso.key.keysym.sym;
  }
  return 0;
}


/*Convert a data file text in plain text */
int in2dump( char filename[] )
{
    char cmd[100];
    sprintf( cmd, "grep -v \"#\" %s > %s.dump", 
	     filename, filename );
    system( cmd );

    return 0;
}


/*This function will convert anything to a string! */
template <class T>
string toString( T argument )
{
       string r;
       stringstream s;
       char str[30];
//        printf("out\n");
       if(!strcmp(typeid(argument).name(),"d")){
	 sprintf(str,"%.5lf",(double)argument);
	 r=string(str); 
       }//*/
       if(!strcmp(typeid(argument).name(),"i")){
	 s << argument;
	 r = s.str();}
       
       return r;
}

/****************************************************************************************
    MACROS, GLOBAL VARIABLES AND INTERNAL HEADERS
****************************************************************************************/
#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600

#define SCN_X 16
#define SCN_Y 12
#define SCN_H 50.
#define SCN_W 50.

string DATA_FOLDER = "./data/";
string SCN_FOLDER = "scenarios/";


#include "characters.hpp"
