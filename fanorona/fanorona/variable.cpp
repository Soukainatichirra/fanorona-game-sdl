#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#include <SDL/SDL.h>
#include <cstdio>
#include "variable.h"

/*void affichier (SPion pion[5][9],int i,int j) {
/*if (pion[i][j].color==0) { SDL_SetColorKey(PionNoir, SDL_SRCCOLORKEY, SDL_MapRGB(PionNoir->format, 255,255, 255));
                            SDL_BlitSurface(PionNoir, NULL, screen, &pion[i][j].position);}
else { SDL_SetColorKey(PionBlanc, SDL_SRCCOLORKEY, SDL_MapRGB(PionNoir->format, 255,255, 255));
                            SDL_BlitSurface(PionBlanc, NULL, screen, &pion[i][j].position);} */

