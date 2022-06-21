#include "graphics.h"
#include "police.h"

#define EN_LOCAL

#ifdef SDL_TTF_OK
	#include <SDL_ttf.h>
	#include <SDL/SDL_ttf.h>
	#define POLICE_NAME "verdana.ttf"
	TTF_Font *police[256];
	int verdana_ok = 0;
#endif

int WIDTH;
int HEIGHT;

SDL_Surface * SDL_screen;
int __init_graphics_is_already_called = 0;
int SDL_AFFICHE_AUTO = 1;
#define MAX_WIDTH  1920
#define MAX_HEIGHT 1080

void init_graphics(int W, int H) {
    if ((W>10) && (W<MAX_WIDTH )) 
        WIDTH  = W; 
    else WIDTH  = 600;
	if ((H>10) && (H<MAX_HEIGHT)) 
        HEIGHT = H; 
    else HEIGHT = 400;
	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
	if ( SDL_screen == NULL ) {
		fprintf(stderr, "Impossible de passer en %dx%d en 32 bits: %s\n", WIDTH, HEIGHT, SDL_GetError());
		exit(1);
    }
	
	SDL_EnableKeyRepeat(1,0);
	
	SDL_WM_SetCaption("Puissance 4!!",NULL);
	
	__init_graphics_is_already_called = 25;
	printf("Fenetre de %d x %d\n",WIDTH,HEIGHT);
	#ifdef SDL_TTF_OK
		printf("SDL_ttf OK, ");
        
		TTF_Init();
        	police[10] = TTF_OpenFont(POLICE_NAME, 10);
		if (police[10])  {
            verdana_ok=1; printf("police %s OK : affichage graphique OK.\n",POLICE_NAME);
        }
        else {
            verdana_ok = 0; printf("police %s absente : affichage dans la console.\n",POLICE_NAME);
        }
	#else
		printf("SDL_ttf absent : affichage dans la console.\n");
	#endif
	
	fill_screen(noir);
	affiche_auto_on();
	affiche_all();

}

void affiche_auto_on () {
    SDL_AFFICHE_AUTO = 1;
}

void affiche_auto_off() {
    SDL_AFFICHE_AUTO = 0;
}

void affiche_all() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) 
        if (event.type == SDL_QUIT) 
            exit(0);
	if (__init_graphics_is_already_called == 25) 
        SDL_Flip(SDL_screen);
    else {
        init_graphics(380,80);
        write_text("init_graphics() n'a pas �t� appel�e.");
        write_text("");
        write_text("           Cliquer pour terminer.");
        fprintf(stderr,"init_graphics() n'a pas �t� appel�e.\n");
        fprintf(stderr,"Cliquer pour terminer.\n");
        wait_clic();
        exit(1);
    }
}

void synchro() { affiche_all(); }

COULEUR couleur_RGB(int r, int g, int b) {
	COULEUR C;
	return ((r%256)<<16) + ((g%256)<<8) + (b%256);
	return C;
}

point get_mouse() {
	point dep;
	dep.x = dep.y = -1;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) 
            exit(0);
	
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE : exit(0);
                default :	break;
            }
        }
		if (event.type == SDL_MOUSEMOTION)
        {
			dep.x = event.motion.x;
			dep.y = event.motion.y;
        }
    }
	return dep;
}

void wait_escape() {
	int display = 1;
	SDL_Event event;
	point p;
	p.x = WIDTH/2 - 170;
	p.y = 25;
	aff_pol("Appuyer sur Echap pour terminer",20,p,gris);
	affiche_all();
	while (SDL_WaitEvent(&event) && display) {
		if (event.type == SDL_QUIT) exit(0);
	
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
                case SDLK_ESCAPE : display=0;	break;
                default :	break;
            }
        }
    }
	#ifdef SDL_TTF_OK
		int i;
		if (verdana_ok) for (i=0;i<256;i++) if (police[i]) TTF_CloseFont(police[i]);
		TTF_Quit();
	#endif
	SDL_Quit();
}

point wait_clic() {
	int encore = 1;
	point P;
	SDL_Event event;
	P.x = 0;
	P.y = 0;
#ifdef EN_LOCAL
	#ifdef SDL_TTF_OK
		point E,F;
		char S[16];
		E.x = WIDTH - 55; E.y = 15;
		F.x = WIDTH; F.y = 0;
	#endif
#endif
	while (SDL_WaitEvent(&event) && encore) {
		if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT)) {
			encore=0;
			P.x = event.button.x;
			P.y = HEIGHT-event.button.y;
        }
		if (event.type == SDL_MOUSEMOTION) {
#ifdef EN_LOCAL
			#ifdef SDL_TTF_OK
				if (police[10]) {
					draw_fill_rectangle(E,F,noir);
					sprintf(S,"%4d %4d",event.motion.x,HEIGHT - event.motion.y);
					aff_pol(S,10,E,gris);
					affiche_all();
                }
			#endif
#endif
			printf("%cEn attente de clic ... %4d %4d           %c",13,event.motion.x,HEIGHT - event.motion.y,13);
			fflush(stdout);
        }
		if (event.type == SDL_QUIT) exit(0);
	
    }
