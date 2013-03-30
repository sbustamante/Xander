#include "allvars.hpp"

int main()
{
    //Scenario
    Environment scene;
    //Objects
    Object rock, xander, tree;
    //General Variables
    SDL_Event suceso;
    int teclas;
    int end=0;


    //Detect a key constantly pressed
    SDL_EnableKeyRepeat(20, 20);
  

    //Initalizing objects
    rock.SetSurface( "./data/Rock.bmp" );
    rock.SetCoordinates( 200, 500 );
    
    tree.SetSurface( "./data/Tree.bmp" );
    tree.SetCoordinates( 150, 0 );
    
    xander.SetSurface( "./data/Xander.bmp" );
    xander.SetCoordinates( 0, 0 );


    //Initalizing Scenario
    scene.SetName( "Xander" );
    scene.Initalize();
    scene.LoadScenario( "./data/scenarios/Scene01.scn" );
    scene.SetSurfaces();
    
    //General Game Loop
    while( end==0 )
    {
	    	
	teclas = nSDL_keypressed();  
	if (teclas == SDLK_UP) { xander.coor.y -= 5; }
	if (teclas == SDLK_DOWN) { xander.coor.y += 5; }
	if (teclas == SDLK_RIGHT) { xander.coor.x += 5; }
	if (teclas == SDLK_LEFT) { xander.coor.x -= 5; }
	if (teclas == SDLK_ESCAPE) { end = 1; }

	//Draw Frames
	scene.Draw();
	xander.Draw( scene.hidden_surface );
	rock.Draw( scene.hidden_surface );
	tree.Draw( scene.hidden_surface );
	scene.Update();

	SDL_Delay( 0 );
    }

    SDL_Quit();
    return 1;
}
