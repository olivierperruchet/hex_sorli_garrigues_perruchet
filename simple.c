

//https://github.com/suzimaru/hex_sorli_garrigues_perruchet/tree/master
  /*gcc -o essai simple.c  `sdl-config --cflags --libs` -lSDL_image -lSDL_ttf*/


//http://www.dafont.com/fr/ site pour différentes polices.
//http://www.corecoding.com/utilities/rgb-or-hex-to-float.php site pour convertir les couleurs hexa->RGB
//http://www.proftnj.com/RGB3.htm site pour les couleurs (hexa+RGB)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
 
#include <SDL/SDL.h>
#include <SDL/SDL_keysym.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
 
#define WINHI 600 // window height
#define WINWI 800 // window width

typedef struct
{
	int h, w;
}	Dimensions;
 
int main(int argc, char *argv[])
{


//////////////////////////// DECLARATION //////////////////////////////////////////


    Uint32 initflags = SDL_INIT_VIDEO; //| SDL_DOUBLEBUF;  /* See documentation for details */
    SDL_Surface *ecran, *texte1, *texte_menu_demarrer, *texte_auteur, *jouer, *charger, *quitter, *image_fond; // quelques surfaces
    Dimensions fenetre; // main window

    fenetre.h = WINHI;  // en pixels
    fenetre.w = WINWI;   

    Uint8  video_bpp = 32; // 32 bits de couleur
    Uint32 videoflags = SDL_HWSURFACE; // utiliser la mémoire vidéo
    Uint32 vert, rouge; // des variables pour des couleurs

    bool continuer; // pour la boucle principale des évènements
    SDL_Event event; // aussi
 
 
 
 
    /* Initialize the SDL library */
    if ( SDL_Init(initflags) < 0 )
    {
        fprintf(stderr, "N'arrive pas à initialiser la SDL : %s\n", SDL_GetError());
        exit(1);
    }
 
    /* Set video mode */
    ecran = SDL_SetVideoMode(fenetre.w, fenetre.h, video_bpp, videoflags); // surface principale

    if (ecran == NULL)
    {
        fprintf(stderr, "N'arrive pas a` etablir mode video%dx%dx%d : %s\n", fenetre.w, fenetre.h, video_bpp, SDL_GetError());
        SDL_Quit();
        exit(2);
    }



////////////////////////////// AFFICHAGE DE L'ECRAN PRINCIPAL /////////////////////////////////
		SDL_Rect position_fond;
		
		position_fond.x=0;
		position_fond.y=0;

    image_fond=IMG_Load("Images/image_fond.png");// couleur du fond de l'écran
    SDL_BlitSurface(image_fond,NULL,ecran,&position_fond);

    SDL_WM_SetCaption("Jeu de Hex", NULL); // titre de la fenêtre

    TTF_Init();
    
   
    TTF_Font *fontMenu = TTF_OpenFont("hacked/hacked.ttf",40);// police du menu
    SDL_Color fontPurple = {0,51,102};// couleur du menu
    texte1 = TTF_RenderText_Blended(fontMenu,"Jeu HEX",fontPurple);// texte du petit rectangle

		// position du texte
		SDL_Rect posTexte1;
    posTexte1.x = 125;
    posTexte1.y = 100;

		// collage des nouvelles surfaces.
    SDL_BlitSurface(texte1,NULL,ecran,&posTexte1); // celle la après pour qu'elle ne soit pas écrasée

		TTF_SetFontStyle(fontMenu,TTF_STYLE_BOLD);
		texte_menu_demarrer = TTF_RenderText_Blended(fontMenu,"MENU",fontPurple);
		TTF_SetFontStyle(fontMenu,TTF_STYLE_NORMAL);

		SDL_Rect posTexte_menu_demarrer;
		posTexte_menu_demarrer.x=475;		
		posTexte_menu_demarrer.y=115;
		
		SDL_BlitSurface(texte_menu_demarrer,NULL,ecran,&posTexte_menu_demarrer);
		
	
//Création du bandeau des auteurs
 		TTF_Font *fontAuteur = TTF_OpenFont("hacked/hacked.ttf",22);// police du menu

		texte_auteur = TTF_RenderText_Blended(fontAuteur,"Garrigues, Perruchet, Sorli 2016",fontPurple);
		
		SDL_Rect posTexte_auteur;
		posTexte_auteur.x=400;
		posTexte_auteur.y=540;
		SDL_BlitSurface(texte_auteur,NULL,ecran,&posTexte_auteur);

//Création du menu, choix
		jouer = TTF_RenderText_Blended(fontMenu,"Jouer",fontPurple);
		charger = TTF_RenderText_Blended(fontMenu,"Charger",fontPurple);
		quitter = TTF_RenderText_Blended(fontMenu,"Quitter",fontPurple);
		
		SDL_Rect posJouer, posCharger, posQuitter;
		posJouer.x=435;
		posJouer.y=195;
		posCharger.x=435;
		posCharger.y=275;
		posQuitter.x=435;
		posQuitter.y=355;

	SDL_BlitSurface(jouer,NULL,ecran,&posJouer);
	SDL_BlitSurface(charger,NULL,ecran,&posCharger);
	SDL_BlitSurface(quitter,NULL,ecran,&posQuitter);


//////////////////////////////////////// RECUPERATION DES COORDONNES DES CLICS //////////////////////////////////







///////////////////////////////////////                     //////////////////////////////////

 
   /* // affichage du pion bleu
    SDL_Surface *pionBleu;
    pionBleu = IMG_Load("Images/button-blue22.png");
    SDL_Rect posPionBleu;               
    posPionBleu.x = 377;
    posPionBleu.y = 149;
    SDL_BlitSurface(pionBleu,NULL,ecran,&posPionBleu);*/

   /* // Affichege du pion rouge
    SDL_Surface *pionRouge = IMG_Load("Images/button-red22.png");
    SDL_Rect posPionRouge;               
    posPionRouge.x = 543;
    posPionRouge.y = 273;
    SDL_BlitSurface(pionRouge,NULL,ecran,&posPionRouge);*/

    SDL_Flip(ecran); //maj des surfaces
 
 // boucle des évènements
    continuer = true; // un furieux du c ferait plutôt une boucle infinie. Je préfère rester correct.
    SDLKey key_pressed ;
    while (continuer)
    {
        while ( SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_MOUSEMOTION:
                    printf("Ça bouge\n"); // sans intérêt, c'est juste pour montrer
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {   
                        int clicX = event.motion.x;
                        int clicY = event.motion.y;
                        printf("X=%d Y=%d\n",clicX,clicY); // on récupère les coordonnées du clic
                    }
                    break;
                case SDL_KEYDOWN:
                    key_pressed = event.key.keysym.sym; // on récupère la touche
                    switch (key_pressed)
                    {
                    case SDLK_ESCAPE: /* Esc keypress quits the app... */
                        continuer = false;
                        break;
                    case SDLK_LEFT:
                        printf("left +1\n"); // par exemple
                        break;
                    case SDLK_RIGHT:
                        printf("right +1\n"); 
                        break;
                    case SDLK_UP:
                        printf("up +1\n");
                        break;
                    case SDLK_DOWN:
                        printf("down +1\n");
                        break;
                    }
                    break;
                case SDL_QUIT:
                    continuer = false;
                    break;
                default:
                    break;
            }
        }
        // refresh screen
        // mettre ici tous les blit utiles s'il y a des changements dans les surfaces, board, nouveaux pions
        SDL_Flip(ecran); //maj des surfaces pour affichage
    }
    //

    /* Clean up the SDL library */
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(texte1);
    SDL_FreeSurface(texte_menu_demarrer);
    SDL_FreeSurface(texte_auteur);
    SDL_FreeSurface(jouer);
    SDL_FreeSurface(charger);
    SDL_FreeSurface(quitter);
    TTF_CloseFont(fontMenu);
    TTF_CloseFont(fontAuteur);

    TTF_Quit();
    SDL_Quit();
    return(0);
}
