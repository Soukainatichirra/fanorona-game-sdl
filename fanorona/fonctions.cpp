#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>

#include <cstdio>
#include "header.h"


    // Sturcutre SPion
    typedef struct SPion {
     SDL_Rect position ;
     int color ;
    } SPion ;

    typedef struct PionS {
     int ligne ;
     int colone ;
    } PionS ;

// Variables et initialisations
    SDL_Rect positionFond;
    SPion pion[5][9] ;
    PionS PionSelected ;
    int i,j;

    SDL_Surface* screen = SDL_SetVideoMode(1122,781, 24,SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_Surface* imageDeFond = SDL_LoadBMP("fond.bmp");
    SDL_Surface *PionBlanc = SDL_LoadBMP("Blanc.bmp");
    SDL_Surface *PionNoir = SDL_LoadBMP("Noir.bmp");
    SDL_Surface *PionSelectedNoir = SDL_LoadBMP("NoirSelected.bmp");
    SDL_Surface *PionSelectedBlanc = SDL_LoadBMP("BlancSelected.bmp");

void afficher () {

}

