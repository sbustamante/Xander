#include "allvars.hpp"

int main()
{
//Declaracion variables
  //Variables SDL
  SDL_Surface *Xander;
  SDL_Surface *Rock;
  SDL_Surface *Tree;
  SDL_Surface *Fondo;
  SDL_Surface *Screen;
  SDL_Surface *PantallaOculta;
  SDL_Rect XanderPH, fondo, XanderP, RockP, TreeP;
  SDL_Event suceso;
  //Variables C
//Uint8* teclas;
  int teclas;
  int i,j;
  int end=0;

//Incializa Libreria SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("No se pudo inicializar SDL: %s\n", SDL_GetError());
    exit(1);
  }

//Incializa Ventana Grafica
  Screen = SDL_SetVideoMode( 800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
  if( Screen == NULL )
  {
    printf( "Error al entrar a modo grafico: %s\n", SDL_GetError() );
    SDL_Quit();
    return -1;
 }

//Permite detectar si es presionada una tecla constantemente  
  SDL_EnableKeyRepeat(20, 20);

//Cambia el titulo de la ventana
  SDL_WM_SetCaption("Xander","Xander");

//Carga Imagenes
  PantallaOculta = SDL_CreateRGBSurface(SDL_SWSURFACE, 800, 600, 32, 0, 0, 0, 0);
  Fondo = SDL_LoadBMP("./pictures/Grass.bmp");  
  Xander = SDL_LoadBMP("./pictures/Xander.bmp");
  Rock= SDL_LoadBMP("./pictures/Rock.bmp");
  Tree= SDL_LoadBMP("./pictures/Tree.bmp");
  //Hace transparente la imagen
  SDL_SetColorKey(Xander, SDL_SRCCOLORKEY, SDL_MapRGB(Xander->format, 0, 255, 0));
  SDL_SetColorKey(Rock, SDL_SRCCOLORKEY, SDL_MapRGB(Xander->format, 0, 255, 0));
  SDL_SetColorKey(Tree, SDL_SRCCOLORKEY, SDL_MapRGB(Xander->format, 0, 255, 0));
  
  XanderPH.x=0;
  XanderPH.y=0;


//Ciclo repetitivo de movimiento
  while( end==0 )
  {
//Carga Fondo
    for(i=0;i<5;i++)
    {
    fondo.x=200*i;
    for(j=0;j<4;j++)
      { 
        fondo.y=200*j;
        SDL_BlitSurface(Fondo, NULL, PantallaOculta, &fondo);
      }
    }

//Carga Xander
    XanderP.x=XanderPH.x;
    XanderP.y=XanderPH.y;
    SDL_BlitSurface(Xander, NULL, PantallaOculta, &XanderP);

//Carga Rock
    RockP.x = 400;
    RockP.y = 200;
    SDL_BlitSurface(Rock, NULL, PantallaOculta, &RockP);
    
//Carga Tree
    TreeP.x = 200;
    TreeP.y = 300;
    SDL_BlitSurface(Tree, NULL, PantallaOculta, &TreeP);
    
//Actualiza la pantalla
    fondo.x=0;
    fondo.y=0;
    SDL_BlitSurface(PantallaOculta, NULL, Screen, &fondo);
    SDL_Flip(Screen);
      

//Comprueba Teclas
    //Para No esperar a presionar una tecla (incluso 2 teclas al tiempo) teclas (Uint8* teclas;)
  /*
  //Comprueba peticion de salida (tecla Esc)
    while (SDL_PollEvent(&suceso)) 
    {   
      if (suceso.type == SDL_KEYDOWN)
        if (suceso.key.keysym.sym == SDLK_ESCAPE)  end = 1; 
    }

  teclas = SDL_GetKeyState(NULL);

  if (teclas[SDLK_UP]) { XanderPH.y -= 10; }
  if (teclas[SDLK_DOWN]) { XanderPH.y += 10; }
  if (teclas[SDLK_RIGHT]) { XanderPH.x += 10; }
  if (teclas[SDLK_LEFT]) { XanderPH.x -= 10; }
*/

  //Para esperar a presionar una tecla  (int teclas;)
  teclas = nSDL_keypressed();  

  if (teclas == SDLK_UP) { XanderPH.y -= 20; }
  if (teclas == SDLK_DOWN) { XanderPH.y += 20; }
  if (teclas == SDLK_RIGHT) { XanderPH.x += 20; }
  if (teclas == SDLK_LEFT) { XanderPH.x -= 20; }
  if (teclas == SDLK_ESCAPE) { end = 1; }
  
//Se espera antes de repetir (50 ns)
    SDL_Delay( 50 );
  }

  SDL_Quit();
  return 1;
}
