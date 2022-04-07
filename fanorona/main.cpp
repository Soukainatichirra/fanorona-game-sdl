#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#include <SDL/SDL.h>
#include <cstdio>
#include <time.h>

//structures du jeu
struct SPion
{
    SDL_Rect position ;
    int color ;
} Spion ;

struct PionSlct
{
    int ligne ;
    int colone ;
    int color ;
} ;

//signatures
int eight_or_four(int i);
int eat_no_more(int i);
int color_eaten (SPion pion[5][9],int SelectedColor) ;
int mvtpossibleExist (int i,int j,SPion pion[5][9]);
void show (int i,int j,SPion pion[5][9],SDL_Surface *PionNoir,SDL_Surface *PionBlanc,SDL_Surface* screen,SDL_Surface *PionSelectedNoir,SDL_Surface *PionSelectedBlanc);
void show_EV(SPion pion[5][9],SDL_Surface *PionNoir,SDL_Surface *PionBlanc,SDL_Surface* screen,SDL_Surface* PionSelectedNoir,SDL_Surface* PionSelectedBlanc);


//fonctions
int eight_or_four(int i)
{

    if (i%2==0)
    {
        return 4;
    }
    else
    {
        return 8;
    }
}
int mvtpossibleExist (int i,int j,SPion pion[5][9])
{
    if (eight_or_four(i)==4)
    {
        if ((pion[i-1][j].color==2)||(pion[i][j+1].color==2)||(pion[i+1][j].color==2)||(pion[i][j-1].color==2))
        {
            return 1 ;
        }
        return 0;
    }
    if (eight_or_four(i)==8)
    {
        if ((pion[i-1][j].color==2)||(pion[i][j+1].color==2)||(pion[i+1][j].color==2)||(pion[i][j-1].color==2)||(pion[i-1][j-1].color==2)||(pion[i-1][j+1].color==2)||(pion[i+1][j+1].color==2)||(pion[i+1][j-1].color==2))
        {
            return 1 ;
        }
        return 0;
    }
}


void show (int i,int j,SPion pion[5][9],SDL_Surface *PionNoir,SDL_Surface *PionBlanc,SDL_Surface* screen,SDL_Surface *PionSelectedNoir,SDL_Surface *PionSelectedBlanc)
{
    if (pion[i][j].color==0)
    {
        SDL_SetColorKey(PionNoir, SDL_SRCCOLORKEY, SDL_MapRGB(PionNoir->format, 255,255, 255));
        SDL_BlitSurface(PionNoir, NULL, screen, &pion[i][j].position);
    }
    if (pion[i][j].color==1)
    {
        SDL_SetColorKey(PionBlanc, SDL_SRCCOLORKEY, SDL_MapRGB(PionBlanc->format, 0,0, 0));
        SDL_BlitSurface(PionBlanc, NULL, screen, &pion[i][j].position);
    }
    if(pion[i][j].color==3)
    {
        SDL_SetColorKey(PionSelectedNoir, SDL_SRCCOLORKEY, SDL_MapRGB(PionSelectedNoir->format, 255,255, 255)) ;
        SDL_BlitSurface(PionSelectedNoir, NULL, screen, &pion[i][j].position);

    }
    if(pion[i][j].color==4)
    {
        SDL_SetColorKey(PionSelectedBlanc, SDL_SRCCOLORKEY, SDL_MapRGB(PionSelectedBlanc->format, 255,255, 255)) ;
        SDL_BlitSurface(PionSelectedBlanc, NULL, screen, &pion[i][j].position);

    }

}

int SelectedPion(SPion pion[5][9],int* l,int* c,SDL_Event event,SDL_Surface *PionNoir,SDL_Surface *PionBlanc,SDL_Surface* screen,SDL_Surface *PionSelectedNoir,SDL_Surface *PionSelectedBlanc,int* lastcolor)
{
    int i,j;
    for (i=0; i<=4; i++)
    {
        for (j=0; j<=8; j++)
        {
            if ((pion[i][j].position.x<=event.button.x)&&(event.button.x<=pion[i][j].position.x+76)&&(pion[i][j].position.y<=event.button.y)&&(event.button.y<=pion[i][j].position.y+80))
            {
                if ((mvtpossibleExist(i,j,pion)==1))
                {
                    *l=i ;
                    *c=j ;
                    if(pion[*l][*c].color==0)
                    {
                        pion[*l][*c].color=3 ;
                        *lastcolor=0 ;
                    }
                    if(pion[*l][*c].color==1)
                    {
                        pion[*l][*c].color=4 ;
                        *lastcolor=1 ;
                    }
                    if (pion[*l][*c].color==2)
                    {
                        return 0;
                    }


                    return 1;
                }


            }


        }
    }
    return 0;

}

int verify_new_position (SPion pion[5][9],int* l,int* c,int SelectedP_L,int SelectedP_C,SDL_Event event)
{
    int i,j,k;
    for (i=0; i<=4; i++)
    {
        for (j=0; j<=8; j++)
        {
            if ((pion[i][j].position.x<=event.button.x)&&(event.button.x<=pion[i][j].position.x+76)&&(pion[i][j].position.y<=event.button.y)&&(event.button.y<=pion[i][j].position.y+80))
            {

                if (pion[i][j].color==2)
                {
                    k=eight_or_four(i) ;
                    if (k==4)
                    {
                        if ((SelectedP_L+1==i)&&(SelectedP_C==j)||(SelectedP_L-1==i)&&(SelectedP_C==j)||(SelectedP_L==i)&&(SelectedP_C-1==j)||(SelectedP_L==i)&&(SelectedP_C+1==j))
                        {
                            *l=i ;
                            *c=j ;
                            return 0;
                        }
                        else
                        {
                            return 1;
                        }
                    }
                    if (k==8)
                    {
                        if ((SelectedP_L+1==i)&&(SelectedP_C==j)||(SelectedP_L-1==i)&&(SelectedP_C==j)||(SelectedP_L==i)&&(SelectedP_C-1==j)||(SelectedP_L==i)&&(SelectedP_C+1==j)||(SelectedP_L+1==i)&&(SelectedP_C+1==j)||(SelectedP_L-1==i)&&(SelectedP_C+1==j)||(SelectedP_L-1==i)&&(SelectedP_C-1==j)||(SelectedP_L+1==i)&&(SelectedP_C-1==j))
                        {
                            *l=i ;
                            *c=j ;
                            return 0;
                        }
                        else
                        {
                            return 1;
                        }

                    }

                }
            }


        }
    }

}