#ifdef EN_LOCAL
	#ifdef SDL_TTF_OK
		aff_pol(S,10,E,noir);
		//draw_fill_rectangle(E,F,jaune);
		affiche_all();
	#endif
#endif
	printf("%cClic en %4d %4d                                           \n",13,P.x,P.y);
	return P;
}

void fill_screen(COULEUR color) {
	int i,j;
	for (i=0;i<WIDTH;i++)
		for (j=0;j<HEIGHT;j++) 
            *((COULEUR *)SDL_screen->pixels + (HEIGHT-j-1) * WIDTH + i) = color;
	if (SDL_AFFICHE_AUTO) 
        affiche_all();
}

int dans_ecran(int x, int y) {
	if (x<0) return 0;
	if (x>=WIDTH) return 0;
	if (y<0) return 0;
	if (y>=HEIGHT) return 0;
	return 1;
}

#define add_pix(x,y,color)  if (dans_ecran((x),(y))) *((COULEUR *)SDL_screen->pixels + (HEIGHT-(y)-1) * WIDTH + (x)) = (color)

void draw_pixel(point p, COULEUR color) {
	add_pix(p.x,p.y,color);
	if (SDL_AFFICHE_AUTO) affiche_all();
}

void draw_line(point p1, point p2, COULEUR color) {
	int xmin, xmax;
	int ymin, ymax;
	int i,j;
	float a,b,ii,jj;
	
	if (p1.x < p2.x) {xmin=p1.x; xmax=p2.x;} else{xmin=p2.x; xmax=p1.x;}
	if (p1.y < p2.y) {ymin=p1.y; ymax=p2.y;} else{ymin=p2.y; ymax=p1.y;}
	
	if (xmin==xmax) for (j=ymin;j<=ymax;j++) add_pix(xmin,j,color);
	if (ymin==ymax) for (i=xmin;i<=xmax;i++) add_pix(i,ymin,color);
	
	
	// La variation la plus grande est en x
	if ((xmax-xmin >= ymax-ymin) && (ymax-ymin>0)) {
		a = (float)(p1.y-p2.y) / ((float)(p1.x-p2.x));
		b = p1.y - a*p1.x;
		for (i=xmin;i<=xmax;i++) {
			jj = a*i+b;
			j = jj;
			if (((jj-j) > 0.5) && (j < HEIGHT-1)) j++;
			add_pix(i,j,color);
        }
    }
	
	// La variation la plus grande est en y
	if ((ymax-ymin > xmax-xmin) && (xmax-xmin>0)) {
		a = (float)(p1.y-p2.y) / ((float)(p1.x-p2.x));
		b = p1.y - a*p1.x;
		for (j=ymin;j<=ymax;j++) {
			ii = (j-b)/a;
			i = ii;
			if (((ii-i) > 0.5) && (i < WIDTH-1)) i++;
			add_pix(i,j,color);
        }
    }
	if (SDL_AFFICHE_AUTO) affiche_all();
}

void draw_rectangle(point p1, point p2, COULEUR color) {
	int xmin, xmax;
	int ymin, ymax;
	int i,j;
	 
	if (p1.x < p2.x) {xmin=p1.x; xmax=p2.x;} else{xmin=p2.x; xmax=p1.x;}
	if (p1.y < p2.y) {ymin=p1.y; ymax=p2.y;} else{ymin=p2.y; ymax=p1.y;}
	
	for (i=xmin;i<=xmax;i++) add_pix(i,ymin,color);
	for (i=xmin;i<=xmax;i++) add_pix(i,ymax,color);
	
	for (j=ymin;j<=ymax;j++) add_pix(xmin,j,color);
	for (j=ymin;j<=ymax;j++) add_pix(xmax,j,color);
	if (SDL_AFFICHE_AUTO) affiche_all();
}

void draw_fill_rectangle(point p1, point p2, COULEUR color) {
	int xmin, xmax;
	int ymin, ymax;
	int i,j;
	
	if (p1.x < p2.x) {xmin=p1.x; xmax=p2.x;} else{xmin=p2.x; xmax=p1.x;}
	if (p1.y < p2.y) {ymin=p1.y; ymax=p2.y;} else{ymin=p2.y; ymax=p1.y;}
	
	for (i=xmin;i<=xmax;i++) for (j=ymin;j<=ymax;j++) add_pix(i,j,color);
	if (SDL_AFFICHE_AUTO) affiche_all();
}

