/********************************************************************
			      HEADERS
********************************************************************/
#include <SDL/SDL.h>
#include <stdio.h>
#include <math.h>

//Funcion Alternativa que detecta una tecla por vez y detecta si es presionada constantemente, para el programa
int nSDL_getch()
{
  SDL_Event suceso;
// Imitacion de "getch()" para SDL
  while (1) {                            /* Repetimos indefinidamente */
    while (SDL_PollEvent(&suceso)) {     /* Comprobamos sucesos */
        if (suceso.type == SDL_KEYDOWN)  /* Si es tecla pulsada */
          return suceso.key.keysym.sym;  /* La devolvermos */
      }
  }
}

//Funcion Alternativa que detecta una tecla por vez y no detecta si es presionada constantemente, no para el programa
int nSDL_keypressed() 
{
  SDL_Event suceso;

    while (SDL_PollEvent(&suceso)) {     /* Comprobamos sucesos */
        if (suceso.type == SDL_KEYDOWN)  /* Si es tecla pulsada */
          return suceso.key.keysym.sym;  /* La devolvemos */
  }
  /* Si no hay tecla pulsada, devolvemos 0 (falso) */
  return 0;
}