void UnSelectedPion(SPion pion[5][9],int i,int j,SDL_Surface *PionNoir,SDL_Surface *PionBlanc,SDL_Surface* screen,SDL_Surface *PionSelectedNoir,SDL_Surface *PionSelectedBlanc)
{
    if(pion[i][j].color==3)
    {
        pion[i][j].color=0 ;
    }
    if(pion[i][j].color==4)
    {
        pion[i][j].color=1 ;
    }
    show(i,j,pion,PionNoir,PionBlanc,screen,PionSelectedNoir,PionSelectedBlanc);
}

void show_EV(SPion pion[5][9],SDL_Surface *PionNoir,SDL_Surface *PionBlanc,SDL_Surface* screen,SDL_Surface* PionSelectedNoir,SDL_Surface* PionSelectedBlanc)
{

    int i,j;
    for (i=0; i<=4; i++)
    {
        for (j=0; j<=8; j++)
        {
            show(i,j,pion,PionNoir,PionBlanc,screen,PionSelectedNoir,PionSelectedBlanc);
        }
    }
    SDL_Flip(screen);
}

void show_window(SDL_Surface* screen,SDL_Surface* Vangogh,SDL_Rect positionFond)
{
    SDL_SetColorKey(Vangogh, SDL_SRCCOLORKEY, SDL_MapRGB(Vangogh->format, 255,255, 255));
    SDL_BlitSurface(Vangogh, NULL, screen, &positionFond);
    SDL_Flip(screen);
}

void deplacer (SPion pion[5][9],int* ligne,int* colone,int toligne,int tocolone,SDL_Surface *PionNoir,SDL_Surface *PionBlanc,SDL_Surface* screen,SDL_Surface *PionSelectedNoir,SDL_Surface *PionSelectedBlanc)
{
    if ((pion[*ligne][*colone].color==3)||(pion[*ligne][*colone].color==4))
    {
        pion[toligne][tocolone].color=pion[*ligne][*colone].color ;
        pion[*ligne][*colone].color=2;
        *ligne=toligne;
        *colone=tocolone;
    }
    else {}

}
void eat_back (SPion pion[5][9],int aftermvt_ligne,int aftermvt_colone,int beforemvt_ligne,int beforemvt_colone,int *a)
{

    //gauche à droite
    if ((beforemvt_ligne==aftermvt_ligne)&&(beforemvt_colone+1==aftermvt_colone))
    {
        int i=beforemvt_ligne,j=beforemvt_colone-1,ver=1;
        if (pion[i][j].color!=2)
        {
            while((i<=4)&&(j>=0)&&(ver==1)&&(pion[i][j].color!=2))
            {
                if (pion[aftermvt_ligne][aftermvt_colone].color==3)
                {
                    if (pion[i][j].color!=0)
                    {
                        pion[i][j].color=2 ;
                        j=j-1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }
                }
                if (pion[aftermvt_ligne][aftermvt_colone].color==4)
                {
                    if (pion[i][j].color!=1)
                    {
                        pion[i][j].color=2 ;
                        j=j-1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }

                }
            }
        }
    }

    //droite à gauche
    if ((beforemvt_ligne==aftermvt_ligne)&&(beforemvt_colone-1==aftermvt_colone))
    {
        int i=beforemvt_ligne,j=beforemvt_colone+1,ver=1;
        if (pion[i][j].color!=2)
        {
            while((i<=4)&&(j<=8)&&(ver==1)&&(pion[i][j].color!=2))
            {
                if (pion[aftermvt_ligne][aftermvt_colone].color==3)
                {
                    if (pion[i][j].color!=0)
                    {
                        pion[i][j].color=2 ;
                        j=j+1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }
                }
                if (pion[aftermvt_ligne][aftermvt_colone].color==4)
                {
                    if (pion[i][j].color!=1)
                    {
                        pion[i][j].color=2 ;
                        j=j+1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }

                }
            }
        }
    }
    //Diagonale à droite \ de haut à bas
    if ((beforemvt_ligne+1==aftermvt_ligne)&&(beforemvt_colone+1==aftermvt_colone))
    {
        int i=beforemvt_ligne-1,j=beforemvt_colone-1,ver=1;
        if (pion[i][j].color!=2)
        {
            while((i>=0)&&(j>=0)&&(ver==1)&&(pion[i][j].color!=2))
            {
                if (pion[aftermvt_ligne][aftermvt_colone].color==3)
                {
                    if (pion[i][j].color!=0)
                    {
                        pion[i][j].color=2 ;
                        j=j-1 ;
                        i=i-1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }
                }
                if (pion[aftermvt_ligne][aftermvt_colone].color==4)
                {
                    if (pion[i][j].color!=1)
                    {
                        pion[i][j].color=2 ;
                        j=j-1 ;
                        i=i-1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }

                }
            }
        }
    }


    //Diagonale à droite \ de bas à haut
    if ((beforemvt_ligne-1==aftermvt_ligne)&&(beforemvt_colone-1==aftermvt_colone))
    {
        int i=beforemvt_ligne+1,j=beforemvt_colone+1,ver=1;
        if (pion[i][j].color!=2)
        {
            while((i<=4)&&(j<=8)&&(ver==1)&&(pion[i][j].color!=2))
            {
                if (pion[aftermvt_ligne][aftermvt_colone].color==3)
                {
                    if (pion[i][j].color!=0)
                    {
                        pion[i][j].color=2 ;
                        j=j+1 ;
                        i=i+1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }
                }
                if (pion[aftermvt_ligne][aftermvt_colone].color==4)
                {
                    if (pion[i][j].color!=1)
                    {
                        pion[i][j].color=2 ;
                        j=j+1 ;
                        i=i+1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }

                }
            }
        }
    }
    //Diagonale à GAUCHE / de bas à haut
    if ((beforemvt_ligne-1==aftermvt_ligne)&&(beforemvt_colone+1==aftermvt_colone))
    {
        int i=beforemvt_ligne+1,j=beforemvt_colone-1,ver=1;
        if (pion[i][j].color!=2)
        {
            while((i<=4)&&(j>=0)&&(ver==1)&&(pion[i][j].color!=2))
            {
                if (pion[aftermvt_ligne][aftermvt_colone].color==3)
                {
                    if (pion[i][j].color!=0)
                    {
                        pion[i][j].color=2 ;
                        j=j-1 ;
                        i=i+1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }
                }
                if (pion[aftermvt_ligne][aftermvt_colone].color==4)
                {
                    if (pion[i][j].color!=1)
                    {
                        pion[i][j].color=2 ;
                        j=j-1 ;
                        i=i+1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }

                }
            }
        }
    }
    //Diagonale à GAUCHE / de haut à bas
    if ((beforemvt_ligne+1==aftermvt_ligne)&&(beforemvt_colone-1==aftermvt_colone))
    {
        int i=beforemvt_ligne-1,j=beforemvt_colone+1,ver=1;
        if (pion[i][j].color!=2)
        {
            while((i>=0)&&(j<=8)&&(ver==1)&&(pion[i][j].color!=2))
            {
                if (pion[aftermvt_ligne][aftermvt_colone].color==3)
                {
                    if (pion[i][j].color!=0)
                    {
                        pion[i][j].color=2 ;
                        j=j+1 ;
                        i=i-1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }
                }
                if (pion[aftermvt_ligne][aftermvt_colone].color==4)
                {
                    if (pion[i][j].color!=1)
                    {
                        pion[i][j].color=2 ;
                        j=j+1 ;
                        i=i-1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }

                }
            }
        }
    }

    //De bas A haut
    if ((beforemvt_ligne-1==aftermvt_ligne)&&(beforemvt_colone==aftermvt_colone))
    {
        int i=beforemvt_ligne+1,j=beforemvt_colone,ver=1;
        if (pion[i][j].color!=2)
        {
            while((i<=4)&&(ver==1)&&(pion[i][j].color!=2))
            {
                if (pion[aftermvt_ligne][aftermvt_colone].color==3)
                {
                    if (pion[i][j].color!=0)
                    {
                        pion[i][j].color=2 ;
                        i=i+1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }
                }
                if (pion[aftermvt_ligne][aftermvt_colone].color==4)
                {
                    if (pion[i][j].color!=1)
                    {
                        pion[i][j].color=2 ;
                        i=i+1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }

                }
            }
        }
    }

    //De haut a bas
    if ((beforemvt_ligne+1==aftermvt_ligne)&&(beforemvt_colone==aftermvt_colone))
    {
        int i=beforemvt_ligne-1,j=beforemvt_colone,ver=1;
        if (pion[i][j].color!=2)
        {
            while((i>=0)&&(ver==1)&&(pion[i][j].color!=2))
            {
                if (pion[aftermvt_ligne][aftermvt_colone].color==3)
                {
                    if (pion[i][j].color!=0)
                    {
                        pion[i][j].color=2 ;
                        i=i-1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }
                }
                if (pion[aftermvt_ligne][aftermvt_colone].color==4)
                {
                    if (pion[i][j].color!=1)
                    {
                        pion[i][j].color=2 ;
                        i=i-1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }

                }
            }
        }
    }



}