void draw_circle(point centre, int rayon, COULEUR color) {
	point min, max;
	int i,j;
	float dx, dy, rr;
	
	min.x = centre.x - rayon;  max.x = centre.x + rayon;
	min.y = centre.y - rayon;  max.y = centre.y + rayon;
	rr = rayon*rayon;
	
	for (i=min.x;i<=max.x;i++) {
		dx = i - centre.x;
		dy = sqrt(rr - dx*dx);
		j = centre.y + dy;
		add_pix(i,j,color);
		j = centre.y - dy;
		add_pix(i,j,color);
    }
	for (j=min.y;j<=max.y;j++) {
		dy = j - centre.y;
		dx = sqrt(rr - dy*dy);
		i = centre.x + dx;
		add_pix(i,j,color);
		i = centre.x - dx;
		add_pix(i,j,color);
    }
	if (SDL_AFFICHE_AUTO) affiche_all();
}

void draw_fill_circle(point centre, int rayon, COULEUR color) {
	point min, max;
	int i,j;
	float dx, dy, rr;
	
	min.x = centre.x - rayon; max.x = centre.x + rayon;
	min.y = centre.y - rayon; max.y = centre.y + rayon;
	
	rr = rayon*rayon;
	
	for (i=min.x;i<=max.x;i++) {
		dx = i - centre.x;
		for (j=min.y;j<=max.y;j++) {
			dy = j - centre.y;
			if (dx*dx + dy*dy <= rr) add_pix(i,j,color);
        }
    }
	if (SDL_AFFICHE_AUTO) affiche_all();
}

void draw_square(point p, int taille, COULEUR color) {
	point p1 = {p.x-taille/2, p.y-taille/2}, p2 = {p.x+taille/2, p.y+taille/2};
	draw_rectangle(p1, p2, color);
}

void draw_fill_square(point p, int taille, COULEUR color) {
	point p1 = {p.x-taille/2, p.y-taille/2}, p2 = {p.x+taille/2, p.y+taille/2};
	draw_fill_rectangle(p1, p2, color);
}

void aff_pol(char *a_ecrire, int taille, point p, COULEUR C) {
	#ifdef SDL_TTF_OK
	    int i;
	    SDL_Color color;
	    SDL_Surface *texte = NULL;
	    SDL_Rect position;
	    static int premiere_fois = 1;
	    static TTF_Font *police[256];
	    TTF_Font *pol;

	    if (premiere_fois)  {
            TTF_Init(); for (i=0;i<256;i++) police[i] = NULL; premiere_fois = 0;
        }
	    if (taille>=256) pol = TTF_OpenFont(POLICE_NAME, taille);
		    else {
			    if (police[taille]==NULL) police[taille] = TTF_OpenFont(POLICE_NAME, taille);
		            pol = police[taille];
            }
	    SDL_GetRGB(C,SDL_screen->format,&(color.r),&(color.g),&(color.b));

	    if (pol) texte = TTF_RenderText_Blended(pol, a_ecrire, color); else texte = NULL;
	    if (texte) {
            position.x = p.x;
            position.y = HEIGHT - p.y;
            SDL_BlitSurface(texte, NULL, SDL_screen, &position);
            if (SDL_AFFICHE_AUTO) 
                affiche_all();
			SDL_FreeSurface(texte);
        }
        else printf("%s\n",a_ecrire);
/*	
	    if (SDL_AFFICHE_AUTO) affiche_all();
	    if (police) TTF_CloseFont(police);
	    TTF_Quit();
	    if (texte) SDL_FreeSurface(texte);
*/
	#else 
		taille = 0; p.x = p.y = 0; C = 0;
		printf("%s\n",a_ecrire);
	#endif
}



void aff_int(int n,  int taille, point p, COULEUR C) {
	char s[32];
	sprintf(s,"%d",n);
	aff_pol(s,taille,p,C);
}

void attendre(int millisecondes) { SDL_Delay(millisecondes); }

float alea_float() {
	static int init_alea = 1;
	if (init_alea) srand(time(NULL));
	init_alea = 0;
	return (float)rand() / (float)RAND_MAX;
}

int alea_int(int N) { return (int)(N*alea_float()); }

void write_text(char *a_ecrire) {
	#ifdef SDL_TTF_OK
	    static char s[256];
	    static int fin = 0;
	    static int premier = 1;
	    static point position;
	    
	    if (premier) {
            position.x = 10;
            position.y = HEIGHT; 
            premier = 0;
        }

	if (verdana_ok)
    {
//		printf("verd\n");
	    if (a_ecrire) {
		    if (fin+strlen(a_ecrire) > 256) {
                fprintf(stderr,"Chaine de caract�re trop longue\n");
                return;
            }
            strcat(s+fin,a_ecrire);
//		printf("a_ecr : #%s#\n",s);
            aff_pol(s,20,position,blanc);
		    fin += strlen(a_ecrire);
		    s[fin] = '\0';
        }
        else {
		    position.y -= 20;
		    fin = 0;
		    s[fin] = '\0';
        }
    }
    else {
        if (a_ecrire) {
            printf("%s",a_ecrire);
            fflush(stdout);
        } 
        else printf("\n");
    }
	#else
	    if (a_ecrire) {printf("%s",a_ecrire); fflush(stdout);}
		    else  printf("\n");
	#endif
}