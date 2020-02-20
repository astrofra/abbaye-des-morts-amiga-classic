/* startscreen.c */

#include <stdio.h>
#include <stdlib.h>

#include "includes.prl"
#include "structs.h"
#include "aga_sdl.h"

extern struct Library *GfxBase;

void startscreen(SDL_Window *screen,uint *state,uint *grapset,uint *fullscreen)
{
	uint exit = 0;
	uint musicplay = 0;

	SDL_Rect srcintro = {0,0,256,192};
	SDL_Rect desintro = {0,0,256,192};

	SDL_Event keyp;

	SDL_Texture *intro = NULL;
	Mix_Music *music = NULL;

	/* Renderer (with VSync, nice !) */
	SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED);
	SDL_SetHint("SDL_HINT_RENDER_SCALE_QUALITY", "0");
	SDL_RenderSetLogicalSize(renderer, 256, 192);

	/* Loading PNG */
	#ifdef MEGADRIVE_GRAPHIC_SET
		intro = IMG_LoadTexture(renderer,"res/graphics/intromd.iff");
	#else
		intro = IMG_LoadTexture(renderer,"res/graphics/intro.iff");
	#endif

	/* Load audio */
	music = Mix_LoadMUS("/usr/share/abbayev2/sounds/MainTitleN.ogg");

	/* Cleaning the renderer */
	SDL_RenderClear(renderer);

	#ifdef MEGADRIVE_GRAPHIC_SET
		AGA_AppyTexturePalette(renderer, intro);
	#else
		AGA_AppyTexturePalette(renderer, intro);
	#endif

	/* Put image on renderer */
	#ifdef MEGADRIVE_GRAPHIC_SET
		SDL_RenderCopy(renderer, intro, &srcintro, &desintro);
	#else
		SDL_RenderCopy(renderer, intro, &srcintro, &desintro);
	#endif

	/* Flip ! */
	SDL_RenderPresent(renderer);

	/* Play music if required */
	if (musicplay == 0) {
		musicplay = 1;
		Mix_PlayMusic(music, 0);
	}
		
	while (exit != 1)
	{
		WaitTOF();
		/* Check keyboard */
		if (/* SDL_PollEvent(&keyp)*/0 ) {
			if (/*keyp.type == SDL_KEYDOWN*/0) { /* Key pressed */
				if (/*keyp.key.keysym.sym == SDLK_c*/0) { /* Change graphic set */
					if (*grapset == 0)
						*grapset = 1;
					else
						*grapset = 0;
				}
				if (/*keyp.key.keysym.sym == SDLK_i*/0) { /* Show instructions */
					if (srcintro.y == 0)
						srcintro.y = 192;
					else {
						srcintro.y = 0;
						musicplay = 0;
					}
				}
				if (/*keyp.key.keysym.sym == SDLK_f*/0) { /* Switch fullscreen/windowed */
					if (*fullscreen == 0) {
						SDL_SetWindowFullscreen(screen,SDL_WINDOW_FULLSCREEN_DESKTOP);
						*fullscreen = 1;
					}
					else {
						SDL_SetWindowFullscreen(screen,0);
						*fullscreen = 0;
					}
				}
				if (/*keyp.key.keysym.sym == SDLK_SPACE*/0) { /* Start game */
					*state = 1;
					exit = 1;
				}
				if (/*keyp.key.keysym.sym == SDLK_ESCAPE*/0) { /* Exit game */
      		exit = 1;
					*state = 6;
				}
			}
		}

		// exit = 1;

	}

	/* Cleaning */
	SDL_DestroyTexture(intro);
	SDL_DestroyRenderer(renderer);

}