void eat_front (SPion pion[5][9],int aftermvt_ligne,int aftermvt_colone,int beforemvt_ligne,int beforemvt_colone,int *a)
{
    //Diagonale à droite "\ de haut a bas"
    if ((beforemvt_ligne+1==aftermvt_ligne)&&(beforemvt_colone+1==aftermvt_colone))
    {
        int i=aftermvt_ligne+1,j=aftermvt_colone+1,ver=1;
        if (pion[i][j].color!=2)
        {
            while((i<=4)&&(j<=8)&&(ver==1)&&(pion[i][j].color!=2))
            {
                if (pion[aftermvt_ligne][aftermvt_colone].color==3)
                {
                    if (pion[i][j].color!=0)
                    {
                        pion[i][j].color=2 ;
                        i=i+1;
                        j=j+1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }
                }
                if (pion[aftermvt_ligne][aftermvt_colone].color==4)
                {
                    if (pion[i][j].color!=1)
                    {
                        pion[i][j].color=2 ;
                        i=i+1;
                        j=j+1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }

                }
            }
        }

    }



    //Diagonale à droite "\ de bas a haut"
    if ((beforemvt_ligne-1==aftermvt_ligne)&&(beforemvt_colone-1==aftermvt_colone))
    {
        int i=aftermvt_ligne-1,j=aftermvt_colone-1,ver=1;
        if (pion[i][j].color!=2)
        {
            while((i>=0)&&(j>=0)&&(ver==1)&&(pion[i][j].color!=2))
            {
                if (pion[aftermvt_ligne][aftermvt_colone].color==3)
                {
                    if (pion[i][j].color!=0)
                    {
                        pion[i][j].color=2 ;
                        i=i-1;
                        j=j-1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }
                }
                if (pion[aftermvt_ligne][aftermvt_colone].color==4)
                {
                    if (pion[i][j].color!=1)
                    {
                        pion[i][j].color=2 ;
                        i=i-1;
                        j=j-1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }

                }
            }
        }

    }



    //Diagonale à gauche "/ de haut a bas"
    if ((beforemvt_ligne+1==aftermvt_ligne)&&(beforemvt_colone-1==aftermvt_colone))
    {
        int i=aftermvt_ligne+1,j=aftermvt_colone-1,ver=1;
        if (pion[i][j].color!=2)
        {
            while((i<=4)&&(j>=0)&&(ver==1)&&(pion[i][j].color!=2))
            {
                if (pion[aftermvt_ligne][aftermvt_colone].color==3)
                {
                    if (pion[i][j].color!=0)
                    {
                        pion[i][j].color=2 ;
                        i=i+1;
                        j=j-1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }
                }
                if (pion[aftermvt_ligne][aftermvt_colone].color==4)
                {
                    if (pion[i][j].color!=1)
                    {
                        pion[i][j].color=2 ;
                        i=i+1;
                        j=j-1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;

                    }

                }
            }
        }

    }

    //Diagonale à gauche "/ de bas a haut"
    if ((beforemvt_ligne-1==aftermvt_ligne)&&(beforemvt_colone+1==aftermvt_colone))
    {
        int i=aftermvt_ligne-1,j=aftermvt_colone+1,ver=1;
        if (pion[i][j].color!=2)
        {
            while((i>=0)&&(j<=8)&&(ver==1)&&(pion[i][j].color!=2))
            {
                if (pion[aftermvt_ligne][aftermvt_colone].color==3)
                {
                    if (pion[i][j].color!=0)
                    {
                        pion[i][j].color=2 ;
                        i=i-1;
                        j=j+1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }
                }
                if (pion[aftermvt_ligne][aftermvt_colone].color==4)
                {
                    if (pion[i][j].color!=1)
                    {
                        pion[i][j].color=2 ;
                        i=i-1;
                        j=j+1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;

                    }

                }
            }
        }

    }

    //gauche à droite
    if ((beforemvt_ligne==aftermvt_ligne)&&(beforemvt_colone+1==aftermvt_colone))
    {
        int i=aftermvt_ligne,j=aftermvt_colone+1,ver=1;
        if (pion[i][j].color!=2)
        {
            while((i<=4)&&(j<=8)&&(ver==1)&&(pion[i][j].color!=2))
            {
                if (pion[aftermvt_ligne][aftermvt_colone].color==3)
                {
                    if (pion[i][j].color!=0)
                    {
                        pion[i][j].color=2 ;
                        j=j+1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }
                }
                if (pion[aftermvt_ligne][aftermvt_colone].color==4)
                {
                    if (pion[i][j].color!=1)
                    {
                        pion[i][j].color=2 ;
                        j=j+1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }

                }
            }
        }
    }

//De droite à gauche
    if ((beforemvt_ligne==aftermvt_ligne)&&(beforemvt_colone-1==aftermvt_colone))
    {
        int i=aftermvt_ligne,j=aftermvt_colone-1,ver=1;
        if(pion[i][j].color!=2)
        {
            while((j>=0)&&(ver==1)&&(pion[i][j].color!=2))
            {
                if (pion[aftermvt_ligne][aftermvt_colone].color==3)
                {
                    if (pion[i][j].color!=0)
                    {
                        pion[i][j].color=2 ;
                        j=j-1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }
                }
                if (pion[aftermvt_ligne][aftermvt_colone].color==4)
                {
                    if (pion[i][j].color!=1)
                    {
                        pion[i][j].color=2 ;
                        j=j-1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }

                }
            }
        }

    }

//De Haut à Bas
    if ((beforemvt_ligne+1==aftermvt_ligne)&&(beforemvt_colone==aftermvt_colone))
    {
        int i=aftermvt_ligne+1,j=aftermvt_colone,ver=1;
        if(pion[i][j].color!=2)
        {
            while((i<=4)&&(ver==1)&&(pion[i][j].color!=2))
            {
                if (pion[aftermvt_ligne][aftermvt_colone].color==3)
                {
                    if (pion[i][j].color!=0)
                    {
                        pion[i][j].color=2 ;
                        i=i+1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }
                }
                if (pion[aftermvt_ligne][aftermvt_colone].color==4)
                {
                    if (pion[i][j].color!=1)
                    {
                        pion[i][j].color=2 ;
                        i=i+1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }

                }
            }
        }

    }

    //De Bas à Haut
    if ((beforemvt_ligne-1==aftermvt_ligne)&&(beforemvt_colone==aftermvt_colone))
    {
        int i=aftermvt_ligne-1,j=aftermvt_colone,ver=1;
        if((pion[i][j].color!=2))
        {
            while((i>=0)&&(ver==1)&&(pion[i][j].color!=2))
            {
                if (pion[aftermvt_ligne][aftermvt_colone].color==3)
                {
                    if (pion[i][j].color!=0)
                    {
                        pion[i][j].color=2 ;
                        i=i-1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }
                }
                if (pion[aftermvt_ligne][aftermvt_colone].color==4)
                {
                    if (pion[i][j].color!=1)
                    {
                        pion[i][j].color=2 ;
                        i=i-1 ;
                        *a=1;
                    }
                    else
                    {
                        ver=0 ;
                    }

                }
            }
        }

    }




}
int color_eaten (SPion pion[5][9],int SelectedColor)
{
    if (SelectedColor==3)
    {
        return 1;
    }
    if (SelectedColor==4)
    {
        return 0;
    }
}

