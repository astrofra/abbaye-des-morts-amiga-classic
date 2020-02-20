/* gameover.c */

#include <stdio.h>
#include <stdlib.h>

#include "includes.prl"
#include "structs.h"
#include "aga_sdl.h"

void gameover (SDL_Window *screen,uint *state) {

	SDL_Renderer *renderer = NULL;
	SDL_Texture *gameover = NULL;
	Mix_Music *bso = NULL;

	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
	SDL_RenderSetLogicalSize(renderer, 256, 192);
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	
	gameover = IMG_LoadTexture(renderer,"/usr/share/abbayev2/graphics/gameover.png");
	
	bso = Mix_LoadMUS("/usr/share/abbayev2/sounds/GameOverV2N.ogg");

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer,gameover,NULL,NULL);

	/* Flip */
	SDL_RenderPresent(renderer);
	Mix_PlayMusic(bso, 0);

	/* Wait */
	sleep(12);

	/* Cleaning */
	Mix_FreeMusic (bso);
	SDL_DestroyTexture(gameover);
	SDL_DestroyRenderer(renderer);

	*state = 0;

}