int eat_no_more (SPion pion[5][9],int i,int j)
{
    //if ((i-2<=0)||(i+2>=4)||(j-2<=0)||(j+2>=8)) {return 1;}
    if (eight_or_four(i)==4)
    {
        if (((pion[i-1][j].color==2)&&(pion[i-2][j].color==color_eaten(pion,pion[i][j].color))&&(i-2>=0))
                ||((pion[i][j+1].color==2)&&(pion[i][j+2].color==color_eaten(pion,pion[i][j].color))&&(j+2<=8))
                ||((pion[i+1][j].color==2)&&(pion[i+2][j].color==color_eaten(pion,pion[i][j].color))&&(i+2<=8))
                ||((pion[i][j-1].color==2)&&(pion[i][j-2].color==color_eaten(pion,pion[i][j].color))&&(j-2>=0)))

        {
            return 0 ;
        }
        if (((pion[i-1][j].color==2)&&(pion[i+1][j].color==color_eaten(pion,pion[i][j].color))&&(i-1>=0)&&(i+1<=8))
                ||((pion[i][j+1].color==2)&&(pion[i][j-1].color==color_eaten(pion,pion[i][j].color))&&(j+1<=8)&&(j-1>=0))
                ||((pion[i+1][j].color==2)&&(pion[i-1][j].color==color_eaten(pion,pion[i][j].color))&&(i+1<=8)&&(i-1>=0))
                ||((pion[i][j-1].color==2)&&(pion[i][j+1].color==color_eaten(pion,pion[i][j].color))&&(j+1<=8)&&(j-1>=0)))

        {
            return 0 ;
        }
        return 1;
    }
    if (eight_or_four(i)==8)
    {
        if (((pion[i-1][j].color==2)&&(pion[i-2][j].color==color_eaten(pion,pion[i][j].color))&&(i-2>=0))
                ||((pion[i][j+1].color==2)&&(pion[i][j+2].color==color_eaten(pion,pion[i][j].color))&&(j+2>=0))
                ||((pion[i+1][j].color==2)&&(pion[i+2][j].color==color_eaten(pion,pion[i][j].color))&&(i+2>=0))
                ||((pion[i][j-1].color==2)&&(pion[i][j-2].color==color_eaten(pion,pion[i][j].color))&&(j-2>=0))
                ||((pion[i-1][j-1].color==2)&&(pion[i-2][j-2].color==color_eaten(pion,pion[i][j].color))&&(i-2>=0)&&(j-2>=0))
                ||((pion[i-1][j+1].color==2)&&(pion[i-2][j+2].color==color_eaten(pion,pion[i][j].color))&&(i-2>=0)&&(j+2<=8))
                ||((pion[i+1][j+1].color==2)&&(pion[i+2][j+2].color==color_eaten(pion,pion[i][j].color))&&(i+2<=4)&&(j+2<=8))
                ||((pion[i+1][j-1].color==2)&&(pion[i+2][j-2].color==color_eaten(pion,pion[i][j].color))&&(i+2<=4)&&(j-2>=0)))

        {
            return 0 ;
        }
        if (((pion[i-1][j].color==2)&&(pion[i+1][j].color==color_eaten(pion,pion[i][j].color))&&(i-1>=0)&&(i+1<=8))
                ||((pion[i][j+1].color==2)&&(pion[i][j-1].color==color_eaten(pion,pion[i][j].color))&&(j+1<=8)&&(j-1>=0))
                ||((pion[i+1][j].color==2)&&(pion[i-1][j].color==color_eaten(pion,pion[i][j].color))&&(i+1<=8)&&(i-1>=0))
                ||((pion[i][j-1].color==2)&&(pion[i][j+1].color==color_eaten(pion,pion[i][j].color))&&(j+1<=8)&&(j-1>=0))
                ||((pion[i-1][j-1].color==2)&&(pion[i+1][j+1].color==color_eaten(pion,pion[i][j].color))&&(i-1>=0)&&(j-1>=0)&&(i+1<=4)&&(j+1<=8))
                ||((pion[i-1][j+1].color==2)&&(pion[i+1][j-1].color==color_eaten(pion,pion[i][j].color))&&(i-1>=0)&&(j-1>=0)&&(i+1<=4)&&(j+1<=8))
                ||((pion[i+1][j+1].color==2)&&(pion[i-1][j-1].color==color_eaten(pion,pion[i][j].color))&&(i-1>=0)&&(j-1>=0)&&(i+1<=4)&&(j+1<=8))
                ||((pion[i+1][j-1].color==2)&&(pion[i-1][j+1].color==color_eaten(pion,pion[i][j].color))&&(i-1>=0)&&(j-1>=0)&&(i+1<=4)&&(j+1<=8)))

        {
            return 0 ;
        }

        return 1;
    }


}

void eat (SPion pion[5][9],int aftermvt_ligne,int aftermvt_colone,int beforemvt_ligne,int beforemvt_colone,int* a,int oldL,int oldC,PionSlct PionSelected,SDL_Rect positionaspiration,SDL_Rect positionpercussion,SDL_Surface *aspiration,SDL_Surface *percussion,SDL_Surface *screen)
{


///Gauche a droite
    if ((PionSelected.ligne==oldL)&&(PionSelected.colone==oldC+1)&&(oldC+1<=8))
    {
        if ((pion[oldL][oldC-1].color==color_eaten(pion,pion[PionSelected.ligne][PionSelected.colone].color))
                &&(pion[PionSelected.ligne][PionSelected.colone+1].color==color_eaten(pion,pion[PionSelected.ligne][PionSelected.colone].color))
                &&(oldC-1>=0)
                &&(PionSelected.colone+1<=8) )
        {
            SDL_SetColorKey(aspiration, SDL_SRCCOLORKEY, SDL_MapRGB(aspiration->format, 255,255, 255));
            SDL_BlitSurface(aspiration, NULL, screen, &positionaspiration);
            SDL_SetColorKey(percussion, SDL_SRCCOLORKEY, SDL_MapRGB(percussion->format, 255,255, 255));
            SDL_BlitSurface(percussion, NULL, screen, &positionpercussion);
            SDL_Flip(screen);

            bool done2 = false;
            while (!done2)
            {
                // message processing loop
                SDL_Event event2;
                while (SDL_PollEvent(&event2))
                {

                    switch(event2.type)
                    {
                    // check for messages
                    // exit if the window is closed
                    case SDL_QUIT:
                        done2 = true;
                    case SDL_MOUSEBUTTONDOWN:


                        if ((669<=event2.button.x)&&(event2.button.x<=699+239)&&(667<=event2.button.y)&&(event2.button.y<=667+58))
                        {
                            eat_back (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a);
                            done2=true ;
                            break;
                        }
                        if ((187<=event2.button.x)&&(event2.button.x<=187+251)&&(667<=event2.button.y)&&(event2.button.y<=667+58))
                        {
                            eat_front (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a) ;
                            done2=true ;
                            break ;
                        }

                    }

                }

            }
        }
        else
        {
            eat_front (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a) ;
            eat_back (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a);
        }
    }
    else {}
///droite à gauche
    if ((PionSelected.ligne==oldL)&&(PionSelected.colone==oldC-1)&&(oldC-1>=0))
    {
        if ((pion[oldL][oldC+1].color==color_eaten(pion,pion[PionSelected.ligne][PionSelected.colone].color))
                &&(pion[PionSelected.ligne][PionSelected.colone-1].color==color_eaten(pion,pion[PionSelected.ligne][PionSelected.colone].color))
                &&(oldC+1<=8)
                &&(PionSelected.colone-1>=0) )
        {
            SDL_SetColorKey(aspiration, SDL_SRCCOLORKEY, SDL_MapRGB(aspiration->format, 255,255, 255));
            SDL_BlitSurface(aspiration, NULL, screen, &positionaspiration);
            SDL_SetColorKey(percussion, SDL_SRCCOLORKEY, SDL_MapRGB(percussion->format, 255,255, 255));
            SDL_BlitSurface(percussion, NULL, screen, &positionpercussion);
            SDL_Flip(screen);

            bool done2 = false;
            while (!done2)
            {
                // message processing loop
                SDL_Event event2;
                while (SDL_PollEvent(&event2))
                {

                    switch(event2.type)
                    {
                    // check for messages
                    // exit if the window is closed
                    case SDL_QUIT:
                        done2 = true;
                    // check for keypresses
                    ////////////////////
                    case SDL_MOUSEBUTTONDOWN:


                        if ((669<=event2.button.x)&&(event2.button.x<=699+239)&&(667<=event2.button.y)&&(event2.button.y<=667+58))
                        {
                            eat_back (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a);
                            done2=true ;
                            break;
                        }
                        if ((187<=event2.button.x)&&(event2.button.x<=187+251)&&(667<=event2.button.y)&&(event2.button.y<=667+58))
                        {
                            eat_front (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a) ;
                            done2=true ;
                            break ;
                        }

                    }

                }

            }
        }
        else
        {
            eat_front (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a) ;
            eat_back (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a);
        }
    }
    else {}



///Diagonale à droite "\ de bas a haut"
    if ((PionSelected.ligne==oldL-1)&&(PionSelected.colone==oldC-1)&&(oldL-1>=0)&&(oldC-1>=0))
    {
        if ((pion[oldL+1][oldC+1].color==color_eaten(pion,pion[PionSelected.ligne][PionSelected.colone].color))
                &&(pion[PionSelected.ligne-1][PionSelected.colone-1].color==color_eaten(pion,pion[PionSelected.ligne][PionSelected.colone].color))
                &&(PionSelected.ligne-1>=0)
                &&(PionSelected.colone-1>=0)
                &&(oldL+1<=4)
                &&(oldC+1<=8) )
        {
            SDL_SetColorKey(aspiration, SDL_SRCCOLORKEY, SDL_MapRGB(aspiration->format, 255,255, 255));
            SDL_BlitSurface(aspiration, NULL, screen, &positionaspiration);
            SDL_SetColorKey(percussion, SDL_SRCCOLORKEY, SDL_MapRGB(percussion->format, 255,255, 255));
            SDL_BlitSurface(percussion, NULL, screen, &positionpercussion);
            SDL_Flip(screen);

            bool done2 = false;
            while (!done2)
            {
                // message processing loop
                SDL_Event event2;
                while (SDL_PollEvent(&event2))
                {

                    switch(event2.type)
                    {
                    // check for messages
                    // exit if the window is closed
                    case SDL_QUIT:
                        done2 = true;
                    // check for keypresses
                    ////////////////////
                    case SDL_MOUSEBUTTONDOWN:


                        if ((669<=event2.button.x)&&(event2.button.x<=699+239)&&(667<=event2.button.y)&&(event2.button.y<=667+58))
                        {
                            eat_back (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a);
                            done2=true ;
                            break;
                        }
                        if ((187<=event2.button.x)&&(event2.button.x<=187+251)&&(667<=event2.button.y)&&(event2.button.y<=667+58))
                        {
                            eat_front (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a) ;
                            done2=true ;
                            break ;
                        }

                    }

                }

            }
        }
        else
        {
            eat_front (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a) ;
            eat_back (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a);
        }
    }
    else {}


    ///Diagonale à droite "\ de haut a bas"

    if ((PionSelected.ligne==oldL+1)&&(PionSelected.colone==oldC+1)&&(oldL+1<=8)&&(oldC+1<=8))
    {
        if ((pion[oldL-1][oldC-1].color==color_eaten(pion,pion[PionSelected.ligne][PionSelected.colone].color))
                &&(pion[PionSelected.ligne+1][PionSelected.colone+1].color==color_eaten(pion,pion[PionSelected.ligne][PionSelected.colone].color))
                &&(oldL-1>=0)
                &&(oldC-1>=0)
                &&(PionSelected.ligne+1<=4)
                &&(PionSelected.colone+1<=8) )
        {
            SDL_SetColorKey(aspiration, SDL_SRCCOLORKEY, SDL_MapRGB(aspiration->format, 255,255, 255));
            SDL_BlitSurface(aspiration, NULL, screen, &positionaspiration);
            SDL_SetColorKey(percussion, SDL_SRCCOLORKEY, SDL_MapRGB(percussion->format, 255,255, 255));
            SDL_BlitSurface(percussion, NULL, screen, &positionpercussion);
            SDL_Flip(screen);

            bool done2 = false;
            while (!done2)
            {
                // message processing loop
                SDL_Event event2;
                while (SDL_PollEvent(&event2))
                {

                    switch(event2.type)
                    {
                    // check for messages
                    // exit if the window is closed
                    case SDL_QUIT:
                        done2 = true;
                    // check for keypresses
                    ////////////////////
                    case SDL_MOUSEBUTTONDOWN:


                        if ((669<=event2.button.x)&&(event2.button.x<=699+239)&&(667<=event2.button.y)&&(event2.button.y<=667+58))
                        {
                            eat_back (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a);
                            done2=true ;
                            break;
                        }
                        if ((187<=event2.button.x)&&(event2.button.x<=187+251)&&(667<=event2.button.y)&&(event2.button.y<=667+58))
                        {
                            eat_front (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a) ;
                            done2=true ;
                            break ;
                        }

                    }

                }

            }
        }
        else
        {
            eat_front (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a) ;
            eat_back (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a);
        }
    }
    else {}

    ///Diagonale à gauche "/ de bas a haut"
    if ((PionSelected.ligne==oldL-1)&&(PionSelected.colone==oldC+1)&&(oldL-1>=0)&&(oldC+1<=8))
    {
        if ((pion[oldL+1][oldC-1].color==color_eaten(pion,pion[PionSelected.ligne][PionSelected.colone].color))
                &&(pion[PionSelected.ligne-1][PionSelected.colone+1].color==color_eaten(pion,pion[PionSelected.ligne][PionSelected.colone].color))
                &&(oldL+1<=4)
                &&(oldC-1>=0)
                &&(PionSelected.ligne-1>=0)
                &&(PionSelected.colone+1<=8) )
        {
            SDL_SetColorKey(aspiration, SDL_SRCCOLORKEY, SDL_MapRGB(aspiration->format, 255,255, 255));
            SDL_BlitSurface(aspiration, NULL, screen, &positionaspiration);
            SDL_SetColorKey(percussion, SDL_SRCCOLORKEY, SDL_MapRGB(percussion->format, 255,255, 255));
            SDL_BlitSurface(percussion, NULL, screen, &positionpercussion);
            SDL_Flip(screen);

            bool done2 = false;
            while (!done2)
            {
                // message processing loop
                SDL_Event event2;
                while (SDL_PollEvent(&event2))
                {

                    switch(event2.type)
                    {
                    // check for messages
                    // exit if the window is closed
                    case SDL_QUIT:
                        done2 = true;
                    // check for keypresses
                    ////////////////////
                    case SDL_MOUSEBUTTONDOWN:


                        if ((669<=event2.button.x)&&(event2.button.x<=699+239)&&(667<=event2.button.y)&&(event2.button.y<=667+58))
                        {
                            eat_back (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a);
                            done2=true ;
                            break;
                        }
                        if ((187<=event2.button.x)&&(event2.button.x<=187+251)&&(667<=event2.button.y)&&(event2.button.y<=667+58))
                        {
                            eat_front (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a) ;
                            done2=true ;
                            break ;
                        }

                    }

                }

            }
        }
        else
        {
            eat_front (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a) ;
            eat_back (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a);
        }
    }
    else {}

    ///Diagonale à gauche "/ de haut a bas"
    if ((PionSelected.ligne==oldL+1)&&(PionSelected.colone==oldC-1)&&(oldL+1<=8)&&(oldC-1>=0))
    {
        if ((pion[oldL-1][oldC+1].color==color_eaten(pion,pion[PionSelected.ligne][PionSelected.colone].color))
                &&(pion[PionSelected.ligne+1][PionSelected.colone-1].color==color_eaten(pion,pion[PionSelected.ligne][PionSelected.colone].color))
                &&(oldL-1>=0)
                &&(oldC+1<=8)
                &&(PionSelected.ligne+1<=4)
                &&(PionSelected.colone-1>=0) )
        {
            SDL_SetColorKey(aspiration, SDL_SRCCOLORKEY, SDL_MapRGB(aspiration->format, 255,255, 255));
            SDL_BlitSurface(aspiration, NULL, screen, &positionaspiration);
            SDL_SetColorKey(percussion, SDL_SRCCOLORKEY, SDL_MapRGB(percussion->format, 255,255, 255));
            SDL_BlitSurface(percussion, NULL, screen, &positionpercussion);
            SDL_Flip(screen);

            bool done2 = false;
            while (!done2)
            {
                // message processing loop
                SDL_Event event2;
                while (SDL_PollEvent(&event2))
                {

                    switch(event2.type)
                    {
                    // check for messages
                    // exit if the window is closed
                    case SDL_QUIT:
                        done2 = true;
                    // check for keypresses

                    case SDL_MOUSEBUTTONDOWN:


                        if ((669<=event2.button.x)&&(event2.button.x<=699+239)&&(667<=event2.button.y)&&(event2.button.y<=667+58))
                        {
                            eat_back (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a);
                            done2=true ;
                            break;
                        }
                        if ((187<=event2.button.x)&&(event2.button.x<=187+251)&&(667<=event2.button.y)&&(event2.button.y<=667+58))
                        {
                            eat_front (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a) ;
                            done2=true ;
                            break ;
                        }

                    }

                }

            }
        }
        else
        {
            eat_front (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a) ;
            eat_back (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a);
        }
    }
    else {}
    ///De bas a haut
    if ((PionSelected.ligne==oldL-1)&&(PionSelected.colone==oldC)&&(oldL-1>=0))
    {
        if ((pion[oldL+1][oldC].color==color_eaten(pion,pion[PionSelected.ligne][PionSelected.colone].color))
                &&(pion[PionSelected.ligne-1][PionSelected.colone].color==color_eaten(pion,pion[PionSelected.ligne][PionSelected.colone].color))
                &&(oldL+1<=4)
                &&(PionSelected.ligne-1>=0) )
        {
            SDL_SetColorKey(aspiration, SDL_SRCCOLORKEY, SDL_MapRGB(aspiration->format, 255,255, 255));
            SDL_BlitSurface(aspiration, NULL, screen, &positionaspiration);
            SDL_SetColorKey(percussion, SDL_SRCCOLORKEY, SDL_MapRGB(percussion->format, 255,255, 255));
            SDL_BlitSurface(percussion, NULL, screen, &positionpercussion);
            SDL_Flip(screen);

            bool done2 = false;
            while (!done2)
            {
                // message processing loop
                SDL_Event event2;
                while (SDL_PollEvent(&event2))
                {

                    switch(event2.type)
                    {
                    // check for messages
                    // exit if the window is closed
                    case SDL_QUIT:
                        done2 = true;
                    // check for keypresses

                    case SDL_MOUSEBUTTONDOWN:


                        if ((669<=event2.button.x)&&(event2.button.x<=699+239)&&(667<=event2.button.y)&&(event2.button.y<=667+58))
                        {
                            eat_back (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a);
                            done2=true ;
                            break;
                        }
                        if ((187<=event2.button.x)&&(event2.button.x<=187+251)&&(667<=event2.button.y)&&(event2.button.y<=667+58))
                        {
                            eat_front (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a) ;
                            done2=true ;
                            break ;
                        }

                    }

                }

            }
        }
        else
        {
            eat_front (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a) ;
            eat_back (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a);
        }
    }
    else {}
    ///De haut a bas
    if ((PionSelected.ligne==oldL+1)&&(PionSelected.colone==oldC)&&(oldL+1<=4))
    {
        if ((pion[oldL-1][oldC].color==color_eaten(pion,pion[PionSelected.ligne][PionSelected.colone].color))
                &&(pion[PionSelected.ligne+1][PionSelected.colone].color==color_eaten(pion,pion[PionSelected.ligne][PionSelected.colone].color))
                &&(oldL-1>=0)
                &&(PionSelected.ligne+1<=4) )
        {
            SDL_SetColorKey(aspiration, SDL_SRCCOLORKEY, SDL_MapRGB(aspiration->format, 255,255, 255));
            SDL_BlitSurface(aspiration, NULL, screen, &positionaspiration);
            SDL_SetColorKey(percussion, SDL_SRCCOLORKEY, SDL_MapRGB(percussion->format, 255,255, 255));
            SDL_BlitSurface(percussion, NULL, screen, &positionpercussion);
            SDL_Flip(screen);

            bool done2 = false;
            while (!done2)
            {
                // message processing loop
                SDL_Event event2;
                while (SDL_PollEvent(&event2))
                {

                    switch(event2.type)
                    {
                    // check for messages
                    // exit if the window is closed
                    case SDL_QUIT:
                        done2 = true;

                    case SDL_MOUSEBUTTONDOWN:


                        if ((669<=event2.button.x)&&(event2.button.x<=699+239)&&(667<=event2.button.y)&&(event2.button.y<=667+58))
                        {
                            eat_back (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a);
                            done2=true ;
                            break;
                        }
                        if ((187<=event2.button.x)&&(event2.button.x<=187+251)&&(667<=event2.button.y)&&(event2.button.y<=667+58))
                        {
                            eat_front (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a) ;
                            done2=true ;
                            break ;
                        }

                    }

                }

            }
        }
        else
        {
            eat_front (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a) ;
            eat_back (pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,a);
        }
    }


}





int main ( int argc, char** argv )
{



    //variable initialization

    SDL_Rect positionFond0,positionFond,positionNextRole,positionaspiration,positionpercussion;
    struct SPion pion[5][9] ;
    struct PionSlct PionSelected ;

    PionSelected.ligne=2 ;
    PionSelected.colone=4 ;
    positionFond.x = 0;
    positionFond.y = 0;
    positionNextRole.x = 366 ;
    positionNextRole.y = 0 ;
    positionaspiration.x= 669 ;
    positionaspiration.y= 667 ;
    positionpercussion.x= 120 ;
    positionpercussion.y= 667 ;






//init positions

    int i ;
    int j ;
    int decx = 0 ;
    int decy = 0 ;

    for (i=0; i<=4; i++)
    {
        for (j=0; j<=8; j++)
        {
            pion[i][j].position.x = 100 + decx - 80/2;
            pion[i][j].position.y = 150 + decy - 76/2;
            decx = decx + 115 ;
        }
        decy = decy + 120 ;
        decx = 0 ;


    }

    for (i=0; i<=2; i++)
    {
        for (j=0; j<=8; j++)
        {
            pion[i][j].color=0 ;
        }
    }

    pion[2][1].color=1 ;
    pion[2][3].color=1 ;
    pion[2][4].color=2 ;
    pion[2][6].color=1 ;
    pion[2][8].color=1 ;

    for (i=3; i<=4; i++)
    {
        for (j=0; j<=8; j++)
        {
            pion[i][j].color=1 ;
        }
    }

    SDL_Surface* screen = SDL_SetVideoMode(1300,900, 24,SDL_HWSURFACE|SDL_DOUBLEBUF);

    const char *imageDeFond_path = "background.bmp";
    SDL_Surface* imageDeFond = SDL_LoadBMP(imageDeFond_path);

    const char *PionBlanc_path = "jaune.bmp";
    SDL_Surface *PionBlanc = SDL_LoadBMP(PionBlanc_path);

    const char *PionNoir_path = "Noir.bmp";
    SDL_Surface *PionNoir = SDL_LoadBMP(PionNoir_path);

    const char *PionSelectedNoir_path = "NoirSelected.bmp";
    SDL_Surface *PionSelectedNoir = SDL_LoadBMP(PionSelectedNoir_path);


    const char *PionSelectedBlanc_path = "BlancSelected.bmp";
    SDL_Surface *PionSelectedBlanc = SDL_LoadBMP(PionSelectedBlanc_path);







    SDL_Surface *NextRole = SDL_LoadBMP("NextPlayer(1).bmp");
    SDL_Surface *aspiration = SDL_LoadBMP("aspiration.bmp");
    SDL_Surface *percussion = SDL_LoadBMP("percussion.bmp");
    //SDL surfaces for first window
    SDL_Surface *VanGogh = SDL_LoadBMP("vangogh.bmp");
    SDL_Surface *Welcome = SDL_LoadBMP("welcome_title.bmp");
    SDL_Surface *Presented = SDL_LoadBMP("presented.bmp");




    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);
    // create a new window
    SDL_WM_SetCaption("Fanorona Game", NULL);
    if ( !screen )
    {
        printf("Unable to set 1100x700 video: %s\n", SDL_GetError());
        return 1;
    }

    // load an image
    if (!imageDeFond)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return 1;
    }
    SDL_BlitSurface(VanGogh, NULL, screen, &positionFond);
    show_window(screen,VanGogh,positionFond);
    clock_t start_t = clock();
    int waiting = 0;
    //while loop
    while(clock()-start_t<4000)
    {
        waiting++;
    }

    SDL_FreeSurface(VanGogh);
    SDL_BlitSurface(imageDeFond, NULL, screen, &positionFond);
    show_EV(pion,PionNoir,PionBlanc,screen,PionSelectedNoir,PionSelectedBlanc);


    int v=0;
    int l=0 ;
    int c=0;
    int lastcolor=10;
    int oldcolor=11;
    int go=0;


    bool done = false;
    while (!done) // program main loop
    {

        SDL_Event event;
        while (SDL_PollEvent(&event)) // message processing loop
        {

            switch(event.type)  // check for messages
            {


            case SDL_QUIT:   // exit if the window is closed
                done = true;




            case SDL_MOUSEBUTTONDOWN:



                while (v==0)
                {
                    oldcolor=lastcolor;
                    v=SelectedPion(pion,&PionSelected.ligne,&PionSelected.colone,event,PionNoir,PionBlanc,screen,PionSelectedNoir,PionSelectedBlanc,&lastcolor) ;

                    if (oldcolor==lastcolor)
                    {
                        UnSelectedPion(pion,PionSelected.ligne,PionSelected.colone,PionNoir,PionBlanc,screen,PionSelectedNoir,PionSelectedBlanc) ;
                        v=0;

                    }



                    SDL_BlitSurface(imageDeFond, NULL, screen, &positionFond);
                    show_EV(pion,PionNoir,PionBlanc,screen,PionSelectedNoir,PionSelectedBlanc);
                    SDL_Flip(screen);
                    break ;
                }


                if(verify_new_position(pion,&l,&c,PionSelected.ligne,PionSelected.colone,event)==0)
                {
                    int oldL=PionSelected.ligne,oldC=PionSelected.colone,a=0;
                    deplacer(pion,&PionSelected.ligne,&PionSelected.colone,l,c,PionNoir,PionBlanc,screen,PionSelectedNoir,PionSelectedBlanc) ;
                    SDL_BlitSurface(imageDeFond, NULL, screen, &positionFond);
                    show_EV(pion,PionNoir,PionBlanc,screen,PionSelectedNoir,PionSelectedBlanc);
                    eat(pion,PionSelected.ligne,PionSelected.colone,oldL,oldC,&a,oldL,oldC,PionSelected,positionaspiration,positionpercussion,aspiration,percussion,screen) ;

                    SDL_BlitSurface(imageDeFond, NULL, screen, &positionFond);
                    show_EV(pion,PionNoir,PionBlanc,screen,PionSelectedNoir,PionSelectedBlanc);





                    if ((eat_no_more(pion,PionSelected.ligne,PionSelected.colone)==1)||(a==0))
                    {
                        UnSelectedPion(pion,PionSelected.ligne,PionSelected.colone,PionNoir,PionBlanc,screen,PionSelectedNoir,PionSelectedBlanc) ;
                        SDL_BlitSurface(imageDeFond, NULL, screen, &positionFond);
                        show_EV(pion,PionNoir,PionBlanc,screen,PionSelectedNoir,PionSelectedBlanc);

                        SDL_SetColorKey(NextRole, SDL_SRCCOLORKEY, SDL_MapRGB(NextRole->format, 0,0, 0));
                        SDL_BlitSurface(NextRole, NULL, screen, &positionNextRole);

                        SDL_Flip(screen);
                        v=0;

                    }



                }








            }

            break;

        }

    }


    SDL_FreeSurface(imageDeFond);
    SDL_FreeSurface(PionBlanc);
    SDL_FreeSurface(PionNoir);
    SDL_FreeSurface(PionSelectedNoir);
    SDL_FreeSurface(PionSelectedBlanc);
    SDL_FreeSurface(NextRole);
    SDL_FreeSurface(aspiration);
    SDL_FreeSurface(percussion);


    printf("Exited cleanly\n");
    return 0;

}


